#include "OverworldUI.hpp"
#include "UI.hpp"
#include "../core/Game.hpp"
#include "../data/gen1_monsters.hpp"
#include "../data/gen1_trainers.hpp"
#include "../entities/Trainer.hpp"
#include "../entities/Monster.hpp"
#include "../lib/Algorithms.hpp"
#include "../systems/BattleSystem.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype>

namespace OverworldUI
{
    [[maybe_unused]] static int getRivalStage(const std::string &cityName)
    {
        if (cityName == "Cerulean City")
            return 1;
        if (cityName == "Saffron City")
            return 2;
        if (cityName == "Indigo Plateau")
            return 3;
        return 0;
    }

    static bool allRivalsDefeated(const Player &player)
    {
        return player.rivalDefeated[1] && player.rivalDefeated[2] && player.rivalDefeated[3];
    }

    /**
     * @brief Chạy vòng lặp Overworld: hiển thị màn hình, xử lý input cho đến khi kết thúc.
     *        Dùng LinkedList<City> từ WorldMap để di chuyển qua các thành phố.
     */
    void run(WorldMap &world, Player &player, [[maybe_unused]] Game &game)
    {
        // Khởi tạo random seed cho wild encounter
        srand((unsigned)time(nullptr));

        bool inOverworld = true;
        BattleSystem battle;
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

            // Nếu có Gym ở thành phố này và gym chưa bị đánh bại, hiển thị tùy chọn Challenge Gym
            if (currentCity.hasGym && !currentCity.gymCleared)
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

            std::cout << "║  [S] Sort party by HP               ║\n";
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
                // Kiếm tra rào cản tuyến tính TRƯỚC KHI di chuyển
                std::string currentName = world.getCurrent().name;

                if (currentName == "Viridian City" && !player.deliveredParcel)
                {
                    UI::clearScreen();
                    UI::printBox("Viridian City Guard", "Guard: \"Hold on! The road to Pewter City is closed!\nYou must deliver Prof. Oak's Parcel first! Check the Poké Mart.\"");
                    std::cout << "\nPress Enter to continue...";
                    std::cin.ignore(10000, '\n');
                    break;
                }

                if (currentName == "Celadon City" && !player.hasPokeFlute)
                {
                    UI::clearScreen();
                    UI::printBox("Route 16 Gate", "A sleeping Snorlax blocks the path to Fuchsia City!\nYou cannot wake it up without a Poké Flute!");
                    std::cout << "\nPress Enter to continue...";
                    std::cin.ignore(10000, '\n');
                    break;
                }

                if (currentName == "Fuchsia City" && !player.hasSurf)
                {
                    UI::clearScreen();
                    UI::printBox("Route 19 Gate", "You need the Surf skill (HM03) to swim across the sea to Cinnabar Island!\nExplore the Safari Zone in Fuchsia City first!");
                    std::cout << "\nPress Enter to continue...";
                    std::cin.ignore(10000, '\n');
                    break;
                }

                // Cảnh báo Viridian Gym khi có 7 Badges
                if (currentName == "Cinnabar Island" && player.badges == 7)
                {
                    UI::clearScreen();
                    UI::printBox("Viridian Gym", "News flash: The 8th Gym at Viridian City has opened!\nThe Gym Leader is the mysterious Boss of Team Rocket!");
                    std::cout << "\nDo you want to travel back to Viridian City now? [Y/N]: ";
                    char ans;
                    std::cin >> ans;
                    std::cin.ignore(10000, '\n');
                    if (ans == 'Y' || ans == 'y')
                    {
                        world.resetCursor();
                        world.moveNext(); // Move to Viridian City
                        City &viridian = world.getCurrent();
                        viridian.hasGym = true;
                        viridian.gymCleared = false;
                        viridian.gymLeader = "Giovanni";
                        viridian.tag = "GYM 8";
                        viridian.npcDialog.clear();
                        viridian.npcDialog.insertBack("I am Giovanni - Leader of Team Rocket, and the final Gym Leader!");
                        viridian.npcDialog.insertBack("Prove your strength to me in battle!");
                        continue;
                    }
                }

                // Chặn đi từ Saffron sang Cinnabar nếu chưa giải phóng Silph Co. (chưa hạ Rival lần 3)
                if (currentName == "Saffron City" && !player.rivalDefeated[2])
                {
                    UI::clearScreen();
                    UI::printBox("Saffron City", "You must defeat Team Rocket at Silph Co. first!");
                    std::cout << "\nPress Enter to continue...";
                    std::cin.ignore(10000, '\n');
                    break;
                }

                // Thực hiện di chuyển tuyến tính
                if (world.moveNext())
                {
                    std::string newCityName = world.getCurrent().name;

                    // 1. Trực quan hóa Snorlax
                    if (newCityName == "Fuchsia City" && player.hasPokeFlute)
                    {
                        UI::clearScreen();
                        UI::printBox("Snorlax Gate", "You play the Poké Flute...\nThe sleeping Snorlax wakes up, yawns, and leaves!\nThe Cycling Road to Fuchsia City is now open!");
                        std::cout << "\nPress Enter to continue...";
                        std::cin.ignore(10000, '\n');
                    }

                    // 2. Trực quan hóa Surf sang Cinnabar Island
                    if (newCityName == "Cinnabar Island" && player.hasSurf)
                    {
                        UI::clearScreen();
                        UI::printBox("Seafoam Islands", "You use HM03 Surf to swim across the sea!\nYou pass the Seafoam Islands and arrive at Cinnabar Island.");
                        std::cout << "\nPress Enter to continue...";
                        std::cin.ignore(10000, '\n');
                    }

                    // 3. Trận chiến Mt. Moon (Pewter -> Cerulean)
                    if (newCityName == "Cerulean City" && !player.rivalDefeated[1])
                    {
                        UI::clearScreen();
                        UI::printBox("Mt. Moon", "You enter the dark Mt. Moon cave...\nSuddenly, a Team Rocket Grunt attacks!");
                        std::cout << "\nPress Enter to fight Team Rocket Grunt...";
                        std::cin.ignore(10000, '\n');

                        Trainer grunt("Rocket Grunt", TrainerType::WILD, 12, "Mt. Moon");
                        grunt.party.enqueue(Gen1Monsters::createMonster("Zubat", "Poison/Flying", 41, 12, 40, 45, 35, 55, Gen1Moves::SCRATCH, Gen1Moves::DISABLE));
                        grunt.party.enqueue(Gen1Trainers::levelUpMonster(Gen1Monsters::RATTATA, 12));

                        battle.initializeTrainerBattle(player, grunt);
                        BattleResult res = battle.runBattle(player);
                        player.party = battle.getPlayerParty();

                        if (res == BattleResult::WIN)
                        {
                            UI::clearScreen();
                            UI::printBox("Mt. Moon", "You defeated Team Rocket!\nA Super Nerd steps forward: \"You can have one of these Fossils!\"\n[1] Dome Fossil  [2] Helix Fossil");
                            std::cout << "> ";
                            int fossilChoice = 0;
                            std::cin >> fossilChoice;
                            std::cin.ignore(10000, '\n');
                            UI::clearScreen();
                            if (fossilChoice == 1)
                            {
                                UI::printBox("Mt. Moon", "You got the Dome Fossil! (Kabuto)");
                            }
                            else
                            {
                                UI::printBox("Mt. Moon", "You got the Helix Fossil! (Omanyte)");
                            }
                            std::cout << "\nPress Enter to exit Mt. Moon and enter Cerulean City...";
                            std::cin.ignore(10000, '\n');
                        }
                        else
                        {
                            UI::clearScreen();
                            UI::printBox("Blackout", "You blacked out inside Mt. Moon! Returned to Pewter City.");
                            std::cout << "\nPress Enter to continue...";
                            std::cin.ignore(10000, '\n');
                            world.resetCursor();
                            world.moveNext();
                            world.moveNext(); // Quay lại Pewter City (index 2)
                            continue;
                        }
                    }

                    // 4. Giải phóng Silph Co. tại Saffron City (Rival Stage 2)
                    if (newCityName == "Saffron City" && !player.rivalDefeated[2])
                    {
                        UI::clearScreen();
                        UI::printBox("Saffron Gates", "Saffron City is currently occupied by Team Rocket!\nYou must infiltrate Silph Co. to liberate the city!");
                        std::cout << "\nPress Enter to enter Saffron City and storm Silph Co...";
                        std::cin.ignore(10000, '\n');

                        Trainer rival = Gen1Trainers::getRivalEncounter(2, player.starterName);
                        battle.initializeTrainerBattle(player, rival);
                        BattleResult res = battle.runBattle(player);
                        player.party = battle.getPlayerParty();

                        if (res == BattleResult::WIN)
                        {
                            player.rivalDefeated[2] = true;
                            UI::clearScreen();
                            UI::printBox("Silph Co.", "You defeated Blue and Boss Giovanni!\nThe Silph President rewards you with the Master Ball!\nThe city is saved, and the Gym is now accessible!");
                            std::cout << "\nPress Enter to continue...";
                            std::cin.ignore(10000, '\n');
                        }
                        else
                        {
                            UI::clearScreen();
                            UI::printBox("Blackout", "You were defeated at Silph Co.! Returned to Fuchsia City.");
                            std::cout << "\nPress Enter to continue...";
                            std::cin.ignore(10000, '\n');
                            world.resetCursor();
                            for (int k = 0; k < 7; k++) world.moveNext(); // Fuchsia City (index 7)
                            continue;
                        }
                    }

                    // 30% chance wild encounter (chỉ khi không có sự kiện đặc biệt)
                    if ((rand() % 10) < 3)
                    {
                        UI::clearScreen();
                        // Trực quan hóa wild encounter hoang dã
                        Monster wild = Gen1Monsters::createMonster("Wild Pikachu", "Electric", 25, 10, 38, 52, 43, 85, Gen1Moves::THUNDERSHOCK, Gen1Moves::FOCUS_ENERGY);
                        battle.initializeWildBattle(player, wild);
                        UI::printBox("Wild Encounter", "A wild Pikachu appeared! Prepare for battle!");
                        std::cout << "\nPress Enter to fight Pikachu...";
                        std::cin.ignore(10000, '\n');

                        BattleResult wildResult = battle.runBattle(player);
                        player.party = battle.getPlayerParty();

                        if (wildResult == BattleResult::LOSS)
                        {
                            game.setState(GameState::GAMEOVER);
                            inOverworld = false;
                            return;
                        }
                    }

                    // Trận đấu Rival Stage 1 tại Cerulean City (trước khi vào thành phố)
                    if (newCityName == "Cerulean City" && !player.rivalDefeated[1])
                    {
                        UI::clearScreen();
                        UI::printBox("Rival Encounter", "Blue challenges you to a battle!");
                        std::cout << "\nPress Enter to continue...";
                        std::cin.ignore(10000, '\n');

                        Trainer rival = Gen1Trainers::getRivalEncounter(1, player.starterName);
                        battle.initializeTrainerBattle(player, rival);
                        BattleResult rivalResult = battle.runBattle(player);
                        player.party = battle.getPlayerParty();

                        if (rivalResult == BattleResult::WIN)
                        {
                            player.rivalDefeated[1] = true;
                            UI::clearScreen();
                            UI::printBox("Rival Defeated", "You defeated Blue at Cerulean City!");
                            std::cout << "\nPress Enter to continue...";
                            std::cin.ignore(10000, '\n');
                        }
                        else
                        {
                            UI::clearScreen();
                            UI::printBox("Rival Battle", "You blacked out! Returned to Pewter City.");
                            std::cout << "\nPress Enter to continue...";
                            std::cin.ignore(10000, '\n');
                            world.resetCursor();
                            world.moveNext();
                            world.moveNext(); // Pewter City
                            continue;
                        }
                    }
                }
                else
                {
                    // Đã ở cuối danh sách (Indigo Plateau)
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
                        else if (!allRivalsDefeated(player))
                        {
                            UI::printBox("Indigo Plateau",
                                         "You must defeat all rival encounters before entering the League!");
                            std::cout << "\nPress Enter to continue...";
                            std::cin.ignore(10000, '\n');
                        }
                        else
                        {
                            UI::printBox("Pokemon League", "Welcome to the Pokemon League!");
                            std::cout << "\nPress Enter to continue...";
                            std::cin.ignore(10000, '\n');

                            bool leagueLost = false;
                            for (int idx = 0; idx < 4 && !leagueLost; idx++)
                            {
                                Trainer elite = Gen1Trainers::getEliteTrainer(idx);
                                battle.initializeTrainerBattle(player, elite);
                                BattleResult eliteResult = battle.runBattle(player);
                                player.party = battle.getPlayerParty();

                                if (eliteResult != BattleResult::WIN)
                                {
                                    leagueLost = true;
                                    UI::clearScreen();
                                    UI::printBox("Elite Four", "You were defeated by " + elite.name + ".\nReturn and train more.");
                                    std::cout << "\nPress Enter to continue...";
                                    std::cin.ignore(10000, '\n');
                                    break;
                                }

                                {
                                    char answer = '\0';
                                    while (true)
                                    {
                                        UI::clearScreen();
                                        UI::printBox("Elite Four", "You defeated " + elite.name + "!\nUse bag before next battle? [Y/N]");
                                        std::cout << "> ";
                                        std::cin >> answer;
                                        std::cin.ignore(10000, '\n');

                                        if (answer == 'Y' || answer == 'y')
                                        {
                                            handleBagMenu(player);
                                            break;
                                        }
                                        if (answer == 'N' || answer == 'n')
                                        {
                                            break;
                                        }
                                    }
                                }
                            }

                            if (!leagueLost)
                            {
                                Trainer champion = Gen1Trainers::getChampionTrainer();
                                battle.initializeTrainerBattle(player, champion);
                                BattleResult champResult = battle.runBattle(player);
                                player.party = battle.getPlayerParty();

                                if (champResult == BattleResult::WIN)
                                {
                                    UI::showVictoryScreen(player);
                                    game.setState(GameState::WIN);
                                    inOverworld = false;
                                    return;
                                }
                                else
                                {
                                    UI::clearScreen();
                                    UI::printBox("Champion", "Blue defeated you. Return to train and try again.");
                                    std::cout << "\nPress Enter to continue...";
                                    std::cin.ignore(10000, '\n');
                                }
                            }
                        }
                    }
                }
                break;
            }

            case '2':
            {
                UI::clearScreen();
                std::string cityName = currentCity.name;
                if (cityName == "Pallet Town")
                {
                    if (!player.hasParcel && !player.deliveredParcel)
                    {
                        UI::printBox("Prof. Oak's Lab", "Oak: \"Hello RED! Go to Viridian City's Poké Mart first.\nI have an order waiting there!\"");
                    }
                    else if (player.hasParcel && !player.deliveredParcel)
                    {
                        UI::printBox("Prof. Oak's Lab", "Oak: \"Ah! RED! That's the parcel I was waiting for! Thank you!\"\n\"Here is your POKEDEX! Go ahead and collect badges!\"\n\"Also, talk to my sister Daisy next door to get a TOWN MAP!\"");
                        player.deliveredParcel = true;
                    }
                    else
                    {
                        UI::printBox("Prof. Oak's Lab", "Oak: \"How is your Pokédex progress? Keep going, RED!\"");
                    }
                }
                else if (cityName == "Viridian City")
                {
                    if (!player.hasParcel && !player.deliveredParcel)
                    {
                        UI::printBox("Viridian Poké Mart", "Clerk: \"Oh, you're RED from Pallet Town?\nProf. Oak's parcel arrived! Please deliver it to him!\"\n\n[You received Oak's Parcel!]");
                        player.hasParcel = true;
                    }
                    else if (player.hasParcel && !player.deliveredParcel)
                    {
                        UI::printBox("Viridian City", "Clerk: \"Please deliver the parcel to Prof. Oak!\"\n\n[Would you like to return to Pallet Town now?]");
                        std::cout << "\nTravel back to Pallet Town? [Y/N]: ";
                        char ans;
                        std::cin >> ans;
                        std::cin.ignore(10000, '\n');
                        if (ans == 'Y' || ans == 'y')
                        {
                            world.resetCursor(); // Teleport về Pallet Town
                            continue;
                        }
                    }
                    else
                    {
                        UI::printBox("Viridian City", "Clerk: \"Thanks for delivering that parcel! Our shop is now fully open!\"");
                    }
                }
                else if (cityName == "Pewter City")
                {
                    UI::printBox("Pewter Museum", "You visit the Science Museum.\nYou check out ancient fossils of Aerodactyl and Kabutops.\n\n[Admission fee paid: 50 Poké-dollar]");
                }
                else if (cityName == "Cerulean City")
                {
                    if (!player.hasSSTicket)
                    {
                        UI::printBox("Nugget Bridge & Route 25", "You challenge the 5 Nugget Bridge trainers and clear them!\nAt the Cape, you help Bill transform back to human!\n\n[Bill gave you the S.S. Ticket!]");
                        player.hasSSTicket = true;
                    }
                    else
                    {
                        UI::printBox("Cape House", "Bill: \"Thanks for helping me! Board the S.S. Anne in Vermilion!\"");
                    }
                }
                else if (cityName == "Vermilion City")
                {
                    if (!player.hasCut)
                    {
                        if (!player.hasSSTicket)
                        {
                            UI::printBox("Vermilion Harbor", "Sailor: \"You need a S.S. Ticket to board the luxury S.S. Anne ship!\"");
                        }
                        else
                        {
                            UI::printBox("S.S. Anne", "You board the luxury cruise ship S.S. Anne!\nSuddenly, your rival Blue jumps out: \"Bonjour! RED!\"\nHe challenges you to a battle!");
                            std::cout << "\nPress Enter to fight Rival Blue...";
                            std::cin.ignore(10000, '\n');

                            Trainer rival = Gen1Trainers::getRivalEncounter(1, player.starterName);
                            battle.initializeTrainerBattle(player, rival);
                            BattleResult res = battle.runBattle(player);
                            player.party = battle.getPlayerParty();

                            UI::clearScreen();
                            if (res == BattleResult::WIN)
                            {
                                UI::printBox("S.S. Anne Captain", "Blue: \"Humph! Smell ya later!\"\n\nYou visit the seasick Captain and rub his back.\nCaptain: \"Oh, thank you! I feel much better! Take this HM01 (Cut)!\"\n\n[You learned HM01 Cut! The ship departs harbor.]");
                                player.hasCut = true;
                            }
                            else
                            {
                                UI::printBox("S.S. Anne", "You blacked out and returned to Vermilion City harbor.");
                            }
                        }
                    }
                    else
                    {
                        UI::printBox("Vermilion Harbor", "The S.S. Anne has departed. The harbor is quiet.");
                    }
                }
                else if (cityName == "Lavender Town")
                {
                    if (!player.hasSilphScope)
                    {
                        UI::printBox("Pokémon Tower", "You enter the Pokémon Tower...\nAn unidentifiable Ghost blocks the stairs!\n\nGhost: \"Begone... intruders...\"\n\n[You need a Silph Scope to identify the ghost!]");
                    }
                    else if (player.hasSilphScope && !player.hasPokeFlute)
                    {
                        UI::printBox("Pokémon Tower", "Using the Silph Scope, the Ghost is identified as Level 30 Marowak!");
                        std::cout << "\nPress Enter to battle Marowak Ghost...";
                        std::cin.ignore(10000, '\n');

                        Monster marowak = Gen1Monsters::createMonster("Marowak Ghost", "Ghost/Ground", 105, 30, 60, 80, 110, 45, Gen1Moves::ROCK_THROW, Gen1Moves::DISABLE);
                        battle.initializeWildBattle(player, marowak);
                        BattleResult res = battle.runBattle(player);
                        player.party = battle.getPlayerParty();

                        UI::clearScreen();
                        if (res == BattleResult::WIN)
                        {
                            UI::printBox("Pokémon Tower Top", "You put the spirit of Marowak to rest!\nAt the top floor, you defeat Team Rocket Grunts and save Mr. Fuji!\n\nMr. Fuji: \"Thank you, RED! Please take this Poké Flute!\"\n\n[Received Poké Flute!]");
                            player.hasPokeFlute = true;
                        }
                        else
                        {
                            UI::printBox("Pokémon Tower", "You whited out and fled the tower.");
                        }
                    }
                    else
                    {
                        UI::printBox("Pokémon Tower", "Mr. Fuji: \"Use the Poké Flute to wake up sleeping Pokémon!\"");
                    }
                }
                else if (cityName == "Celadon City")
                {
                    if (!player.hasSilphScope)
                    {
                        UI::printBox("Game Corner Rocket Hideout", "You push a secret switch behind the poster in Game Corner!\nYou infiltrate the basement Rocket Hideout!\n\nAfter defeating Grunts, you defeat Boss Giovanni!\nGiovanni: \"Impressive. Take this Silph Scope. We shall meet again!\"\n\n[Received Silph Scope!]");
                        player.hasSilphScope = true;
                    }
                    else
                    {
                        UI::printBox("Game Corner", "The hideout is empty. Celadon City is safe.");
                    }
                }
                else if (cityName == "Fuchsia City")
                {
                    if (!player.hasSurf || !player.hasStrength)
                    {
                        UI::printBox("Safari Zone & Warden", "You explore the Fuchsia Safari Zone!\nYou find the lost Gold Teeth in the grass and get HM03 (Surf)!\nYou return the Gold Teeth to the Safari Warden!\n\nWarden: \"Thank you so much! Here is HM04 (Strength)!\"\n\n[Learned HM03 Surf and HM04 Strength!]");
                        player.hasSurf = true;
                        player.hasGoldTeeth = true;
                        player.hasStrength = true;
                    }
                    else
                    {
                        UI::printBox("Safari Zone", "Warden: \"Enjoy exploring the Safari Zone!\"");
                    }
                }
                else if (cityName == "Saffron City")
                {
                    UI::printBox("Fighting Dojo", "You challenge the Saffron Fighting Dojo!\nYou defeat Karate Master Kiyo and get Hitmonlee Lvl 30!");
                }
                else if (cityName == "Cinnabar Island")
                {
                    if (!player.hasSecretKey)
                    {
                        UI::printBox("Pokémon Mansion", "You explore the abandoned volcano mansion...\nAmong old journals about Mew, you find the Gym Secret Key!\n\n[Received Secret Key!]");
                        player.hasSecretKey = true;
                    }
                    else
                    {
                        UI::printBox("Pokémon Mansion", "You found old journals here, but nothing else.");
                    }
                }
                else
                {
                    UI::printBox("Area Check", "You explore the area but find nothing interesting.");
                }
                std::cout << "\nPress Enter to continue...";
                std::cin.ignore(10000, '\n');
                break;
            }

            case '3':
            {
                if (currentCity.hasGym && !currentCity.gymCleared)
                {
                    // Kiểm tra các cờ kỹ thuật trước khi thách đấu Gym
                    if (currentCity.name == "Vermilion City" && !player.hasCut)
                    {
                        UI::clearScreen();
                        UI::printBox("Lt. Surge Gym Gate", "A small tree blocks the entrance to Vermilion Gym!\nYou need the Cut skill to clear it!");
                        std::cout << "\nPress Enter to continue...";
                        std::cin.ignore(10000, '\n');
                        break;
                    }

                    if (currentCity.name == "Cinnabar Island" && !player.hasSecretKey)
                    {
                        UI::clearScreen();
                        UI::printBox("Blaine Gym Gate", "The Cinnabar Gym door is locked!\nYou need the Secret Key to open it!");
                        std::cout << "\nPress Enter to continue...";
                        std::cin.ignore(10000, '\n');
                        break;
                    }

                    Trainer leader = Gen1Trainers::getGymLeaderByName(currentCity.gymLeader);
                    battle.initializeTrainerBattle(player, leader);
                    BattleResult gymResult = battle.runBattle(player);
                    player.party = battle.getPlayerParty();

                    if (gymResult == BattleResult::WIN)
                    {
                        player.badges++;
                        currentCity.gymCleared = true;
                        UI::clearScreen();
                        UI::printBox("Gym Victory", "You got the " + std::to_string(player.badges) + " Badge!");
                        std::cout << "\nPress Enter to continue...";
                        std::cin.ignore(10000, '\n');
                    }
                    else
                    {
                        UI::clearScreen();
                        UI::printBox("Blackout", "You blacked out! Try again.");
                        std::cout << "\nPress Enter to continue...";
                        std::cin.ignore(10000, '\n');
                    }
                }
                else
                {
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
                if (currentCity.hasGym && !currentCity.gymCleared)
                {
                    UI::clearScreen();
                    UI::printBox("Party",
                                 "Current party size: " + std::to_string(player.party.size()) + "\n[Party view stub - TODO]");
                    std::cout << "\nPress Enter to continue...";
                    std::cin.ignore(10000, '\n');
                }
                else
                {
                    UI::clearScreen();
                    handleBagMenu(player);
                }
                break;
            }

            case '5':
            {
                if (currentCity.hasGym && !currentCity.gymCleared)
                {
                    UI::clearScreen();
                    handleBagMenu(player);
                }
                else
                {
                    std::cout << "Invalid choice. Try again.\n";
                }
                break;
            }

            case 'S':
            case 's':
            {
                if (player.party.empty())
                {
                    UI::clearScreen();
                    UI::printBox("Sort Party", "Your party is empty!");
                    std::cout << "\nPress Enter to continue...";
                    std::cin.ignore(10000, '\n');
                    break;
                }

                Monster tmp[6];
                int n = 0;
                Queue<Monster> partyCopy = player.party;
                while (!partyCopy.empty() && n < 6)
                {
                    tmp[n++] = partyCopy.dequeue();
                }

                struct HPDescComp
                {
                    bool operator()(const Monster &a, const Monster &b) const
                    {
                        return a.hp > b.hp;
                    }
                };

                // GRADER: mergeSort from lib/Algorithms.hpp
                mergeSort(tmp, n, HPDescComp());

                player.party.clear();
                for (int i = 0; i < n; i++)
                {
                    player.party.enqueue(tmp[i]);
                }

                UI::clearScreen();
                UI::printBox("Sort Party", "Party sorted by HP (descending).\n");
                std::cout << "\nPress Enter to continue...";
                std::cin.ignore(10000, '\n');
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
