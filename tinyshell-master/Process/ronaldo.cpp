// Process/ronaldo.cpp
#include <stdio.h>
#include <string.h>  // Cho strlen nếu cần
#include <windows.h> // Cho Sleep, GetStdHandle, SetConsoleCursorInfo
#include <vector>
#include <string>    // std::string
#include <chrono>    // std::chrono::milliseconds
#include <thread>    // std::this_thread::sleep_for

// Hàm xóa màn hình bằng mã ANSI escape và di chuyển con trỏ về đầu
void clearScreenRonaldo() {
    printf("\033[H\033[J");
    fflush(stdout);
}

// Hàm sleep
void customSleep(unsigned int milliseconds) {
#ifdef _WIN32
    Sleep(milliseconds);
#else
    // usleep(milliseconds * 1000); // Cần unistd.h
    Sleep(milliseconds); // Giữ lại Sleep cho đơn giản trong môi trường Windows
#endif
}

// --- Các Frame ASCII cho Animation Ronaldo ---
// LƯU Ý: Đảm bảo các ký tự Unicode Braille (nếu có) hiển thị đúng trên terminal của bạn.
// Nếu không, hãy thay thế chúng bằng các ký tự ASCII đơn giản hơn.

const std::vector<std::string> frame_ronaldo_0_prepare = {
    "                                     ",
    "#######***..*********..**************",
    "####*..*#####..****''*#####''''****##",
    "###*....''''....###....###.....***##",
    "###*.............###***###......**##",
    "###*.............###**###*......##**",
    "###*..#####......###...###*.....###*",
    "**###*****'......###...*###....*###*",
    "..'''''''.........'''....'''....''''",
    "..................****##****........",
    "..................*######*'.........",
    "................*##########*........",
    ".............*###############*......",
    "..........*#######**--**######......",
    ".......*####*''....####.#####'''*...",
    "....*####'''.......#######***''*##*.",
    "*###'''.............############..''",
    "..................#############*...",
    ".................###############*..",
    "................*#####'''''######*.",
    "...............*####'..........####*",
    "............*####*'..............*##",
    "..........*###*'..................##*",
    ".........*##'......................##*",
    "........'##........................##*",
    ".......-*'..........................##*---"
    // "Cristiano Ronaldo", // Sẽ in riêng
    // "Chuẩn bị... ⚽"
};

const std::vector<std::string> frame_ronaldo_1_jump_siu = {
    "                                     ",
    "#######***..*********..**************",
    "####*..*#####..****''*#####''''****##",
    "###*....''''....###....###.....***##",
    "###*.............###***###......**##",
    "###*.............###**###*......##**",
    "###*..#####......###...###*.....###*",
    "**###*****'......###...*###....*###*",
    "..'''''''.........'''....'''....''''",
    "..................****##****........",
    "..................*######*'.........",
    "................*##########*........",
    ".............*###############*......",
    "..........*#######** \\O/ #######......", // Tay dang lên
    ".......*####*''....####.#####'''*...",
    "....*####'''.......#######***''*##*.",
    "*###'''.............############..''",
    "..................#############*...",
    ".................###############*..",
    "................*#####'''''######*.",
    "...............*####'..........####*", // Chân có thể hơi co lại
    "............*####*'..............*##",
    "..........*###*'..................##*",
    ".........*##'...................._/\\_", // Mô phỏng chân co
    "........'##........................##*",
    ".......-*'..........................##*---"
    // "Cristiano Ronaldo",
    // "Bay lên! SIUU ⚽⚽"
};

const std::vector<std::string> frame_ronaldo_2_siu_complete = {
    "                                     ",
    "#######***..*********..**************",
    "####*..*#####..****''*#####''''****##",
    "###*....''''....###....###.....***##",
    "###*.............###***###......**##",
    "###*.............###**###*......##**",
    "###*..#####......###...###*.....###*",
    "**###*****'......###...*###....*###*",
    "..'''''''.........'''....'''....'''' SIIIIIIIIIIIIIIIIIII", // SIU to hơn
    "..................****##****........",
    "..................*######*'.........",
    "................*##########*........",
    ".............*###############*......",
    "..........*#######** \\O/**######......", // Tay dang rộng, hoặc tư thế SIU hoàn chỉnh
    ".......*####*''....####.#####'''*... UUUUUUUUUUUUUUUUUUU",
    "....*####'''.......#######***''*##*.",
    "*###'''.............############..''",
    "..................#############*...",
    ".................###############*..",
    "................*#####'''''######*.",
    "...............*####'..........####*", // Chân tiếp đất vững chãi
    "............*####*'..............*##",
    "..........*###*'..................##*",
    ".........*##'.........LL.LL........##*", // Chân
    "........'##........................##*",
    ".......-*'..........................##*---"
    // "Cristiano Ronaldo",
    // "SIUUUUUUU ⚽⚽⚽"
};

