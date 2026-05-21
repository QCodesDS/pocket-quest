#ifndef UI_HPP
#define UI_HPP

#include <string>

/**
 * @namespace UI
 * @brief     Cung cấp các hàm vẽ, định dạng giao diện console ASCII chuẩn và đẹp mắt.
 */
namespace UI {
    /**
     * @brief Xóa trắng màn hình console, tự động chuyển đổi theo hệ điều hành (Windows cls / Unix clear).
     */
    void clearScreen();

    /**
     * @brief In ra một hộp thoại viền kép (Double-line Border Box) bao bọc tiêu đề và nội dung.
     * @param title Tiêu đề hộp thoại
     * @param content Nội dung dòng văn bản cần in
     */
    void printBox(const std::string& title, const std::string& content);

    /**
     * @brief In ra đường kẻ phân tách dài với ký tự tùy chọn.
     * @param sym Ký tự làm đường kẻ (mặc định: '=')
     * @param width Độ rộng đường kẻ (mặc định: 42)
     */
    void printSeparator(char sym = '=', int width = 42);

    /**
     * @brief Trực quan hóa thanh HP Bar dạng [#######...] thân thiện.
     * @param hp Lượng HP hiện tại
     * @param maxHp Lượng HP tối đa
     * @param width Độ dài tối đa của thanh vẽ (mặc định: 10)
     * @return Chuỗi vẽ thanh HP (ví dụ: "[#######...]")
     */
    std::string hpBar(int hp, int maxHp, int width = 10);
}

#endif // UI_HPP
