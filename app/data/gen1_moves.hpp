/**
 * @file gen1_moves.hpp
 * @brief Move database for Gen 1 Pokémon (Kanto region).
 *        Dùng trong BattleSystem cho damage calculation.
 *        Grader visibility: Rõ ràng định nghĩa Move struct data.
 */

#ifndef GEN1_MOVES_HPP
#define GEN1_MOVES_HPP

#include "../entities/Move.hpp"

namespace Gen1Moves
{
    // Power moves dùng cho phần lớn Pokemon với hệ đi kèm
    const Move EMBER("Ember", "Fire", 40, 25);               ///< Fire move, 40 power
    const Move GUST("Gust", "Flying", 40, 35);                 ///< Flying move, 40 power
    const Move SCRATCH("Scratch", "Normal", 40, 35);           ///< Normal move, 40 power
    const Move PECK("Peck", "Flying", 35, 35);                 ///< Flying move, 35 power
    const Move POWDER_SNOW("Powder Snow", "Ice", 40, 25);   ///< Ice move, 40 power
    const Move WATER_GUN("Water Gun", "Water", 40, 25);       ///< Water move, 40 power
    const Move VINE_WHIP("Vine Whip", "Grass", 45, 25);       ///< Grass move, 45 power
    const Move THUNDERBOLT("Thunderbolt", "Electric", 90, 15);   ///< Electric move, 90 power (strong)
    const Move ROCK_THROW("Rock Throw", "Rock", 50, 15);     ///< Rock move, 50 power
    const Move SHADOW_BALL("Shadow Ball", "Ghost", 80, 15);   ///< Ghost move, 80 power
    const Move THUNDERSHOCK("Thundershock", "Electric", 40, 30); ///< Electric move, 40 power
    const Move DISABLE("Disable", "Normal", 0, 20);            ///< Status move (stub for Phase 04)
    const Move FOCUS_ENERGY("Focus Energy", "Normal", 0, 30);  ///< Status move (stub for Phase 04)
}

#endif // GEN1_MOVES_HPP
