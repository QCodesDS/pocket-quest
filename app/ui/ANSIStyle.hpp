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
    // POKEMON  — vàng rực
    inline const std::string POKEMON = "\033[1;38;5;220m";
    // GEN I    — xanh lá tươi
    inline const std::string GEN_I = "\033[1;38;5;82m";
    // KANTO    — đỏ cam
    inline const std::string KANTO = "\033[1;38;5;208m";

    // ── Palette màu rồng (theo hàng tương ứng chữ) ──────────────────────
    // Phần rồng ngang POKEMON  — tím
    inline const std::string DRAGON_POKEMON = "\033[1;38;5;141m";
    // Phần rồng ngang GEN I    — xanh ngọc
    inline const std::string DRAGON_GEN_I = "\033[1;38;5;87m";
    // Phần rồng ngang KANTO    — hồng san hô
    inline const std::string DRAGON_KANTO = "\033[1;38;5;204m";

    // ── Màu khác ─────────────────────────────────────────────────────────
    // Dòng copyright — xám bạc nhạt, tinh tế
    inline const std::string COPYRIGHT = "\033[38;5;245m";
    // "PRESS ENTER" khi nhấp nháy — cyan sáng
    inline const std::string BLINK_CYAN = "\033[1;38;5;87m";

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
                          int times = 3,
                          int intervalMs = 500)
    {
        // In placeholder để giữ dòng
        std::cout << "\n"
                  << std::flush;

        for (int i = 0; i < times * 2; i++)
        {
            // Di chuyển con trỏ lên 1 dòng rồi xóa dòng đó
            std::cout << "\033[1A\033[2K";

            if (i % 2 == 0)
            {
                std::cout << color << text << RESET << "\n"
                          << std::flush;
            }
            else
            {
                std::cout << std::string(text.size(), ' ') << "\n"
                          << std::flush;
            }
            sleepMs(intervalMs);
        }
        // Kết thúc: để chữ hiển thị
        std::cout << "\033[1A\033[2K" << color << text << RESET << "\n"
                  << std::flush;
    }

} // namespace ANSIStyle

#endif // ANSISTYLE_HPP