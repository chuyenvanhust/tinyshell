#ifndef RONALDO_H
#define RONALDO_H

#include <thread>
#include <chrono>
#include <vector>
#include <iostream>

void showRonaldo() {
    const std::vector<std::string> frames = {
        R"( 
   \O/
    |
   / \
)",
        R"(
   \O
    |\
   / \
)",
        R"(
   _O_
    |
   / \
   SIUUU!
)",
        R"(
   \O/
    |
   / \
)"
    };

    for (int i = 0; i < 6; ++i) {
        system("cls"); // dùng "clear" nếu trên Linux/macOS
        std::cout << frames[i % frames.size()] << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
    }

    std::cout << "\n SIUUUUUUUUUUUUUU! \n" << std::endl;
}


#endif // RONALDO_H