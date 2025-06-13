#ifndef HELP_H
#define HELP_H

#include <iostream>
#include <vector>
#include <iomanip>

void showHelp(const std::vector<std::string> &args)
{
    if (!args.empty())
    {
        std::cerr << "Usage: help" << std::endl;
        return;
    }

    std::cout << std::left;
    std::cout << std::setw(22) << "Command" << ": Description" << std::endl;
    std::cout << std::setw(22) << "--------------------" << "-----------------------------" << std::endl;

    std::cout << "\n[ File & Directory ]\n";
    std::cout << std::setw(22) << "create" << ": Create a directory" << std::endl;
    std::cout << std::setw(22) << "delete" << ": Delete a directory" << std::endl;
    std::cout << std::setw(22) << "move" << ": Move a directory" << std::endl;
    std::cout << std::setw(22) << "copy" << ": Copy a directory" << std::endl;
    std::cout << std::setw(22) << "tree" << ": List directory tree" << std::endl;
    std::cout << std::setw(22) << "cd" << ": Change directory" << std::endl;
    std::cout << std::setw(22) << "ls" << ": List directory contents" << std::endl;
    std::cout << std::setw(22) << "pwd" << ": Print working directory" << std::endl;

    std::cout << "\n[ File Operations ]\n";
    std::cout << std::setw(22) << "open" << ": Open a file" << std::endl;
    std::cout << std::setw(22) << "rename" << ": Rename a file" << std::endl;
    std::cout << std::setw(22) << "write_file" << ": Write content to file" << std::endl;
    std::cout << std::setw(22) << "read_file" << ": Read content from file" << std::endl;
    std::cout << std::setw(22) << "copy_file" << ": Copy a file" << std::endl;
    std::cout << std::setw(22) << "file_size" << ": Get file size" << std::endl;

    std::cout << "\n[ Process Management ]\n";
    std::cout << std::setw(22) << "run_fg" << ": Run process in foreground" << std::endl;
    std::cout << std::setw(22) << "run_bg" << ": Run process in background" << std::endl;
    std::cout << std::setw(22) << "terminate" << ": Terminate a process" << std::endl;
    std::cout << std::setw(22) << "ps" << ": List running processes" << std::endl;
    std::cout << std::setw(22) << "child" << ": Start a child process" << std::endl;
    std::cout << std::setw(22) << "list_children" << ": Print all child processes" << std::endl;
    std::cout << std::setw(22) << "suspend" << ": Suspend a process" << std::endl;
    std::cout << std::setw(22) << "resume" << ": Resume a process" << std::endl;

    std::cout << "\n[ System Info ]\n";
    std::cout << std::setw(22) << "time" << ": Show system time" << std::endl;
    std::cout << std::setw(22) << "date" << ": Show system date" << std::endl;
    std::cout << std::setw(22) << "uptime" << ": Show system uptime" << std::endl;
    std::cout << std::setw(22) << "cpuinfo" << ": Show CPU information" << std::endl;
    std::cout << std::setw(22) << "meminfo" << ": Show memory information" << std::endl;
    std::cout << std::setw(22) << "diskinfo" << ": Show disk information" << std::endl;
    std::cout << std::setw(22) << "osinfo" << ": Show OS information" << std::endl;
    std::cout << std::setw(22) << "list_drivers" << ": List all drivers" << std::endl;

    std::cout << "\n[ Display & Appearance ]\n";
    std::cout << std::setw(22) << "set_color" << ": Change text color" << std::endl;
    std::cout << std::setw(22) << "clear" << ": Clear screen" << std::endl;

    std::cout << "\n[ Calculator & Expression ]\n";
    std::cout << std::setw(22) << "calculator" << ": Open calculator" << std::endl;
    std::cout << std::setw(22) << "calculate" << ": Calculate expression value" << std::endl;
    std::cout << std::setw(22) << "convert" << ": Convert number base" << std::endl;

    std::cout << "\n[ Environment Variables ]\n";
    std::cout << std::setw(22) << "add_path" << ": Add path to PATH" << std::endl;
    std::cout << std::setw(22) << "remove_path" << ": Remove path from PATH" << std::endl;
    std::cout << std::setw(22) << "set_env" << ": Set environment variable" << std::endl;
    std::cout << std::setw(22) << "unset_env" << ": Unset environment variable" << std::endl;
    std::cout << std::setw(22) << "print_env" << ": Print environment variable" << std::endl;
    std::cout << std::setw(22) << "list_env" << ": List all environment variables" << std::endl;

    std::cout << "\n[ Fun Commands ]\n";
    std::cout << std::setw(22) << "ronaldo" << ": SIUUUUUUUUUU" << std::endl;
    std::cout << std::setw(22) << "run_producer_consumer" << ": Launch a simulation of the producer-consumer problem" << std::endl;
    std::cout << std::setw(22) << "random_fact" << ": Show a random fact" << std::endl;

    std::cout << "\n[ Utility ]\n";
    std::cout << std::setw(22) << "run" << ": Run a script" << std::endl;
    std::cout << std::setw(22) << "help" << ": Show this help message" << std::endl;
    std::cout << std::setw(22) << "exit" << ": Exit the shell" << std::endl;
    std::cout << std::setw(22) << "history" << ": Show command history" << std::endl;
    std::cout << std::setw(22) << "clear_history" << ": Clear command history" << std::endl;
}

#endif // HELP_H
