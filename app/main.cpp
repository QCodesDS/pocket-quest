#include "core/Game.hpp"

#ifdef _WIN32
#include <windows.h>
#endif

/**
 * @brief  Điểm khởi đầu của chương trình game MonsterQuest.
 * @return 0 nếu kết thúc bình thường
 */
int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8); // Set UTF-8 output
    SetConsoleCP(CP_UTF8);       // Set UTF-8 input
#endif
    Game game;
    game.run();
    return 0;
}
