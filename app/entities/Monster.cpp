#include "Monster.hpp"

Monster::Monster()
    : name(""), type(""), id(0), level(1), hp(0), maxHp(0),
      atk(0), def(0), spd(0), spc(0), exp(0), nextLevelExp(5)
{
    // Khởi tạo 4 moves rỗng (mặc định)
    for (int i = 0; i < 4; i++)
    {
        moves[i] = Move();
    }
}

Monster::Monster(const std::string &n, const std::string &t, int i, int lvl,
                 int hp_, int a, int d, int s, int sp)
    : name(n), type(t), id(i), level(lvl), hp(hp_), maxHp(hp_),
      atk(a), def(d), spd(s), spc(sp < 0 ? s / 2 : sp),
      exp(0), nextLevelExp(lvl * lvl * 5)
{
    // Khởi tạo 4 moves rỗng (sẽ được gán trong gen1_monsters.hpp)
    for (int i = 0; i < 4; i++)
    {
        moves[i] = Move();
    }
}

bool Monster::gainExp(int amount)
{
    exp += amount;
    bool leveledUp = false;
    while (exp >= nextLevelExp) {
        levelUp();
        leveledUp = true;
    }
    return leveledUp;
}

void Monster::levelUp()
{
    level++;
    nextLevelExp = level * level * 5;
    
    // Tăng chỉ số
    maxHp += 2;
    hp += 2; // Hồi 2 máu mỗi khi lên cấp
    atk += 1;
    def += 1;
    spd += 1;
    spc += 1;
}
