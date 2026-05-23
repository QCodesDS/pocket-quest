#include "BattleUI.hpp"
#include "UI.hpp"
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
        std::cout << "╔══════════════════════════════════════╗\n";

        // Enemy info
        displayMonsterInfo(enemyMon, "Enemy", true);

        std::cout << "╠══════════════════════════════════════╣\n";

        // Player info
        displayMonsterInfo(playerMon, "Your", false);

        std::cout << "╠══════════════════════════════════════╣\n";

        // Battle log (max 5 lines)
        // GRADER: Sử dụng Stack<std::string> từ lib/ để hiển thị log
        displayLog(battle.getLog());

        std::cout << "╠══════════════════════════════════════╣\n";

        // Action menu
        displayActionMenu();

        std::cout << "╚══════════════════════════════════════╝\n";
    }

    void displayMonsterInfo(Monster &mon, const std::string &owner, bool isEnemy)
    {
        // Format: "Enemy PIDGEY    Lv.5"
        //         "HP [##########]  35/35"

        std::string name = owner + " " + mon.name;
        std::string levelStr = "Lv." + std::to_string(mon.level);

        // Line 1: Name and Level
        std::cout << "║  " << name;
        // Pad to align level on right
        int namePadding = 34 - name.length() - levelStr.length();
        for (int i = 0; i < namePadding; i++)
            std::cout << " ";
        std::cout << levelStr << "  ║\n";

        // Line 2: HP Bar
        std::string hpDisplay = UI::hpBar(mon.hp, mon.maxHp, 10);
        std::string hpText = "HP " + hpDisplay + "  " + std::to_string(mon.hp) + "/" + std::to_string(mon.maxHp);

        std::cout << "║  " << hpText;
        int hpPadding = 34 - hpText.length();
        for (int i = 0; i < hpPadding; i++)
            std::cout << " ";
        std::cout << "  ║\n";
    }

    void displayLog(Stack<std::string> &log)
    {
        // Stack is LIFO, so we need to read it in reverse order
        // Create temporary array to store log lines in correct order

        std::string logLines[5];
        int lineCount = 0;

        // Copy stack to temporary stack to read in reverse (LIFO)
        Stack<std::string> tempStack;
        Stack<std::string> copyStack = log;

        // Pop all from log into tempStack (reverses the order)
        while (!copyStack.empty() && lineCount < 5)
        {
            logLines[lineCount] = copyStack.pop();
            lineCount++;
        }

        // Now logLines[] contains lines in reverse chronological order (oldest first)
        // Reverse again to show newest first
        for (int i = 0; i < lineCount / 2; i++)
        {
            std::string temp = logLines[i];
            logLines[i] = logLines[lineCount - 1 - i];
            logLines[lineCount - 1 - i] = temp;
        }

        // Display lines
        for (int i = 0; i < lineCount; i++)
        {
            std::cout << "║  " << logLines[i];
            int padding = 34 - logLines[i].length();
            for (int j = 0; j < padding; j++)
                std::cout << " ";
            std::cout << "  ║\n";
        }

        // Fill remaining lines if log has less than 5 entries
        for (int i = lineCount; i < 5; i++)
        {
            std::cout << "║  " << std::string(34, ' ') << "  ║\n";
        }
    }

    void displayActionMenu()
    {
        std::cout << "║     [1] Fight      [2] Bag           ║\n";
        std::cout << "║     [3] Switch     [4] Run           ║\n";
    }

} // namespace BattleUI
