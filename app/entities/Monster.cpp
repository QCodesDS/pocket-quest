#include "Monster.hpp"

Monster::Monster()
    : name(""), type(""), id(0), level(1), hp(0), maxHp(0),
      atk(0), def(0), spd(0)
{
    // Khởi tạo 4 moves rỗng (mặc định)
    for (int i = 0; i < 4; i++)
    {
        moves[i] = Move();
    }
}

Monster::Monster(const std::string &n, const std::string &t, int i, int lvl,
                 int hp_, int a, int d, int s)
    : name(n), type(t), id(i), level(lvl), hp(hp_), maxHp(hp_),
      atk(a), def(d), spd(s)
{
    // Khởi tạo 4 moves rỗng (sẽ được gán trong gen1_monsters.hpp)
    for (int i = 0; i < 4; i++)
    {
        moves[i] = Move();
    }
}
