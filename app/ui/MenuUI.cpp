#include "MenuUI.hpp"
#include "UI.hpp"
#include <iostream>
#include <string>

namespace MenuUI {

    void showGameOver(const Player& player) {
        UI::clearScreen();
        std::cout << "\n\n";
        
        std::string text = 
            "           GAME OVER\n\n"
            "  Trainer : " + player.name + "\n"
            "  Badges  : " + std::to_string(player.badges) + "/8\n\n"
            "  \"Do not lose hope! Keep training\n"
            "   your partner " + (player.starterName.empty() ? "Pokémon" : player.starterName) + "!\"";
            
        UI::printBox("DEFEAT", text);
        
        std::cout << "\n             [ PRESS ENTER TO CONTINUE ]\n";
        std::string dummy;
        std::getline(std::cin, dummy);
    }

    void showVictory(const Player& player) {
        UI::clearScreen();
        std::cout << "\n\n";
        
        std::string text = 
            "         ★  CHAMPION!  ★\n\n"
            "  Trainer : " + player.name + "\n"
            "  Partner : " + player.starterName + "\n"
            "  Badges  : " + std::to_string(player.badges) + "/8\n\n"
            "  \"" + player.name + " became the Pokémon League\n"
            "   Champion!\"";
            
        UI::printBox("VICTORY", text);
        
        std::cout << "\n             [ PRESS ENTER TO FINISH ]\n";
        std::string dummy;
        std::getline(std::cin, dummy);
    }
}
