#include "core/Game.hpp"
#include <windows.h>

/**
 * @brief  Điểm khởi đầu của chương trình game MonsterQuest.
 * @return 0 nếu kết thúc bình thường
 */
int main() {
    SetConsoleOutputCP(CP_UTF8);  // Set UTF-8 output
    SetConsoleCP(CP_UTF8);        // Set UTF-8 input
    Game game;
    game.run();
    return 0;
}
