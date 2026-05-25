#ifndef ANSISTYLE_HPP
#define ANSISTYLE_HPP

#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#else
#include <chrono>
#include <thread>
#endif

/**
 * @namespace ANSIStyle
 * @brief Màu sắc ANSI 256-color và tiện ích animation dùng chung toàn project.
 *
 * Cách dùng:
 *   std::cout << ANSIStyle::POKEMON << "text" << ANSIStyle::RESET;
 *   ANSIStyle::blinkText("[ PRESS ENTER ]", ANSIStyle::BLINK_CYAN, 3, 500);
 */
namespace ANSIStyle
{

    // ── Reset ────────────────────────────────────────────────────────────
    inline const std::string RESET = "\033[0m";
    inline const std::string BOLD = "\033[1m";
    inline const std::string DIM = "\033[2m";

    // ── Palette màu chữ lớn (title screen) ──────────────────────────────
    // POKEMON  — vàng (#F8C800 → 256c 220)
    inline const std::string POKEMON = "\033[1;38;5;220m";
    // GEN I    — cam lửa (#F87828 → 256c 208)
    inline const std::string GEN_I = "\033[1;38;5;208m";
    // KANTO    — đỏ đậm (#C03000 → 256c 160)
    inline const std::string KANTO = "\033[1;38;5;160m";

    // ── Palette màu rồng Charizard ───────────────────────────────────────
    // Cam nhạt #FF6600
    inline const std::string LIGHT_ORANGE = "\033[1;38;5;202m";
    // Cam đậm #FF0000
    inline const std::string DARK_ORANGE = "\033[1;38;5;196m";
    // Đỏ đậm #CC0000
    inline const std::string DARK_RED = "\033[1;38;5;160m";
    // Xanh #4D93D9
    inline const std::string BLUE = "\033[1;38;5;75m";
    // Vàng #FFC000
    inline const std::string YELLOW = "\033[1;38;5;220m";
    // Trắng #FFFFFF
    inline const std::string WHITE = "\033[1;38;5;15m";
    // Đen #000000
    inline const std::string BLACK = "\033[1;38;5;0m";

    // Phần rồng ngang POKEMON  — cam lửa chính (#F87828 → 256c 208)
    inline const std::string DRAGON_POKEMON = "\033[1;38;5;208m";
    // Phần rồng ngang GEN I    — đỏ đậm (#C03000 → 256c 160)
    inline const std::string DRAGON_GEN_I = "\033[1;38;5;160m";
    // Phần rồng ngang KANTO    — vàng bụng (#F8C800 → 256c 220)
    inline const std::string DRAGON_KANTO = "\033[1;38;5;220m";

    // ── Màu khác ─────────────────────────────────────────────────────────
    // Dòng copyright — xám bạc nhạt, tinh tế
    inline const std::string COPYRIGHT = "\033[38;5;245m";
    // "PRESS ENTER" khi nhấp nháy — đỏ lửa đồng bộ theme Charizard
    inline const std::string BLINK_CYAN = "\033[1;38;5;196m";

    // ── Sleep helper ─────────────────────────────────────────────────────
    /**
     * @brief Dừng thread hiện tại một khoảng thời gian (cross-platform).
     * @param ms Số millisecond cần dừng
     */
    inline void sleepMs(int ms)
    {
#ifdef _WIN32
        Sleep(ms);
#else
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
#endif
    }

    // ── Blink animation ──────────────────────────────────────────────────
    /**
     * @brief In một dòng chữ nhấp nháy tại vị trí con trỏ hiện tại.
     *        Dùng ANSI cursor-up để ghi đè lại cùng một dòng.
     *
     * @param text      Nội dung chữ cần nhấp nháy
     * @param color     Mã màu ANSI (dùng hằng trong ANSIStyle::)
     * @param times     Số lần nhấp nháy (1 lần = hiện + ẩn)
     * @param intervalMs Thời gian mỗi trạng thái hiện/ẩn (ms)
     */
    inline void blinkText(const std::string &text,
                          const std::string &color,
                          int times = 4,
                          int intervalMs = 350)
    {
        if (text.empty())
            return;

        std::cout << std::flush;

        for (int i = 0; i < times; ++i)
        {
            // Hiện chữ
            std::cout << "\033[2K" << color << text << ANSIStyle::RESET << "\r" << std::flush;
            sleepMs(intervalMs);

            // Ẩn chữ
            std::cout << "\033[2K\r" << std::flush;
            sleepMs(intervalMs);
        }

        // Kết thúc hiển thị
        std::cout << "\033[2K" << color << text << ANSIStyle::RESET << "\n"
                  << std::flush;
    }

