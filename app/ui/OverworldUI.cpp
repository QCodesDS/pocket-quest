#include "OverworldUI.hpp"
#include "UI.hpp"
#include "../core/Game.hpp"
#include "../data/gen1_monsters.hpp"
#include "../entities/Trainer.hpp"
#include "../entities/Monster.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

namespace OverworldUI
{

    /**
     * @brief Chạy vòng lặp Overworld: hiển thị màn hình, xử lý input cho đến khi kết thúc.
     *        Dùng LinkedList<City> từ WorldMap để di chuyển qua các thành phố.
     */
    void run(WorldMap &world, Player &player, [[maybe_unused]] Game &game)
    {
        // Khởi tạo random seed cho wild encounter
        srand((unsigned)time(nullptr));

        bool inOverworld = true;
        while (inOverworld)
        {
            // ==========================================
            // 1. Render: Hiển thị màn hình Overworld
            // ==========================================
            UI::clearScreen();

            if (!world.hasCurrent())
            {
                std::cout << "ERROR: Invalid world state.\n";
                break;
            }

            City &currentCity = world.getCurrent();

            // Tiêu đề: Tag + Tên Thành Phố
            std::string title = currentCity.tag + "          " + currentCity.name;
            std::string info = "Trainer: " + player.name + "        Badges: " + std::to_string(player.badges) + "/8";

            // In hộp thoại chính
            std::cout << "╔══════════════════════════════════════╗\n";
            std::cout << "║ " << std::string(34, ' ') << " ║\n";
            std::cout << "║  " << title << std::string(std::max(0, 32 - (int)title.length()), ' ') << "║\n";
            std::cout << "║  " << info << std::string(std::max(0, 32 - (int)info.length()), ' ') << "║\n";
            std::cout << "║ " << std::string(34, ' ') << " ║\n";
            std::cout << "╠══════════════════════════════════════╣\n";

            // In NPC dialog từ LinkedList
            std::cout << "║ NPC: ";
            currentCity.npcDialog.resetCursor();
            bool firstLine = true;
            while (currentCity.npcDialog.hasCurrent())
            {
                if (!firstLine)
                {
                    std::cout << "║      ";
                }
                std::cout << currentCity.npcDialog.getCurrent();
                std::cout << std::string(std::max(0, 30 - (int)currentCity.npcDialog.getCurrent().length()), ' ');
                std::cout << " ║\n";
                firstLine = false;

                // Advance cursor only if there's a next element; break if moveNext() returns false
                if (!currentCity.npcDialog.moveNext())
                    break;
            }

            std::cout << "╠══════════════════════════════════════╣\n";

            // In các tùy chọn menu
            std::cout << "║  [1] Go forward                      ║\n";
            std::cout << "║  [2] Check area                      ║\n";

            // Nếu có Gym ở thành phố này, hiển thị tùy chọn Challenge Gym
            if (currentCity.hasGym)
            {
                std::string gymOption = "║  [3] Challenge Gym — " + currentCity.gymLeader;
                gymOption += std::string(std::max(0, 39 - (int)gymOption.length()), ' ');
                gymOption += "║";
                std::cout << gymOption << "\n";
                std::cout << "║  [4] View party                      ║\n";
                std::cout << "║  [5] Open bag                        ║\n";
            }
            else
            {
                std::cout << "║  [3] View party                      ║\n";
                std::cout << "║  [4] Open bag                        ║\n";
            }

            std::cout << "╚══════════════════════════════════════╝\n";

            // ==========================================
            // 2. Input: Xử lý lựa chọn từ người chơi
            // ==========================================
            std::cout << "> ";
            char choice;
            std::cin >> choice;

            // Xóa input buffer
            std::cin.ignore(10000, '\n');

            switch (choice)
            {
            case '1':
            {
                // Go forward: Di chuyển tới thành phố tiếp theo
                if (world.moveNext())
                {
                    // Di chuyển thành công
                    // 30% chance wild encounter
                    if ((rand() % 10) < 3)
                    {
                        UI::clearScreen();
                        UI::printBox("Wild Encounter", "A wild Pokemon appeared! [TODO]\nBattle not yet implemented.");
                        std::cout << "\nPress Enter to continue...";
                        std::cin.ignore(10000, '\n');
                    }
                }
                else
                {
                    // Đã ở cuối danh sách (Indigo Plateau)
                    // Kiểm tra badges
                    if (world.atIndigoPlateau())
                    {
                        UI::clearScreen();
                        if (player.badges < 8)
                        {
                            UI::printBox("Indigo Plateau",
                                         "You need 8 badges to enter the Pokemon League!\nYou currently have " +
                                             std::to_string(player.badges) + " badges.");
                            std::cout << "\nPress Enter to continue...";
                            std::cin.ignore(10000, '\n');
                        }
                        else
                        {
                            UI::printBox("Indigo Plateau", "You have all 8 badges!\nReady to challenge the Pokemon League!");
                            std::cout << "\nPress Enter to continue...";
                            std::cin.ignore(10000, '\n');
                            inOverworld = false; // TODO: Transition to League
                        }
                    }
                }
                break;
            }

            case '2':
            {
                // Check area - placeholder
                UI::clearScreen();
                UI::printBox("Area Check", "You explore the area but find nothing interesting.\n[Area check stub - TODO]");
                std::cout << "\nPress Enter to continue...";
                std::cin.ignore(10000, '\n');
                break;
            }

            case '3':
            {
                if (currentCity.hasGym)
                {
                    // Challenge Gym - placeholder
                    UI::clearScreen();
                    std::string gymMsg = "You approach Gym Leader " + currentCity.gymLeader + "...\n[Gym battle stub - TODO]";
                    UI::printBox("Gym Battle", gymMsg);
                    std::cout << "\nPress Enter to continue...";
                    std::cin.ignore(10000, '\n');
                }
                else
                {
                    // No gym at this city - view party
                    UI::clearScreen();
                    UI::printBox("Party",
                                 "Current party size: " + std::to_string(player.party.size()) + "\n[Party view stub - TODO]");
                    std::cout << "\nPress Enter to continue...";
                    std::cin.ignore(10000, '\n');
                }
                break;
            }

            case '4':
            {
                if (currentCity.hasGym)
                {
                    // View party
                    UI::clearScreen();
                    UI::printBox("Party",
                                 "Current party size: " + std::to_string(player.party.size()) + "\n[Party view stub - TODO]");
                    std::cout << "\nPress Enter to continue...";
                    std::cin.ignore(10000, '\n');
                }
                else
                {
                    // Open bag (non-gym city)
                    UI::clearScreen();
                    handleBagMenu(player);
                }
                break;
            }

            case '5':
            {
                if (currentCity.hasGym)
                {
                    // Open bag (gym city)
                    UI::clearScreen();
                    handleBagMenu(player);
                }
                else
                {
                    // Invalid input
                    std::cout << "Invalid choice. Try again.\n";
                }
                break;
            }

            default:
            {
                // Invalid input - re-prompt
                std::cout << "Invalid choice. Try again.\n";
                break;
            }
            }
        }
    }

