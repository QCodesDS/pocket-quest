#include "Player.hpp"
#include "../data/gen1_monsters.hpp"

Player::Player() : name(""), badges(0), starterName("")
{
    // Khởi tạo hàng đợi party rỗng, sẽ được thêm Starter khi initializePartyWithStarter() gọi
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
