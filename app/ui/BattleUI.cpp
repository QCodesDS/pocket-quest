#include "BattleUI.hpp"
#include "UI.hpp"
#include "../lib/Algorithms.hpp"
#include <iostream>
#include <cstring>

namespace BattleUI
{

    void renderBattleScreen(BattleSystem &battle)
    {
        UI::clearScreen();

        // Get references to parties
        Queue<Monster> &playerParty = battle.getPlayerParty();
        Queue<Monster> &enemyParty = battle.getEnemyParty();

        // Check if parties are empty (shouldn't happen during battle)
        if (playerParty.empty() || enemyParty.empty())
        {
            std::cout << "ERROR: Empty party during battle!\n";
            return;
        }

        Monster &playerMon = playerParty.front();
        Monster &enemyMon = enemyParty.front();

        // ===== Render Battle Screen =====
        std::cout << "================================================================================\n";
        std::cout << "║                                POCKET QUEST                                  ║\n";
        std::cout << "================================================================================\n";

        // Display Side-by-Side Party Overview
        std::string pName = playerMon.name + " (Lv." + std::to_string(playerMon.level) + ")";
        std::string eName = enemyMon.name + " (Lv." + std::to_string(enemyMon.level) + ")";

        // Clean HP Bar calculation
        int pPercent = (playerMon.maxHp > 0) ? (playerMon.hp * 100 / playerMon.maxHp) : 0;
        int ePercent = (enemyMon.maxHp > 0) ? (enemyMon.hp * 100 / enemyMon.maxHp) : 0;

        std::string pHpBar = UI::hpBar(playerMon.hp, playerMon.maxHp, 12);
        std::string eHpBar = UI::hpBar(enemyMon.hp, enemyMon.maxHp, 12);

        // Print active battle stats
        std::cout << "║  [PLAYER MONSTER]                             [ENEMY MONSTER]                ║\n";
        
        // Player info line
        std::string pInfo = pName + " " + pHpBar + " " + std::to_string(pPercent) + "%";
        // Enemy info line
        std::string eInfo = eName + " " + eHpBar + " " + std::to_string(ePercent) + "%";

        std::cout << "║  " << pInfo;
        int leftPad = 45 - (int)pInfo.length();
        for (int i = 0; i < leftPad; i++) std::cout << " ";
        std::cout << eInfo;
        int rightPad = 77 - 45 - (int)eInfo.length();
        for (int i = 0; i < rightPad; i++) std::cout << " ";
        std::cout << "║\n";

        // Print attributes row
        std::string pStats = "HP: " + std::to_string(playerMon.hp) + "/" + std::to_string(playerMon.maxHp) + 
                             " (" + playerMon.type + ")";
        std::string eStats = "HP: " + std::to_string(enemyMon.hp) + "/" + std::to_string(enemyMon.maxHp) + 
                             " (" + enemyMon.type + ")";
        std::cout << "║  " << pStats;
        leftPad = 45 - (int)pStats.length();
        for (int i = 0; i < leftPad; i++) std::cout << " ";
        std::cout << eStats;
        rightPad = 77 - 45 - (int)eStats.length();
        for (int i = 0; i < rightPad; i++) std::cout << " ";
        std::cout << "║\n";

        // Print stats row (Atk, Def, Spd, Spc)
        std::string pAttr = "Atk:" + std::to_string(playerMon.atk) + " Def:" + std::to_string(playerMon.def) + 
                            " Spd:" + std::to_string(playerMon.spd) + " Spc:" + std::to_string(playerMon.spc);
        std::string eAttr = "Atk:" + std::to_string(enemyMon.atk) + " Def:" + std::to_string(enemyMon.def) + 
                            " Spd:" + std::to_string(enemyMon.spd) + " Spc:" + std::to_string(enemyMon.spc);
        std::cout << "║  " << pAttr;
        leftPad = 45 - (int)pAttr.length();
        for (int i = 0; i < leftPad; i++) std::cout << " ";
        std::cout << eAttr;
        rightPad = 77 - 45 - (int)eAttr.length();
        for (int i = 0; i < rightPad; i++) std::cout << " ";
        std::cout << "║\n";

        std::cout << "║                                                                              ║\n";
        std::cout << "║  [BATTLE LOG]                                                                ║\n";
        std::cout << "║  ┌────────────────────────────────────────────────────────────────────────┐  ║\n";

        // Render logs
        displayLog(battle.getLog());

        std::cout << "║  └────────────────────────────────────────────────────────────────────────┘  ║\n";
        std::cout << "║                                                                              ║\n";
        std::cout << "║  [CHOOSE ACTION]                                                             ║\n";
        std::cout << "║  ┌──────────────────┐ ┌──────────────────┐ ┌──────────────────┐ ┌──────────┐ ║\n";
        std::cout << "║  │ [1] FIGHT        │ │ [2] BAG          │ │ [3] SWITCH       │ │ [4] RUN  │ ║\n";
        std::cout << "║  └──────────────────┘ └──────────────────┘ └──────────────────┘ └──────────┘ ║\n";
        std::cout << "================================================================================\n";
    }

