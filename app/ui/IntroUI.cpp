#include "IntroUI.hpp"
#include "UI.hpp"
#include <iostream>
#include <iomanip>
#include <windows.h>

namespace IntroUI {

    void typeWrite(const std::string& text, int delayMs) {
        for (char c : text) {
            std::cout << c << std::flush;
            Sleep(delayMs);
        }
    }

    void typeWriteBox(const std::string& title, const std::string& content) {
        const int innerWidth = 38;

        // 1. Vẽ cạnh trên viền hộp thoại (tăng thêm 2 ký tự để vừa khít với lề trống bên trong)
        if (title.empty()) {
            std::cout << "╔";
            for (int i = 0; i < innerWidth + 2; ++i) std::cout << "═";
            std::cout << "╗\n";
        } else {
            std::string paddedTitle = " " + title + " ";
            int totalPad = (innerWidth + 2) - paddedTitle.length();
            int leftPad = totalPad / 2;
            if (leftPad < 2) leftPad = 2;
            int rightPad = (innerWidth + 2) - paddedTitle.length() - leftPad;

            std::cout << "╔";
            for (int i = 0; i < leftPad; ++i) std::cout << "═";
            std::cout << paddedTitle;
            for (int i = 0; i < rightPad; ++i) std::cout << "═";
            std::cout << "╗\n";
        }

        // 2. Chạy chữ typewriter đa dòng bên trong viền bảo đảm căn lề chuẩn
        size_t pos = 0;
        while (pos < content.length()) {
            size_t nextNewline = content.find('\n', pos);
            std::string line = (nextNewline == std::string::npos) 
                               ? content.substr(pos) 
                               : content.substr(pos, nextNewline - pos);

            do {
                std::string part = line.substr(0, innerWidth);
                std::cout << "║ " << std::flush;
                
                // Hiệu ứng chữ chạy cho phân đoạn này
                typeWrite(part, 15);

                // Điền khoảng trắng bù phần thiếu ngay lập tức (không chạy từ từ)
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

        // 3. Vẽ cạnh dưới viền hộp thoại (tăng thêm 2 ký tự để vừa khít với lề trống bên trong)
        std::cout << "╚";
        for (int i = 0; i < innerWidth + 2; ++i) std::cout << "═";
        std::cout << "╝\n";
    }

    void showTitleScreen() {
        UI::clearScreen();
        std::cout << "\n\n";
        std::cout << "        ╔══════════════════════════════════════╗\n";
        std::cout << "        ║            MONSTER QUEST             ║\n";
        std::cout << "        ║                v1.0                  ║\n";
        std::cout << "        ╚══════════════════════════════════════╝\n";
        std::cout << "\n";
        std::cout << "                   ,___,               \n";
        std::cout << "                   (o.o)   AN ADVENTURE\n";
        std::cout << "                   <| - |>  AWAITS YOU!\n";
        std::cout << "                    /   \\              \n";
        std::cout << "\n";
        std::cout << "             [ PRESS ENTER TO START GAME ]\n\n";
        
        std::string dummy;
        std::getline(std::cin, dummy); // Đọc toàn bộ dòng trống khi nhấn Enter
    }

    void showOakDialog() {
        UI::clearScreen();
        std::string dialog = 
            "\"In the world you are about to\n"
            " enter, you will embark on a grand\n"
            " adventure as the hero.\n\n"
            " Speak to people and gather hints\n"
            " from every source you find.\"";
        
        typeWriteBox("PROF. OAK", dialog);
        
        std::cout << "\n                  [ PRESS ENTER → ]";
        std::string dummy;
        std::getline(std::cin, dummy);
    }

    void showNameInput(Player& player) {
        UI::clearScreen();
        std::string question = 
            "\"But first — let's begin with your\n"
            " name. What is it?\"";
        
        typeWriteBox("PROF. OAK", question);
        
        while (true) {
            std::cout << "\n  > ";
            std::string rawName;
            std::getline(std::cin, rawName);
            
            // Xử lý loại bỏ khoảng trắng thừa đầu cuối
            size_t first = rawName.find_first_not_of(" \t\n\r");
            if (first == std::string::npos) {
                std::cout << "  Name cannot be empty! Please try again.\n";
                continue;
            }
            size_t last = rawName.find_last_not_of(" \t\n\r");
            player.name = rawName.substr(first, (last - first + 1));
            
            // Giới hạn độ dài tên để không bị bể viền UI
            if (player.name.length() > 20) {
                std::cout << "  Name is too long (Max 20 chars)! Try again.\n";
                continue;
            }
            break;
        }
    }

    void showStarterSelect(Player& player) {
        UI::clearScreen();
        std::string question = 
            "\"Choose your first partner, " + player.name + "!\"";
        
        typeWriteBox("PROF. OAK", question);
        
        std::cout << "\n";
        std::cout << " ┌──────────────────────────────────────┐\n";
        std::cout << " │  [1] Bulbasaur   Grass   HP:45       │\n";
        std::cout << " │  [2] Charmander  Fire    HP:39       │\n";
        std::cout << " │  [3] Squirtle    Water   HP:44       │\n";
        std::cout << " └──────────────────────────────────────┘\n";
        
        int choice = 0;
        std::string input;
        while (true) {
            std::cout << "\n  > ";
            std::getline(std::cin, input);
            
            // Trim
            size_t first = input.find_first_not_of(" \t\n\r");
            if (first != std::string::npos) {
                size_t last = input.find_last_not_of(" \t\n\r");
                input = input.substr(first, (last - first + 1));
            } else {
                input = "";
            }
            
            try {
                size_t pos = 0;
                choice = std::stoi(input, &pos);
                if (pos == input.length() && choice >= 1 && choice <= 3) {
                    break; // Thành công
                }
            } catch (...) {}
            
            std::cout << "  Invalid input. Please enter 1, 2, or 3.\n";
        }
        
        if (choice == 1) player.starterName = "Bulbasaur";
        else if (choice == 2) player.starterName = "Charmander";
        else if (choice == 3) player.starterName = "Squirtle";
        
        UI::clearScreen();
        std::string confirmation = 
            "Oak: \"Excellent! " + player.starterName + "\n"
            " is your new partner!\"\n\n"
            "\"Your journey begins now!\"";
        
        typeWriteBox("PROF. OAK", confirmation);
        
        std::cout << "\n             [ PRESS ENTER TO EMBARK... ]";
        std::getline(std::cin, input);
    }
}
