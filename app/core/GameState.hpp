#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

/**
 * @enum  GameState
 * @brief Định nghĩa các trạng thái cốt lõi của máy trạng thái game (Game State Machine).
 */
enum class GameState {
    MENU,       ///< Màn hình chính (Main Menu) / Title screen
    INTRO,      ///< Cốt truyện mở đầu (Oak Intro Dialog, Name Input, Starter Select)
    OVERWORLD,  ///< Di chuyển tự do trên bản đồ thế giới Kanto
    BATTLE,     ///< Trận chiến Turn-based (Wild hoặc Trainer)
    GAMEOVER,   ///< Trực quan hóa màn hình Game Over
    WIN         ///< Trực quan hóa màn hình Victory / Champion
};

#endif // GAMESTATE_HPP
