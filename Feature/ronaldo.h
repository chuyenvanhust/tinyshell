#ifndef RONALDO_H
#define RONALDO_H

#include <iostream>
#include <vector>
#include <string>
#include <thread> // Cho std::this_thread::sleep_for
#include <chrono> // Cho std::chrono::milliseconds

// Hàm xóa màn hình cơ bản (nếu bạn muốn màn hình động)
// Bạn có thể dùng lại hàm clearScreen() đã có nếu nó được khai báo global
// hoặc include "clear_screen.h" nếu nó là file riêng.
// Hoặc dùng mã ANSI escape trực tiếp.
inline void clearScreenForAnimation() {
    #ifdef _WIN32
        // system("cls"); // Cách này hoạt động nhưng không phải lúc nào cũng tốt
        // In mã ANSI escape để xóa màn hình và di chuyển con trỏ về đầu
        // Hoạt động tốt trên Windows Terminal mới và nhiều terminal khác.
        std::cout << "\033[H\033[J" << std::flush;
    #else
        // Cho Linux/macOS
        std::cout << "\033[H\033[J" << std::flush;
    #endif
}


inline void displayRonaldoSiu() {
    const std::vector<std::string> ronaldo_art = {
        "                                  SIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU",
        "                                                                                                                                                                                     ",
        "                                                                        #####                                                                                                      ",
        "                                                                     ###    ####                                                                                                   ",
        "                                                                    ##   ##   ###                                                                                                  ",
        "                                                                   ##  #  #   ###                                                                                                  ",
        "                                                                   #  ####   ##                                                                                                   ",
        "                                                                   #  ####   ##                                                                                                   ",
        "                                                                    ## ##   ##             #                                                                                         ",
        "                                     ##########                      ###   ###            ###                                                                                        ",
        "                                  ####        ####                   #####             #####                                                                                       ",
        "                                ###              ###                                  ##   ##                                                                                       ",
        "                              ###        ##        ###                               ##  #  ##                                                                                      ",
        "                             ##         ####         ##                              ## ## ##                                                                                       ",
        "                            ##           ##           ##                              ### ###                                                                                        ",
        "                            ##                        ##                               #####                                                                                         ",
        "                             ##                      ##                                 ###                                                                                          ",
        "                              ###       ##        ###                                                                                                                              ",
        "                                ###    ####      ###                                                                                                                               ",
        "                                 ##################                                                                                                                                ",
        "                                ###  ##########  ###                                                                                                                               ",
        "                              ###   ## ###### ##   ###                                                                                                                             ",
        "                             ##    ##    ##    ##    ##                                                                                                                            ",
        "                           ##      ##    ##    ##      ##                                                                                                                           ",
        "                          ##        ###### ######        ##                                                                                                                          ",
        "                          ##                           ##                                                                                                                           ",
        "                           ####                     ####                                                                                                                            ",
        "                              ######################                                                                                                                                 ",
        "                                    ############                                                                                                                                   ",
        "                                      ######                                                                                                                                       ",
        "                                                                                                                                                                                     "
    };

    const std::vector<std::string> celebration_frames[] = {
        {
        "                               SIIIIIIIIIIIUUUUUUUUUUU!                                 ",
        "                                      #####                                             ",
        "                                   ###    ####                                          ",
        "                                  ##   ##   ###                                         ",
        "                                 ##  #  #   ###                                         ",
        "                                 #  ####   ##                                          ",
        "                                 #  ####   ##                                          ",
        "                                  ## ##   ##             #                              ",
        "                ##########         ###   ###            ###                             ",
        "             ####        ####       #####             #####                             ",
        "           ###              ###                      ##   ##                             ",
        "         ###        ##        ###                   ##  #  ##                            ",
        "        ##         ####         ##                  ## ## ##                             ",
        "       ##           ##           ##                  ### ###                             ",
        "       ##                        ##                   #####                              ",
        "        ##                      ##                     ###                               ",
        "         ###       ##        ###                                                        ",
        "           ###    ####      ###                                                         ",
        "             ##################                                                         ",
        "               ############                                                             "
        },
        {
        "                               SIIIIIIIIIIIUUUUUUUUUUU!                                 ",
        "                                      #####                                             ",
        "                                   ###    ####                                          ",
        "                                  ##   ##   ###                                         ",
        "                                 ##  #  #   ###                                         ",
        "         \\  O  /                #  ####   ##                                          ",
        "          \\ | /                 #  ####   ##                                          ",
        "           \\|/                   ## ##   ##             #                              ",
        " O--<--<--<--X-->-->-->--O  ##########         ###   ###            ###                             ",
        "           /|\\             ####        ####       #####             #####                             ",
        "          / | \\                 ###              ###                      ##   ##                             ",
        "         /  O  \\               ###        ##        ###                   ##  #  ##                            ",
        "                               ##         ####         ##                  ## ## ##                             ",
        "                               ##           ##           ##                  ### ###                             ",
        "                               ##                        ##                   #####                              ",
        "                                ##                      ##                     ###                               ",
        "                                 ###       ##        ###                                                        ",
        "                                   ###    ####      ###                                                         ",
        "                                     ##################                                                         ",
        "                                       ############                                                             "
        },
        {
        "                               SIIIIIIIIIIIUUUUUUUUUUU!                                 ",
        "                                      #####                                             ",
        "                                   ###    ####                                          ",
        "                                  ##   ##   ###                                         ",
        "                                 ##  #  #   ###                                         ",
        "                                 #  ####   ##                  \\  O  /                 ",
        "                                 #  ####   ##                   \\ | /                  ",
        "                                  ## ##   ##             #       \\|/                   ",
        "                ##########         ###   ###            ###  O--<--<--<--X-->-->-->--O   ",
        "             ####        ####       #####             #####        /|\\                  ",
        "           ###              ###                      ##   ##      / | \\                 ",
        "         ###        ##        ###                   ##  #  ##    /  O  \\                ",
        "        ##         ####         ##                  ## ## ##                             ",
        "       ##           ##           ##                  ### ###                             ",
        "       ##                        ##                   #####                              ",
        "        ##                      ##                     ###                               ",
        "         ###       ##        ###                                                        ",
        "           ###    ####      ###                                                         ",
        "             ##################                                                         ",
        "               ############                                                             "
        }
    };


    // Hiển thị hình ảnh tĩnh ban đầu
    clearScreenForAnimation();
    for (const auto& line : ronaldo_art) {
        std::cout << line << std::endl;
    }
    std::cout << "\n\nPress Enter to see the SIU celebration..." << std::endl;
    std::cin.get(); // Chờ người dùng nhấn Enter

    // Animation ăn mừng "SIU"
    for (int cycle = 0; cycle < 3; ++cycle) { // Lặp lại animation vài lần
        for (const auto& frame : celebration_frames) {
            clearScreenForAnimation();
            for (const auto& line : frame) {
                std::cout << line << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(300)); // Tốc độ animation
        }
    }

    // Quay lại hình ảnh tĩnh hoặc một thông điệp cuối
    clearScreenForAnimation();
     for (const auto& line : ronaldo_art) {
        std::cout << line << std::endl;
    }
    std::cout << "\nCR7 - The GOAT!" << std::endl;
}

// Hàm xử lý lệnh 'ronaldo'
inline void handleRonaldoCommand(const std::vector<std::string>& args) {
    // Lệnh này không cần đối số, nhưng vẫn giữ tham số args cho nhất quán
    if (!args.empty()) {
        std::cout << "Usage: ronaldo (this command takes no arguments)" << std::endl;
        // return; // Có thể cho phép chạy dù có đối số thừa
    }
    displayRonaldoSiu();
}

#endif // RONALDO_H