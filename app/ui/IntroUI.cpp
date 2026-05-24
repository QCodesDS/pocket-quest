#include "IntroUI.hpp"
#include "UI.hpp"
#include <iostream>
#include <iomanip>

#ifdef _WIN32
#include <windows.h>
#else
#include <chrono>
#include <thread>
#endif

namespace IntroUI
{

    void typeWrite(const std::string &text, int delayMs)
    {
        for (char c : text)
        {
            std::cout << c << std::flush;
#ifdef _WIN32
            Sleep(delayMs);
#else
            std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
#endif
        }
    }

    void typeWriteBox(const std::string &title, const std::string &content)
    {
        const int innerWidth = 90;

        // 1. Vẽ cạnh trên viền hộp thoại (tăng thêm 2 ký tự để vừa khít với lề trống bên trong)
        if (title.empty())
        {
            std::cout << "╔";
            for (int i = 0; i < innerWidth + 2; ++i)
                std::cout << "═";
            std::cout << "╗\n";
        }
        else
        {
            std::string paddedTitle = " " + title + " ";
            int totalPad = (innerWidth + 2) - paddedTitle.length();
            int leftPad = totalPad / 2;
            if (leftPad < 2)
                leftPad = 2;
            int rightPad = (innerWidth + 2) - paddedTitle.length() - leftPad;

            std::cout << "╔";
            for (int i = 0; i < leftPad; ++i)
                std::cout << "═";
            std::cout << paddedTitle;
            for (int i = 0; i < rightPad; ++i)
                std::cout << "═";
            std::cout << "╗\n";
        }

        // 2. Chạy chữ typewriter đa dòng bên trong viền bảo đảm căn lề chuẩn
        size_t pos = 0;
        while (pos < content.length())
        {
            size_t nextNewline = content.find('\n', pos);
            std::string line = (nextNewline == std::string::npos)
                                   ? content.substr(pos)
                                   : content.substr(pos, nextNewline - pos);

            do
            {
                std::string part = line.substr(0, innerWidth);
                std::cout << "║ " << std::flush;

                // Hiệu ứng chữ chạy cho phân đoạn này
                typeWrite(part, 30);

                // Điền khoảng trắng bù phần thiếu ngay lập tức (không chạy từ từ)
                for (int i = 0; i < innerWidth - (int)part.length(); ++i)
                {
                    std::cout << " ";
                }
                std::cout << " ║\n";

                if (line.length() > (size_t)innerWidth)
                {
                    line = line.substr(innerWidth);
                }
                else
                {
                    line = "";
                }
            } while (!line.empty());

            if (nextNewline == std::string::npos)
                break;
            pos = nextNewline + 1;
        }

        // 3. Vẽ cạnh dưới viền hộp thoại (tăng thêm 2 ký tự để vừa khít với lề trống bên trong)
        std::cout << "╚";
        for (int i = 0; i < innerWidth + 2; ++i)
            std::cout << "═";
        std::cout << "╝\n";
    }