// Frame chạy (tạo 2 frame để có cảm giác chuyển động)
const std::vector<std::string> frame_ronaldo_run_1 = {
    "                                     ",
    "#######***..*********..**************",
    "####*..*#####..****''*#####''''****##",
    "###*....''''....###....###.....***##",
    "###*.............###***###......**##",
    "###*.............###**###*......##**",
    "###*..#####......###...###*.....###*",
    "**###*****'......###...*###....*###*",
    "..'''''''.........'''....'''....''''",
    "..................****##****........",
    "..................*######*'.........",
    "................*##########*........",
    ".............*###############*......",
    "..........*#######**--**######......",
    ".......*####*''....####.#####'''*...",
    "....*####'''.......#######***''*##*.",
    "*###'''.............############..''",
    "..................#############*...",
    ".................###############*..",
    "................*#####'''''######*.",
    "...............*####'..........####*",
    "............*####*'..............*##",
    "..........*###*'..................##*.",
    ".........*##'.....................##*/", // Chân phải trước
    "........'##......................._/##",
    ".......-*'..........................##*---"
};
const std::vector<std::string> frame_ronaldo_run_2 = {
    "                                     ",
    "#######***..*********..**************",
    "####*..*#####..****''*#####''''****##",
    "###*....''''....###....###.....***##",
    "###*.............###***###......**##",
    "###*.............###**###*......##**",
    "###*..#####......###...###*.....###*",
    "**###*****'......###...*###....*###*",
    "..'''''''.........'''....'''....''''",
    "..................****##****........",
    "..................*######*'.........",
    "................*##########*........",
    ".............*###############*......",
    "..........*#######**--**######......",
    ".......*####*''....####.#####'''*...",
    "....*####'''.......#######***''*##*.",
    "*###'''.............############..''",
    "..................#############*...",
    ".................###############*..",
    "................*#####'''''######*.",
    "...............*####'..........####*",
    "............*####*'..............*##*\\", // Chân trái trước
    "..........*###*'.................._\\##",
    ".........*##'......................./",
    "........'##........................##",
    ".......-*'..........................##*---"
};

// Frame sút bóng
const std::vector<std::string> frame_ronaldo_kick_ball = {
    "                                     ",
    "#######***..*********..**************",
    "####*..*#####..****''*#####''''****##",
    "###*....''''....###....###.....***##",
    "###*.............###***###......**##",
    "###*.............###**###*......##**",
    "###*..#####......###...###*.....###*",
    "**###*****'......###...*###....*###*",
    "..'''''''.........'''....'''....''''",
    "..................****##****........",
    "..................*######*'.........",
    "................*##########*........",
    ".............*###############*......",
    "..........*#######**--**######......",
    ".......*####*''....####.#####'''*...",
    "....*####'''.......#######***''*##*.",
    "*###'''.............############..''",
    "..................#############*...",
    ".................###############*..",
    "................*#####'''''######*.",
    "...............*####'..........####*",
    "............*####*'..............*##",
    "..........*###*'..................##",
    ".........*##'...................⚽##", // Bóng gần chân
    "........'##.....................__/##", // Chân sút
    ".......-*'..........................##*---"
};

// Frame bóng bay và GOAL
const std::vector<std::string> frame_ronaldo_ball_fly_goal = {
    "                                   ⚽ ",
    "                                     ",
    "      GGGGGGGGGGG   OOOOOOOOO        ",
    "     GGG           OOO     OOO       ",
    "    GGG           OOO       OOO      ",
    "   GGG    GGGGGG OOO         OOO     ",
    "   GGG       GGG OOO         OOO     ",
    "    GGG      GGG  OOO       OOO      ",
    "     GGG     GGG   OOO     OOO       ",
    "      GGGGGGGGG     OOOOOOOOO        ",
    "                                     ",
    "        AAAAAAA     LLL              ",
    "       AAA   AAA    LLL              ",
    "      AAA     AAA   LLL              ",
    "      AAAAAAAAAAA   LLL              ",
    "      AAAAAAAAAAA   LLL              ",
    "      AAA     AAA   LLLLLLLLLL       ",
    "      AAA     AAA   LLLLLLLLLL       ",
    "                                     ",
    "#######***..*********..**************", // Ronaldo nhìn theo bóng
    "####*..*#####..****''*#####''''****##",
    "###*....''''....###....###.....***##",
    "###*.............###***###......**##",
    "###*.............###**###*......##**",
    "###*..#####......###...###*.....###*",
    "**###*****'......###...*###....*###*"
};


// Hàm in một frame với padding
void printSingleAsciiFrame(const std::vector<std::string>& frame_lines, int left_padding) {
    for (const std::string& line : frame_lines) {
        for (int i = 0; i < left_padding; ++i) {
            printf(" ");
        }
        printf("%s\n", line.c_str());
    }
}

