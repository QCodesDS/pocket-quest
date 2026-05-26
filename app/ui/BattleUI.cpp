#include "BattleUI.hpp"
#include "UI.hpp"
#include "../lib/Algorithms.hpp"
#include <iostream>
#include <cstring>

namespace BattleUI
{

    // Helper: build party indicator string like [●][●][●][ ][ ][ ]
    std::string partyIndicator(int alive)
    {
        const int MAX_SLOTS = 8;
        std::string result = "";
        for (int i = 0; i < MAX_SLOTS; i++)
        {
            if (i < alive)
                result += "[O]";
            else
                result += "[ ]";
        }
        return result;
    }

    std::string getTypeColor(const std::string& type)
    {
        if (type.find("Fire") != std::string::npos) return "\033[31m";
        if (type.find("Water") != std::string::npos) return "\033[34m";
        if (type.find("Grass") != std::string::npos) return "\033[32m";
        if (type.find("Electric") != std::string::npos) return "\033[33m";
        if (type.find("Poison") != std::string::npos) return "\033[35m";
        if (type.find("Psychic") != std::string::npos || type.find("Ghost") != std::string::npos) return "\033[35m";
        if (type.find("Flying") != std::string::npos || type.find("Ice") != std::string::npos) return "\033[36m";
        if (type.find("Bug") != std::string::npos) return "\033[32m";
        if (type.find("Ground") != std::string::npos || type.find("Rock") != std::string::npos) return "\033[33m";
        if (type.find("Dragon") != std::string::npos) return "\033[34m";
        return "\033[37m"; // White default
    }

    std::string formatDualTypeDisp(const std::string& type) {
        size_t pos = type.find('/');
        if (pos != std::string::npos) {
            std::string t1 = type.substr(0, pos);
            std::string t2 = type.substr(pos + 1);
            return "[" + getTypeColor(t1) + t1 + "\033[0m][" + getTypeColor(t2) + t2 + "\033[0m]";
        }
        return "[" + getTypeColor(type) + type + "\033[0m]";
    }

    std::string formatDualTypeRaw(const std::string& type) {
        size_t pos = type.find('/');
        if (pos != std::string::npos) {
            std::string t1 = type.substr(0, pos);
            std::string t2 = type.substr(pos + 1);
            return "[" + t1 + "][" + t2 + "]";
        }
        return "[" + type + "]";
    }

    void renderBattleScreen(BattleSystem &battle)
    {
        UI::clearScreen();

        Queue<Monster> &playerParty = battle.getPlayerParty();
        Queue<Monster> &enemyParty = battle.getEnemyParty();

        if (playerParty.empty() || enemyParty.empty())
        {
            std::cout << "ERROR: Empty party during battle!\n";
            return;
        }

        Monster &playerMon = playerParty.front();
        Monster &enemyMon = enemyParty.front();

        int pDisplayHp = playerMon.hp < 0 ? 0 : playerMon.hp;
        int eDisplayHp = enemyMon.hp < 0 ? 0 : enemyMon.hp;

        std::string pHpBar = UI::hpBar(pDisplayHp, playerMon.maxHp, 20);
        std::string eHpBar = UI::hpBar(eDisplayHp, enemyMon.maxHp, 20);

        int pAlive = playerParty.size();
        int eAlive = enemyParty.size();
        std::string pParty = partyIndicator(pAlive);
        std::string eParty = partyIndicator(eAlive);

        // ========== TOP BORDER ==========
        std::cout << "+------------------------------------------------------------------------------+\n";

        // ========== ENEMY (top-right) ==========
        // Row 1: enemy party indicator (right-aligned)
        int ePartyLen = (int)eParty.length();
        std::cout << "|";
        for (int i = 0; i < 78 - ePartyLen - 2; i++) std::cout << " ";
        std::cout << eParty << "  |\n";

        // Row 2: enemy name + level + type (right-aligned)
        std::string eInfoRaw = enemyMon.name + "  Lv" + std::to_string(enemyMon.level) + " " + formatDualTypeRaw(enemyMon.type);
        std::string eInfoDisp = enemyMon.name + "  Lv" + std::to_string(enemyMon.level) + " " + formatDualTypeDisp(enemyMon.type);
        int eInfoLen = (int)eInfoRaw.length();
        std::cout << "|";
        for (int i = 0; i < 78 - eInfoLen - 2; i++) std::cout << " ";
        std::cout << eInfoDisp << "  |\n";

        // Row 3: enemy HP bar (right-aligned)
        std::string eBarLine = "HP: " + eHpBar;
        int eBarLen = (int)eBarLine.length();
        std::cout << "|";
        for (int i = 0; i < 78 - eBarLen - 2; i++) std::cout << " ";
        std::cout << eBarLine << "  |\n";

        // Row 4: enemy HP numbers (right-aligned)
        std::string eHpNum = std::to_string(eDisplayHp) + "/" + std::to_string(enemyMon.maxHp);
        int eHpNumLen = (int)eHpNum.length();
        std::cout << "|";
        for (int i = 0; i < 78 - eHpNumLen - 2; i++) std::cout << " ";
        std::cout << eHpNum << "  |\n";

        // Separator row
        std::cout << "|                                                                              |\n";

        // ========== PLAYER (bottom-left) ==========
        // Row 1: player party indicator (left-aligned)
        std::cout << "|  " << pParty;
        int pPartyLen = (int)pParty.length();
        for (int i = 0; i < 78 - pPartyLen - 2; i++) std::cout << " ";
        std::cout << "|\n";

        // Row 2: player name + level + type (left-aligned)
        std::string pInfoRaw = playerMon.name + "  Lv" + std::to_string(playerMon.level) + " " + formatDualTypeRaw(playerMon.type);
        std::string pInfoDisp = playerMon.name + "  Lv" + std::to_string(playerMon.level) + " " + formatDualTypeDisp(playerMon.type);
        int pInfoLen = (int)pInfoRaw.length();
        std::cout << "|  " << pInfoDisp;
        for (int i = 0; i < 78 - pInfoLen - 2; i++) std::cout << " ";
        std::cout << "|\n";

        // Row 3: player HP bar (left-aligned)
        std::string pBarLine = "HP: " + pHpBar;
        int pBarLen = (int)pBarLine.length();
        std::cout << "|  " << pBarLine;
        for (int i = 0; i < 78 - pBarLen - 2; i++) std::cout << " ";
        std::cout << "|\n";

        // Row 4: player HP numbers (left-aligned)
        std::string pHpNum = std::to_string(pDisplayHp) + "/" + std::to_string(playerMon.maxHp);
        int pHpNumLen = (int)pHpNum.length();
        std::cout << "|  " << pHpNum;
        for (int i = 0; i < 78 - pHpNumLen - 2; i++) std::cout << " ";
        std::cout << "|\n";

        // ========== BATTLE LOG ==========
        std::cout << "+------------------------------------------------------------------------------+\n";

        displayLog(battle.getLog());

        // ========== CHOOSE ACTION ==========
        std::cout << "+------------------------------------------------------------------------------+\n";
        std::cout << "|  What will you do?                                                           |\n";
        std::cout << "|  [1] FIGHT        [2] BAG          [3] SWITCH       [4] RUN                  |\n";
        std::cout << "+------------------------------------------------------------------------------+\n";
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
                content = "> " + logLines[i];
            }
            std::cout << "|  " << content;
            int padding = 76 - (int)content.length();
            for (int j = 0; j < padding; j++)
                std::cout << " ";
            std::cout << "|\n";
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
