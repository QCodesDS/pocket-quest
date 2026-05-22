#ifndef INTROUI_HPP
#define INTROUI_HPP

#include <string>
#include "../entities/Player.hpp"

/**
 * @namespace IntroUI
 * @brief     Quản lý các màn hình và hộp thoại giới thiệu khi bắt đầu trò chơi (Intro Flow).
 */
namespace IntroUI
{
    /**
     * @brief Hiển thị văn bản dạng máy đánh chữ (typewriter effect) từng ký tự một.
     * @param text Dòng chữ cần chạy
     * @param delayMs Độ trễ giữa mỗi ký tự (mặc định: 20ms)
     */
    void typeWrite(const std::string &text, int delayMs = 20);

    /**
     * @brief Vẽ và hiển thị viền hộp thoại đa dòng kết hợp hiệu ứng typewriter thời gian thực.
     * @param title Tiêu đề của hộp thoại
     * @param content Nội dung văn bản chạy chữ bên trong viền
     */
    void typeWriteBox(const std::string &title, const std::string &content);

    /**
     * @brief Màn hình chào mừng chính (Title Screen). Chờ phím Enter để tiếp tục.
     */
    void showTitleScreen();

    /**
     * @brief Đoạn giới thiệu thế giới pokemon.
     */
    void showOpeningStory();

    /**
     * @brief Đoạn hội thoại kể chuyện đầu tiên của Giáo sư Oak.
     */
    void showOakDialog();

    /**
     * @brief Hộp thoại hỏi và nhập tên Trainer của người chơi có xử lý chống khoảng trắng trống.
     * @param player Tham chiếu đối tượng Player để cập nhật tên
     */
    void showNameInput(Player &player);

    /**
     * @brief Hiển thị bảng chọn 3 Starter Pokémon đầu tiên của Gen 1 và bắt buộc người chơi chọn hợp lệ.
     * @param player Tham chiếu đối tượng Player để cập nhật Starter được chọn
     */
    void showStarterSelect(Player &player);
}

#endif // INTROUI_HPP