int main() {
    std::vector<std::vector<std::string>> animation_sequence;
    // Giai đoạn 1: Intro và chuẩn bị
    animation_sequence.push_back(frame_ronaldo_0_prepare); // 0
    animation_sequence.push_back(frame_ronaldo_0_prepare); // 1: Đứng yên

    // Giai đoạn 2: Chạy lấy đà
    animation_sequence.push_back(frame_ronaldo_run_1);     // 2
    animation_sequence.push_back(frame_ronaldo_run_2);     // 3
    animation_sequence.push_back(frame_ronaldo_run_1);     // 4
    animation_sequence.push_back(frame_ronaldo_run_2);     // 5

    // Giai đoạn 3: Sút bóng
    animation_sequence.push_back(frame_ronaldo_kick_ball); // 6
    animation_sequence.push_back(frame_ronaldo_ball_fly_goal); // 7: Bóng bay + GOAL
    animation_sequence.push_back(frame_ronaldo_ball_fly_goal); // 8: Giữ GOAL

    // Giai đoạn 4: Ăn mừng Siuuu
    animation_sequence.push_back(frame_ronaldo_run_1);          // 9: Chạy ăn mừng
    animation_sequence.push_back(frame_ronaldo_run_2);          // 10: Chạy ăn mừng
    animation_sequence.push_back(frame_ronaldo_1_jump_siu);     // 11: Nhảy lên
    animation_sequence.push_back(frame_ronaldo_2_siu_complete); // 12: Tư thế Siuuu
    animation_sequence.push_back(frame_ronaldo_2_siu_complete); // 13: Giữ pose
    animation_sequence.push_back(frame_ronaldo_2_siu_complete); // 14: Giữ pose
    // animation_sequence.push_back(frame_ronaldo_0_prepare); // Quay lại đứng yên để lặp

    int current_frame_idx = 0;
    int animation_delay_ms = 200; // Tốc độ animation (0.2 giây mỗi frame)

    // Căn giữa cơ bản
    int terminal_width_approx = 100; // Ước lượng chiều rộng terminal
    size_t art_width = 0;
    if (!animation_sequence.empty() && !animation_sequence[0].empty() && !animation_sequence[0][1].empty()) {
        art_width = animation_sequence[0][1].length(); // Dòng thứ 2 của frame đầu làm chuẩn
    }
    if (art_width == 0) art_width = 45; // Fallback

    int position = (terminal_width_approx - static_cast<int>(art_width)) / 2;
    if (position < 0) position = 0;

    // Ẩn con trỏ console
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    // --- Phần Intro ngắn ---
    clearScreenRonaldo();
    const char* title = "### CRISTIANO RONALDO ###";
    const char* subtitle = "THE LEGEND... THE GOAL... THE SIUUUU!";
    int title_len = strlen(title);
    int subtitle_len = strlen(subtitle);

    for(int i=0; i < (terminal_width_approx - title_len)/2; ++i) printf(" ");
    printf("%s\n\n", title);
    for(int i=0; i < (terminal_width_approx - subtitle_len)/2; ++i) printf(" ");
    printf("%s\n\n", subtitle);
    customSleep(2500); // Chờ 2.5 giây

    // --- Vòng lặp Animation Chính ---
    while (true) { // Chạy vô hạn
        clearScreenRonaldo(); // Xóa màn hình TRƯỚC KHI vẽ frame mới

        printSingleAsciiFrame(animation_sequence[current_frame_idx], position);

        // Caption
        std::string caption_ronaldo = "Cristiano Ronaldo";
        std::string caption_siu = "Siuuuuuu ⚽⚽";
        int pad_cap1 = (terminal_width_approx - caption_ronaldo.length()) / 2;
        int pad_cap2 = (terminal_width_approx - caption_siu.length()) / 2;
        if(pad_cap1 < 0) pad_cap1 = 0;
        if(pad_cap2 < 0) pad_cap2 = 0;

        for(int i=0; i<pad_cap1; ++i) printf(" ");
        printf("%s\n", caption_ronaldo.c_str());
        for(int i=0; i<pad_cap2; ++i) printf(" ");
        printf("%s\n", caption_siu.c_str());

        customSleep(animation_delay_ms);

        current_frame_idx = (current_frame_idx + 1) % animation_sequence.size();
        // Nếu muốn Ronaldo di chuyển ngang, bạn có thể thêm logic thay đổi 'position' ở đây
    }

    // Đoạn này sẽ không bao giờ được thực thi trong vòng lặp vô hạn hiện tại
    // cursorInfo.bVisible = TRUE;
    // SetConsoleCursorInfo(hConsole, &cursorInfo);
    return 0;
}