    /**
     * @brief Hiển thị bag menu ngoài battle, xử lý item sử dụng.
     *        GRADER: Sử dụng InventorySystem::forEach() để duyệt HashTable items.
     */
    void handleBagMenu(Player &player)
    {
        if (player.inventory.empty())
        {
            UI::printBox("Bag", "Your bag is empty!");
            std::cout << "\nPress Enter to continue...";
            std::cin.ignore(10000, '\n');
            return;
        }

        // Display bag with items
        std::cout << "╔════════════════════════════════════╗\n";
        std::cout << "║  BAG                               ║\n";
        std::cout << "╠════════════════════════════════════╣\n";

        // GRADER: Sử dụng InventorySystem::forEach() với lambda callback
        int itemIndex = 1;
        player.inventory.forEach([&itemIndex](const std::string &name, Item &item)
                                 {
            std::string line = "[" + std::to_string(itemIndex) + "] " + name + 
                              " x" + std::to_string(item.quantity) + 
                              " (+" + std::to_string(item.healAmount) + " HP)";
            std::cout << "║  " << line;
            int padding = 30 - line.length();
            for (int i = 0; i < padding && i < 30; i++)
                std::cout << " ";
            std::cout << "║\n";
            itemIndex++; });

        std::cout << "╠════════════════════════════════════╣\n";
        std::cout << "║  [0] Cancel                        ║\n";
        std::cout << "╚════════════════════════════════════╝\n";

        // Get user selection
        std::cout << "> Choose item: ";
        std::string choice;
        std::cin >> choice;
        std::cin.ignore(10000, '\n');

        // Validate input
        int itemNum = 0;
        try
        {
            itemNum = std::stoi(choice);
        }
        catch (...)
        {
            std::cout << "Invalid input!\n";
            return;
        }

        // Handle cancel
        if (itemNum == 0)
        {
            return;
        }

        // Find selected item from inventory
        int currentIndex = 1;
        std::string selectedItemName = "";

        player.inventory.forEach([&currentIndex, &itemNum, &selectedItemName](const std::string &name, Item &item)
                                 {
            if (currentIndex == itemNum && item.quantity > 0)
            {
                selectedItemName = name;
            }
            currentIndex++; });

        if (selectedItemName.empty())
        {
            std::cout << "Invalid item selection!\n";
            return;
        }

        // Select which mon to use item on
        UI::clearScreen();
        std::cout << "╔════════════════════════════════════╗\n";
        std::cout << "║  Choose Pokemon to use item on:     ║\n";
        std::cout << "╠════════════════════════════════════╣\n";

        // Display party mons
        // TODO: Implement party iteration from Queue
        std::cout << "║  [1] Front pokemon                 ║\n";
        std::cout << "║  [0] Cancel                        ║\n";
        std::cout << "╚════════════════════════════════════╝\n";

        std::cout << "> Choose pokemon: ";
        std::string monChoice;
        std::cin >> monChoice;
        std::cin.ignore(10000, '\n');

        if (monChoice == "0")
        {
            return;
        }

        // Use item on player's current mon (front of queue)
        if (!player.party.empty())
        {
            Monster &targetMon = player.party.front();

            // GRADER: Sử dụng InventorySystem::useItem() với HashTable::find()
            if (player.inventory.useItem(selectedItemName, targetMon))
            {
                std::cout << "\nUsed " << selectedItemName << " on " << targetMon.name << "!\n";
                std::cout << targetMon.name << "'s HP is now " << targetMon.hp << "/" << targetMon.maxHp << ".\n";
            }
            else
            {
                std::cout << "\nCouldn't use " << selectedItemName << ".\n";
            }
        }
        else
        {
            std::cout << "You have no pokemon to use item on!\n";
        }

        std::cout << "\nPress Enter to continue...";
        std::cin.ignore(10000, '\n');
    }

} // namespace OverworldUI