    void showTitleScreen()
    {
        UI::clearScreen();
        std::cout << "\n";
        std::cout << R"(
                                                                                                       ████                      ████
    ██████╗  ██████╗ ██╗  ██╗███████╗███╗   ███╗ ██████╗ ███╗   ██╗                      ██      ████  ██  ██                    ██  ██
    ██╔══██╗██╔═══██╗██║ ██╔╝██╔════╝████╗ ████║██╔═══██╗████╗  ██║                    ██  ██  ██  ██  ██    ██                  ██    ██
    ██████╔╝██║   ██║█████╔╝ █████╗  ██╔████╔██║██║   ██║██╔██╗ ██║                    ██  ████    ██    ██  ██                    ██  ██
    ██╔═══╝ ██║   ██║██╔═██╗ ██╔══╝  ██║╚██╔╝██║██║   ██║██║╚██╗██║                  ██    ██      ██    ██    ████                ██    ██
    ██║     ╚██████╔╝██║  ██╗███████╗██║ ╚═╝ ██║╚██████╔╝██║ ╚████║                  ██          ██      ██        ██            ██      ██
    ╚═╝      ╚═════╝ ╚═╝  ╚═╝╚══════╝╚═╝     ╚═╝ ╚═════╝ ╚═╝  ╚═══╝              ████      ██    ██      ██          ████        ██    ██
                                                                               ██  ██    ██  ██  ██        ██            ██    ██      ██
                   ██████╗ ███████╗███╗  ██╗   ██╗                           ██    ██  ██    ██  ██      ██  ██            ██  ██      ██
                  ██╔════╝ ██╔════╝████╗ ██║   ██║                           ██  ██████    ██      ██    ██  ██            ██  ██        ██
                  ██║  ███╗█████╗  ██╔██╗██║   ██║                         ██              ██      ██  ██      ██      ██    ██  ██      ██
                  ██║   ██║██╔══╝  ██║╚████║   ██║                         ██            ██████    ████    ██  ██████    ██  ██  ██        ██
                  ╚██████╔╝███████╗██║ ╚███║   ██║                       ██                    ████      ██      ██  ██    ██    ██      ██
                   ╚═════╝ ╚══════╝╚═╝  ╚══╝   ╚═╝                       ██                                    ██      ██  ██  ██        ██
                                                                         ██        ██    ████              ██    ██    ██    ████        ██
             ██╗  ██╗ █████╗ ███╗  ██╗████████╗ ██████╗                ██        ██      ██  ██      ████    ██    ██    ██  ██  ██      ██
             ██╔═██╔╝██╔══██╗████╗ ██║╚══██╔══╝██╔═══██╗             ██                ██  ██  ██        ██    ████  ██  ██    ██  ██    ██
             █████╔╝ ███████║██╔██╗██║   ██║   ██║   ██║             ██            ████    ██  ██        ██        ████    ██  ██  ██  ██
             ██╔═██╗ ██╔══██║██║╚████║   ██║   ██║   ██║               ██      ████  ██      ██  ██  ████        ██  ████  ██  ████    ██
             ██║  ██╗██║  ██║██║ ╚███║   ██║   ╚██████╔╝                 ████  ██      ██████      ██          ██    ██  ██████      ██
             ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚══╝   ╚═╝    ╚═════╝                      ██            ██        ████    ██    ██              ██
                                                                                             ████████  ██████      ████        ████
                © 2026  POCKETRQUEST  —  DSA · HCMUS                                                     ██      ██    ████████
                                                                                                           ██████
                                                           [PRESS ENTER TO START]

    )"
                  << "\n";

