#include "UI.hpp"
#include <iostream>
#include <iomanip>
#include <cstdlib>

namespace UI {

    void clearScreen() {
#ifdef _WIN32
        std::system("cls");
#else
        std::system("clear");
#endif
    }

    void printSeparator(char sym, int width) {
        for (int i = 0; i < width; ++i) {
            std::cout << sym;
        }
        std::cout << "\n";
    }

    void printBox(const std::string& title, const std::string& content) {
        const int innerWidth = 38; // Độ rộng văn bản thực tế bên trong viền

        // 1. Vẽ cạnh trên của hộp thoại (tăng thêm 2 ký tự để vừa khít với lề trống bên trong)
        if (title.empty()) {
            std::cout << "╔";
            for (int i = 0; i < innerWidth + 2; ++i) std::cout << "═";
            std::cout << "╗\n";
        } else {
            std::string paddedTitle = " " + title + " ";
            int totalPad = (innerWidth + 2) - paddedTitle.length();
            int leftPad = totalPad / 2;
            if (leftPad < 2) leftPad = 2; // Đảm bảo luôn có ít nhất 2 dấu gạch ở bên trái
            int rightPad = (innerWidth + 2) - paddedTitle.length() - leftPad;

            std::cout << "╔";
            for (int i = 0; i < leftPad; ++i) std::cout << "═";
            std::cout << paddedTitle;
            for (int i = 0; i < rightPad; ++i) std::cout << "═";
            std::cout << "╗\n";
        }

        // 2. Phân tích nội dung đa dòng (hỗ trợ '\n' và tự động xuống dòng nếu quá dài)
        size_t pos = 0;
        while (pos < content.length()) {
            size_t nextNewline = content.find('\n', pos);
            std::string line = (nextNewline == std::string::npos) 
                               ? content.substr(pos) 
                               : content.substr(pos, nextNewline - pos);

            // Cắt dòng nếu dòng đó dài hơn độ rộng chứa đựng
            do {
                std::string part = line.substr(0, innerWidth);
                std::cout << "║ " << part;
                for (int i = 0; i < innerWidth - (int)part.length(); ++i) {
                    std::cout << " ";
                }
                std::cout << " ║\n";

                if (line.length() > (size_t)innerWidth) {
                    line = line.substr(innerWidth);
                } else {
                    line = "";
                }
            } while (!line.empty());

            if (nextNewline == std::string::npos) break;
            pos = nextNewline + 1;
        }

        // 3. Vẽ cạnh dưới của hộp thoại (tăng thêm 2 ký tự để vừa khít với lề trống bên trong)
        std::cout << "╚";
        for (int i = 0; i < innerWidth + 2; ++i) std::cout << "═";
        std::cout << "╝\n";
    }

    std::string hpBar(int hp, int maxHp, int width) {
        if (maxHp <= 0) return "[]";
        if (hp < 0) hp = 0;
        if (hp > maxHp) hp = maxHp;

        int filled = (hp * width) / maxHp;
        // Đảm bảo nếu HP > 0 thì ít nhất có 1 vạch để tránh hiểu nhầm đã xỉu
        if (hp > 0 && filled == 0) filled = 1; 
        int empty = width - filled;

        std::string bar = "[";
        for (int i = 0; i < filled; ++i) bar += "#";
        for (int i = 0; i < empty; ++i) bar += ".";
        bar += "]";
        return bar;
    }
}
