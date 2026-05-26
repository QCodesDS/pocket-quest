#include "Player.hpp"
#include "../data/gen1_monsters.hpp"

Player::Player() : name(""), badges(0), starterName(""),
                   hasParcel(false), deliveredParcel(false), hasSSTicket(false),
                   hasCut(false), hasSilphScope(false), hasPokeFlute(false),
                   hasSurf(false), hasGoldTeeth(false), hasStrength(false),
                   hasSecretKey(false)
{
    // Khởi tạo hàng đợi party rỗng, sẽ được thêm Starter khi initializePartyWithStarter() gọi
    for (int i = 0; i < 4; i++)
    {
        rivalDefeated[i] = false;
    }

    // GRADER: Khởi tạo inventory với Potion ×3 ban đầu
    // Sử dụng InventorySystem::addItem() với HashTable::insert()
    inventory.addItem("Potion", 3);
}

void Player::initializePartyWithStarter()
{
    // Tải Starter từ gen1_monsters.hpp dựa trên starterName
    // GRADER: Sử dụng Queue<Monster> từ lib/ để enqueue() starter vào party

    if (starterName == "Bulbasaur")
    {
        party.enqueue(Gen1Monsters::BULBASAUR);
    }
    else if (starterName == "Charmander")
    {
        party.enqueue(Gen1Monsters::CHARMANDER);
    }
    else if (starterName == "Squirtle")
    {
        party.enqueue(Gen1Monsters::SQUIRTLE);
    }
    // Nếu starterName không hợp lệ, party vẫn rỗng (safe fallback)
}

void Player::healParty()
{
    int s = party.size();
    for (int i = 0; i < s; i++)
    {
        Monster m = party.dequeue();
        m.hp = m.maxHp;
        party.enqueue(m);
    }
}
