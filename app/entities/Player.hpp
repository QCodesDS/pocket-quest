#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include "Queue.hpp"
#include "Monster.hpp"
#include "../systems/InventorySystem.hpp"

/**
 * @struct Player
 * @brief  Cấu trúc dữ liệu lưu trữ thông tin và trạng thái của người chơi (Trainer).
 *         Quản lý party thông qua Queue<Monster> từ lib/ (Phase 03 lib usage).
 *         Quản lý bag thông qua InventorySystem với HashTable<string, Item> (Phase 04 lib usage).
 */
struct Player
{
    std::string name;        ///< Tên Trainer của người chơi
    int badges;              ///< Số lượng huy hiệu Gym đạt được (0 - 8)
    Queue<Monster> party;    ///< Đội hình chiến đấu dùng Queue<Monster> (FIFO: front mon battles first)
    std::string starterName; ///< Tên của Starter được chọn ban đầu
    bool rivalDefeated[4];   ///< Trạng thái các trận đấu với Rival Blue (4 lần)

    // Cờ trạng thái các nhiệm vụ cốt truyện (Quest Flags)
    bool hasParcel;          ///< Nhận được kiện hàng đặc biệt của Giáo sư Oak
    bool deliveredParcel;    ///< Đã giao kiện hàng thành công cho Giáo sư Oak (để lấy Pokédex)
    bool hasSSTicket;        ///< Vé tàu S.S. Anne nhận từ Bill
    bool hasCut;             ///< Bí kỹ HM01 Cut dùng chặt cây cản đường
    bool hasSilphScope;      ///< Kính hồng ngoại tìm ma ở Lavender Pokémon Tower
    bool hasPokeFlute;       ///< Sáo đánh thức Snorlax mở đường đi Fuchsia
    bool hasSurf;            ///< Kỹ năng bơi HM03 Surf
    bool hasGoldTeeth;       ///< Hàm răng vàng bị mất của Giám đốc Safari
    bool hasStrength;        ///< Kỹ năng đẩy đá HM04 Strength
    bool hasSecretKey;       ///< Chìa khóa bí mật mở Gym Blaine tại Cinnabar Island

    // GRADER: InventorySystem uses HashTable<string, Item> from lib/ (Phase 04 lib usage)
    InventorySystem inventory; ///< Bag của player quản lý items

    /**
     * @brief Constructor khởi tạo Trainer mặc định với các giá trị rỗng.
     *        Khởi tạo inventory với Potion ×3 ban đầu.
     */
    Player();

    /**
     * @brief Khởi tạo party với Starter Pokémon dựa trên starterName.
     *        Được gọi sau khi IntroUI::showStarterSelect() cài đặt starterName.
     *        Sử dụng Queue<Monster> từ lib/ để lưu starter vào party.
     */
    void initializePartyWithStarter();

    /**
     * @brief Hồi phục toàn bộ HP cho tất cả Pokémon trong party (Dùng khi Blackout).
     */
    void healParty();
};

#endif // PLAYER_HPP
