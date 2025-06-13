#ifndef NET_SPEED_H
#define NET_SPEED_H

#include <windows.h>
#include <iphlpapi.h>
#include <iostream>
#include <csignal>
#include <thread>
#include <chrono>
#include <vector>
#include <iomanip>

#pragma comment(lib, "iphlpapi.lib")

bool keepRunning = true;

void signalHandler(int signal) {
    if (signal == SIGINT) {
        std::cout << "\nStopping net_speed...\n";
        keepRunning = false;
    }
}

void showNetSpeed(const std::vector<std::string> &args) {
        if (!args.empty()) {
        std::cerr << "Usage: net_speed" << std::endl;
        return;
    }

    signal(SIGINT, signalHandler);

    DWORD size = 0;
    GetIfTable(nullptr, &size, FALSE);
    std::vector<char> buffer(size);
    MIB_IFTABLE* ifTable = reinterpret_cast<MIB_IFTABLE*>(buffer.data());

    if (GetIfTable(ifTable, &size, FALSE) != NO_ERROR) {
        std::cerr << "Failed to get network table." << std::endl;
        return;
    }

    std::cout << "Monitoring network speed... (Ctrl+C to stop)" << std::endl;

    while (keepRunning) {
        uint64_t in1 = 0, out1 = 0;
        for (DWORD i = 0; i < ifTable->dwNumEntries; ++i) {
            in1 += ifTable->table[i].dwInOctets;
            out1 += ifTable->table[i].dwOutOctets;
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));

        if (GetIfTable(ifTable, &size, FALSE) != NO_ERROR) {
            std::cerr << "Failed to get network table." << std::endl;
            break;
        }

        uint64_t in2 = 0, out2 = 0;
        for (DWORD i = 0; i < ifTable->dwNumEntries; ++i) {
            in2 += ifTable->table[i].dwInOctets;
            out2 += ifTable->table[i].dwOutOctets;
        }

        double downloadSpeed = (in2 - in1) / 1024.0;
        double uploadSpeed = (out2 - out1) / 1024.0;

        std::cout << "\rDownload Speed: " << std::setw(8) << std::fixed << std::setprecision(2) << downloadSpeed << " KB/s"
                  << " | Upload Speed: " << std::setw(8) << std::fixed << std::setprecision(2) << uploadSpeed << " KB/s" << std::flush;
    }

    std::cout << "\nExiting net_speed.\n";
}


#endif //NET_SPEED_H