    void displayLog(Stack<std::string> &log)
    {
        std::string logLines[5];
        int lineCount = 0;

        // Copy stack to read chronologically
        Stack<std::string> tempStack;
        Stack<std::string> copyStack = log;

        while (!copyStack.empty() && lineCount < 5)
        {
            logLines[lineCount] = copyStack.pop();
            lineCount++;
        }

        // Chronological order: reverse
        for (int i = 0; i < lineCount / 2; i++)
        {
            std::string temp = logLines[i];
            logLines[i] = logLines[lineCount - 1 - i];
            logLines[lineCount - 1 - i] = temp;
        }

        // Display lines with padding
        for (int i = 0; i < 4; i++)
        {
            std::string content = "";
            if (i < lineCount)
            {
                content = logLines[i];
            }
            std::cout << "║  │ " << content;
            int padding = 70 - (int)content.length();
            for (int j = 0; j < padding; j++)
                std::cout << " ";
            std::cout << " │  ║\n";
        }
    }

    void displayBagMenu(InventorySystem &inventory, ItemEntry items[], int &count)
    {
        count = 0;

        if (inventory.empty())
        {
            UI::printBox("BAG", "Your bag is empty!");
            return;
        }

        // Collect items via InventorySystem::forEach into ItemEntry items[10]
        inventory.forEach([&items, &count](const std::string &name, Item &item)
                          {
                              if (count < 10)
                              {
                                  items[count].name = name;
                                  items[count].item = item;
                                  count++;
                              } });

        if (count == 0)
        {
            UI::printBox("BAG", "Your bag is empty!");
            return;
        }

        // Sort items by name ascending
        struct NameAscComp
        {
            bool operator()(const ItemEntry &a, const ItemEntry &b) const
            {
                return a.name < b.name;
            }
        };

        // GRADER: insertionSort from lib/Algorithms.hpp
        insertionSort(items, count, NameAscComp());

        // Display header
        std::cout << "╔════════════════════════════════════╗\n";
        std::cout << "║  BAG                               ║\n";
        std::cout << "╠════════════════════════════════════╣\n";

        for (int i = 0; i < count; i++)
        {
            std::string line = "[" + std::to_string(i + 1) + "] " + items[i].name +
                               " x" + std::to_string(items[i].item.quantity) +
                               " (+" + std::to_string(items[i].item.healAmount) + " HP)";
            std::cout << "║  " << line;
            int padding = 30 - (int)line.length();
            for (int j = 0; j < padding && j < 30; j++)
                std::cout << " ";
            std::cout << "║\n";
        }

        std::cout << "╠════════════════════════════════════╣\n";
        std::cout << "║  [0] Cancel                        ║\n";
        std::cout << "╚════════════════════════════════════╝\n";
    }

} // namespace BattleUI