    // ── Charizard sprite ─────────────────────────────────────────────
    /**
     * @brief In sprite Charizard pixel-art màu ANSI ra stdout.
     */
    inline void printStartScreen()
    {
        std::cout << ANSIStyle::BLACK << "                                                                                                       ████                      ████\n";
        std::cout << ANSIStyle::LIGHT_ORANGE << "    ██████╗  ██████╗ ██╗  ██╗███████╗███╗   ███╗ ██████╗ ███╗   ██╗                      " << ANSIStyle::BLACK << "██      ████  ██" << ANSIStyle::LIGHT_ORANGE << "██" << ANSIStyle::BLACK << "██                    ██" << ANSIStyle::DARK_RED << "██" << ANSIStyle::BLACK << "██\n";
        std::cout << ANSIStyle::LIGHT_ORANGE << "    ██╔══██╗██╔═══██╗██║ ██╔╝██╔════╝████╗ ████║██╔═══██╗████╗  ██║                    " << ANSIStyle::BLACK << "██" << ANSIStyle::LIGHT_ORANGE << "██" << ANSIStyle::BLACK << "██  ██" << ANSIStyle::DARK_ORANGE << "██" << ANSIStyle::BLACK << "██  ██" << ANSIStyle::LIGHT_ORANGE << "████" << ANSIStyle::BLACK << "██                  ██" << ANSIStyle::DARK_RED << "████" << ANSIStyle::BLACK << "██\n";
        std::cout << ANSIStyle::LIGHT_ORANGE << "    ██████╔╝██║   ██║█████╔╝ █████╗  ██╔████╔██║██║   ██║██╔██╗ ██║                    " << ANSIStyle::BLACK << "██" << ANSIStyle::LIGHT_ORANGE << "██" << ANSIStyle::BLACK << "████" << ANSIStyle::DARK_ORANGE << "████" << ANSIStyle::BLACK << "██    ██" << ANSIStyle::LIGHT_ORANGE << "██" << ANSIStyle::BLACK << "██                    ██" << ANSIStyle::DARK_RED << "██" << ANSIStyle::BLACK << "██\n";
        std::cout << ANSIStyle::LIGHT_ORANGE << "    ██╔═══╝ ██║   ██║██╔═██╗ ██╔══╝  ██║╚██╔╝██║██║   ██║██║╚██╗██║                  " << ANSIStyle::BLACK << "██" << ANSIStyle::LIGHT_ORANGE << "████" << ANSIStyle::BLACK << "██" << ANSIStyle::DARK_ORANGE << "██████" << ANSIStyle::BLACK << "██    ██" << ANSIStyle::LIGHT_ORANGE << "████" << ANSIStyle::BLACK << "████                ██" << ANSIStyle::DARK_RED << "████" << ANSIStyle::BLACK << "██\n";
        std::cout << ANSIStyle::LIGHT_ORANGE << "    ██║     ╚██████╔╝██║  ██╗███████╗██║ ╚═╝ ██║╚██████╔╝██║ ╚████║                  " << ANSIStyle::BLACK << "██" << ANSIStyle::LIGHT_ORANGE << "████" << ANSIStyle::DARK_ORANGE << "██████" << ANSIStyle::BLACK << "██      ██" << ANSIStyle::LIGHT_ORANGE << "████████" << ANSIStyle::BLACK << "██            ██" << ANSIStyle::DARK_RED << "██████" << ANSIStyle::BLACK << "██\n";
        std::cout << ANSIStyle::LIGHT_ORANGE << "    ╚═╝      ╚═════╝ ╚═╝  ╚═╝╚══════╝╚═╝     ╚═╝ ╚═════╝ ╚═╝  ╚═══╝              " << ANSIStyle::BLACK << "████" << ANSIStyle::LIGHT_ORANGE << "██████" << ANSIStyle::BLACK << "██" << ANSIStyle::DARK_ORANGE << "████" << ANSIStyle::BLACK << "██      ██" << ANSIStyle::LIGHT_ORANGE << "██████████" << ANSIStyle::BLACK << "████        ██" << ANSIStyle::DARK_RED << "██" << ANSIStyle::LIGHT_ORANGE << "██" << ANSIStyle::BLACK << "██\n";
        std::cout << ANSIStyle::BLACK << "                                                                               ██" << ANSIStyle::DARK_ORANGE << "██" << ANSIStyle::BLACK << "██" << ANSIStyle::LIGHT_ORANGE << "████" << ANSIStyle::BLACK << "██" << ANSIStyle::LIGHT_ORANGE << "██" << ANSIStyle::BLACK << "██" << ANSIStyle::DARK_ORANGE << "██" << ANSIStyle::BLACK << "██        ██" << ANSIStyle::LIGHT_ORANGE << "████████████" << ANSIStyle::BLACK << "██    ██" << ANSIStyle::DARK_RED << "██" << ANSIStyle::LIGHT_ORANGE << "████" << ANSIStyle::BLACK << "██\n";
        std::cout << ANSIStyle::DARK_ORANGE << "                   ██████╗ ███████╗███╗  ██╗   ██╗                           " << ANSIStyle::BLACK << "██" << ANSIStyle::DARK_ORANGE << "██" << ANSIStyle::LIGHT_ORANGE << "██" << ANSIStyle::BLACK << "██" << ANSIStyle::LIGHT_ORANGE << "██" << ANSIStyle::BLACK << "██" << ANSIStyle::LIGHT_ORANGE << "████" << ANSIStyle::BLACK << "██" << ANSIStyle::DARK_ORANGE << "██" << ANSIStyle::BLACK << "██      ██" << ANSIStyle::LIGHT_ORANGE << "██" << ANSIStyle::BLACK << "██" << ANSIStyle::LIGHT_ORANGE << "████" << ANSIStyle::DARK_ORANGE << "██" << ANSIStyle::LIGHT_ORANGE << "████" << ANSIStyle::DARK_ORANGE << "██" << ANSIStyle::BLACK << "██  ██" << ANSIStyle::DARK_RED << "██" << ANSIStyle::YELLOW << "██" << ANSIStyle::LIGHT_ORANGE << "██" << ANSIStyle::BLACK << "██\n";
        std::cout << ANSIStyle::DARK_ORANGE << "                  ██╔════╝ ██╔════╝████╗ ██║   ██║                           " << ANSIStyle::BLACK << "██" << ANSIStyle::DARK_ORANGE << "██" << ANSIStyle::BLACK << "██████" << ANSIStyle::LIGHT_ORANGE << "████" << ANSIStyle::BLACK << "██" << ANSIStyle::BLUE << "██" << ANSIStyle::DARK_ORANGE << "████" << ANSIStyle::BLACK << "██    ██" << ANSIStyle::LIGHT_ORANGE << "██" << ANSIStyle::BLACK << "██" << ANSIStyle::LIGHT_ORANGE << "██████" << ANSIStyle::DARK_ORANGE << "██" << ANSIStyle::LIGHT_ORANGE << "██" << ANSIStyle::DARK_ORANGE << "██" << ANSIStyle::BLACK << "██  ██" << ANSIStyle::LIGHT_ORANGE << "████" << ANSIStyle::YELLOW << "██" << ANSIStyle::LIGHT_ORANGE << "██" << ANSIStyle::BLACK << "██\n";
        std::cout << "                  ██║  ███╗█████╗  ██╔██╗██║   ██║                         " << "██              ██      ██  ██      ██      ██    ██  ██      ██\n";
        std::cout << "                  ██║   ██║██╔══╝  ██║╚████║   ██║                         ██            ██████    ████    ██  ██████    ██  ██  ██        ██\n";
        std::cout << "                  ╚██████╔╝███████╗██║ ╚███║   ██║                       ██                    ████      ██      ██  ██    ██    ██      ██\n";
        std::cout << "                   ╚═════╝ ╚══════╝╚═╝  ╚══╝   ╚═╝                       ██                                    ██      ██  ██  ██        ██\n";
        std::cout << "                                                                         ██        ██    ████              ██    ██    ██    ████        ██\n";
        std::cout << "             ██╗  ██╗ █████╗ ███╗  ██╗████████╗ ██████╗                ██        ██      ██  ██      ████    ██    ██    ██  ██  ██      ██\n";
        std::cout << "             ██╔═██╔╝██╔══██╗████╗ ██║╚══██╔══╝██╔═══██╗             ██                ██  ██  ██        ██    ████  ██  ██    ██  ██    ██\n";
        std::cout << "             █████╔╝ ███████║██╔██╗██║   ██║   ██║   ██║             ██            ████    ██  ██        ██        ████    ██  ██  ██  ██\n";
        std::cout << "             ██╔═██╗ ██╔══██║██║╚████║   ██║   ██║   ██║               ██      ████  ██      ██  ██  ████        ██  ████  ██  ████    ██\n";
        std::cout << "             ██║  ██╗██║  ██║██║ ╚███║   ██║   ╚██████╔╝                 ████  ██      ██████      ██          ██    ██  ██████      ██\n";
        std::cout << "             ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚══╝   ╚═╝    ╚═════╝                      ██            ██        ████    ██    ██              ██\n";
        std::cout << "                                                                                             ████████  ██████      ████        ████\n";
        std::cout << "                © 2026  POCKETRQUEST  —  DSA · HCMUS                                                     ██      ██    ███████\n";
        std::cout << "                                                                                                           ██████\n";

        std::cout << ANSIStyle::RESET << "\n";
    }

} // namespace ANSIStyle

#endif // ANSISTYLE_HPP