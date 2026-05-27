#include "Monster.hpp"
#include "../data/gen1_learnsets_all.hpp"

Monster::Monster()
    : name(""), type(""), id(0), level(1), hp(0), maxHp(0),
      atk(0), def(0), spd(0), spAtk(0), spDef(0), exp(0), nextLevelExp(5)
{
    // Khởi tạo 4 moves rỗng (mặc định)
    for (int i = 0; i < 4; i++)
    {
        moves[i] = Move();
    }
}

Monster::Monster(const std::string &n, const std::string &t, int i, int lvl,
                 int hp_, int a, int d, int s, int spAtk_, int spDef_)
    : name(n), type(t), id(i), level(lvl), hp(hp_), maxHp(hp_),
      atk(a), def(d), spd(s), spAtk(spAtk_), spDef(spDef_),
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
    while (exp >= nextLevelExp)
    {
        levelUp();
        leveledUp = true;
    }
    return leveledUp;
}

void Monster::levelUp()
{
    level++;
    nextLevelExp = level * level * 5;

    // Tăng chỉ số (+1 mỗi lần levelup)
    maxHp += 1;
    hp = (hp + 1 > maxHp) ? maxHp : hp + 1; // Hồi 1 máu mỗi khi lên cấp
    atk += 1;
    def += 1;
    spd += 1;
    spAtk += 1;
    spDef += 1;

    // Kiểm tra học chiêu mới tại level mới
    learnMovesAtLevel(level);
}

void Monster::learnMovesAtLevel(int newLevel)
{
    // Lookup learnset từ gen1_learnsets_all.hpp dựa trên pokemon id
    // Sử dụng string matching để tìm đúng learnset struct

    // Ví dụ: nếu id = 4 (Charmander) tại level 10 → học EMBER
    // Cách tiếp cận: dùng static lookup array hoặc switch statement

    // Để đơn giản, ta sử dụng hard-coded lookup cho các starters + common mons
    // Tương lai có thể refactor thành dynamic lookup

    if (id == 1)
    { // Bulbasaur
        // Learnset: Lv1 Tackle/Growl, Lv7 Leech Seed, Lv13 Vine Whip, etc.
        if (newLevel == 7)
            addMove(Move("Leech Seed", "Grass", 0, 10));
        else if (newLevel == 13)
            addMove(Move("Vine Whip", "Grass", 45, 25));
        else if (newLevel == 20)
            addMove(Move("Poison Powder", "Poison", 0, 75));
    }
    else if (id == 4)
    { // Charmander
        // Learnset: Lv1 Scratch/Growl, Lv10 Ember, Lv16 Flame Burst, etc.
        if (newLevel == 10)
            addMove(Move("Ember", "Fire", 40, 25));
        // More levels can be added
    }
    else if (id == 7)
    { // Squirtle
        // Learnset: Lv1 Tackle/Tail Whip, Lv8 Water Gun, Lv15 Bite, etc.
        if (newLevel == 8)
            addMove(Move("Water Gun", "Water", 40, 25));
        else if (newLevel == 15)
            addMove(Move("Bite", "Normal", 60, 25));
    }
    // Thêm learnsets cho các pokémon khác nếu cần
}

void Monster::addMove(const Move &newMove)
{
    // Tìm slot trống hoặc replace move cuối cùng
    for (int i = 0; i < 4; i++)
    {
        if (moves[i].name.empty())
        {
            moves[i] = newMove;
            return;
        }
    }
    // Nếu không có slot trống, thay move cuối (slot 3)
    moves[3] = newMove;
}