        std::string dummy;
        std::getline(std::cin, dummy);
    }

    void showOpeningStory()
    {
        UI::clearScreen();
        std::string story =
            "In the world which you are about to enter, you will embark on a grand adventure with you\n"
            "as the hero.\n"
            "\n\n"
            "Speak to people and check things everywhere you go, be it towns, roads, or caves. Gather\n"
            "information and hints from every source.\n"
            "\n\n"
            "New paths will open to you by helping people in need, overcoming challenges, and solving\n"
            "mysteries.\n"
            "\n\n"
            "At times, you will be challenged by others and attacked by wild creatures. Be brave and\n"
            "keep pushing on.\n"
            "\n\n"
            "Through your adventure, we hope that you will interact with all sorts of people and\n"
            "achieve personal growth. That is our biggest objective.\n"
            "\n\n"
            "Press Enter, and let your adventure begin!";

        typeWriteBox("", story);

        std::cout << "                                                                            [Press Enter...]";
        std::string dummy;
        std::getline(std::cin, dummy);
    }

    void showOakDialog()
    {
        UI::clearScreen();
        std::string dialog =
            "Hello, there! Glad to meet you! Welcome to the world of POKEMON!\n"
            "\n\n"
            "My name is OAK. People affectionately refer to me as the POKEMON PROFESSOR.\n"
            "\n\n"
            "This world... is inhabited far and wide by creatures called POKEMON.\n"
            "\n\n"
            "For some people, POKEMON are pets. Others use them for battling.\n"
            "\n\n"
            "As for myself... I study POKEMON as a profession.\n";

        typeWriteBox("PROF. OAK", dialog);

        std::cout << "                                                                            [Press Enter...]";
        std::string dummy;
        std::getline(std::cin, dummy);
    }

    void showNameInput(Player &player)
    {
        UI::clearScreen();
        std::string question =
            "But first, tell me a little about yourself.\n"
            "Let's begin with your name. What is it? (Max 8 letters):";

        typeWriteBox("PROF. OAK", question);

        while (true)
        {
            std::cout << " > ";
            std::string rawName;
            std::getline(std::cin, rawName);

            // Xử lý loại bỏ khoảng trắng thừa đầu cuối
            size_t first = rawName.find_first_not_of(" \t\n\r");
            if (first == std::string::npos)
            {
                std::cout << "  Name cannot be empty! Please try again.\n";
                continue;
            }
            size_t last = rawName.find_last_not_of(" \t\n\r");
            player.name = rawName.substr(first, (last - first + 1));

            // Nếu tên sau khi cắt khoảng trắng vẫn dài hơn 8 ký tự, tự động lấy 8 ký tự đầu
            if (player.name.length() > 8)
            {
                player.name = player.name.substr(0, 8);
            }
            break; // Thoát vòng lặp ngay vì tên đã hợp lệ và được xử lý xong
        }
    }

    void showStarterSelect(Player &player)
    {
        UI::clearScreen();
        std::string haveName =
            "Right... So your name is " + player.name + ".\n"
                                                        "\n\n"
                                                        "Your very own POKEMON legend is about to unfold!\n"
                                                        "\n\n"
                                                        "A world of dreams and adventures with POKEMON awaits! Let's go!\n";

        typeWriteBox("PROF. OAK", haveName);
        std::cout << "                                                                            [Press Enter...]";
        std::string dummy;
        std::getline(std::cin, dummy);

        UI::clearScreen();
        std::string question =
            "You need your own POKEMON for your protection.\n"
            "\n\n"
            "You can have one. Go on, choose!\n";

        typeWriteBox("PROF. OAK", question);

        std::cout << "\n";
        std::cout << " ┌────────────────────────────────────────────────────────────────────────────────────┐\n";
        std::cout << " │  [1] Bulbasaur   [Grass]   HP:45 | Att:49 | S.Att:65 | Def:49 | S.Def:65 | Spd: 45 │\n";
        std::cout << " │                  [Poison]                                                          │\n";
        std::cout << " │                                                                                    │\n";
        std::cout << " │  [2] Squirtle    [Water]   HP:44 | Att:48 | S.Att:50 | Def:65 | S.Def:64 | Spd: 43 │\n";
        std::cout << " │                                                                                    │\n";
        std::cout << " │  [3] Charmander  [Fire]    HP:39 | Att:52 | S.Att:60 | Def:43 | S.Def:50 | Spd: 65 │\n";
        std::cout << " └────────────────────────────────────────────────────────────────────────────────────┘\n";

        int choice = 0;
        std::string input;
        while (true)
        {
            std::cout << "\n  > ";
            std::getline(std::cin, input);

            // Trim
            size_t first = input.find_first_not_of(" \t\n\r");
            if (first != std::string::npos)
            {
                size_t last = input.find_last_not_of(" \t\n\r");
                input = input.substr(first, (last - first + 1));
            }
            else
            {
                input = "";
            }

            try
            {
                size_t pos = 0;
                choice = std::stoi(input, &pos);
                if (pos == input.length() && choice >= 1 && choice <= 3)
                {
                    break; // Thành công
                }
            }
            catch (...)
            {
            }

            std::cout << "  Invalid input. Please enter 1, 2, or 3.\n";
        }

        if (choice == 1)
            player.starterName = "Bulbasaur";
        else if (choice == 2)
            player.starterName = "Squirtle";
        else if (choice == 3)
            player.starterName = "Charmander";

        UI::clearScreen();
        std::string confirmation =
            "Oak: \"Excellent! " + player.starterName + "\n"
                                                        " is your new partner!\"\n\n"
                                                        "\"Your journey begins now!\"";

        typeWriteBox("PROF. OAK", confirmation);

        std::cout << "                                                                            [Press Enter...]";
        std::getline(std::cin, input);
    }
}
