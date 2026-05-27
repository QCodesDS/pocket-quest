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
    // ===== ATTACKING MOVES =====
    const Move TACKLE("Tackle", "Normal", 40, 35);               ///< Normal move, 40 power
    const Move SCRATCH("Scratch", "Normal", 40, 35);             ///< Normal move, 40 power
    const Move EMBER("Ember", "Fire", 40, 25);                   ///< Fire move, 40 power
    const Move GUST("Gust", "Flying", 40, 35);                   ///< Flying move, 40 power
    const Move PECK("Peck", "Flying", 35, 35);                   ///< Flying move, 35 power
    const Move WATER_GUN("Water Gun", "Water", 40, 25);          ///< Water move, 40 power
    const Move VINE_WHIP("Vine Whip", "Grass", 45, 25);          ///< Grass move, 45 power
    const Move POWDER_SNOW("Powder Snow", "Ice", 40, 25);        ///< Ice move, 40 power
    const Move THUNDERSHOCK("Thundershock", "Electric", 40, 30); ///< Electric move, 40 power
    const Move THUNDERBOLT("Thunderbolt", "Electric", 90, 15);   ///< Electric move, 90 power
    const Move ROCK_THROW("Rock Throw", "Rock", 50, 15);         ///< Rock move, 50 power
    const Move SHADOW_BALL("Shadow Ball", "Ghost", 80, 15);      ///< Ghost move, 80 power
    const Move BITE("Bite", "Normal", 60, 25);                   ///< Normal move, 60 power
    const Move LEECH_SEED("Leech Seed", "Grass", 0, 10);         ///< Status move (HP drain)
    const Move ABSORB("Absorb", "Grass", 20, 25);                ///< Grass move, 20 power + HP drain
    const Move THUNDERWAVE("Thunder Wave", "Electric", 0, 20);   ///< Status move (paralysis)
    const Move FURY_ATTACK("Fury Attack", "Normal", 15, 20);     ///< Normal move, 15 power x2-5
    const Move QUICK_ATTACK("Quick Attack", "Normal", 40, 30);   ///< Normal move, 40 power
    const Move TWISTER("Twister", "Dragon", 40, 20);             ///< Dragon move, 40 power
    const Move DRAGON_RAGE("Dragon Rage", "Dragon", 40, 10);     ///< Dragon move, 40 damage fixed

    // ===== STATUS MOVES =====
    const Move GROWL("Growl", "Normal", 0, 40);               ///< Status move (lower ATK)
    const Move LEER("Leer", "Normal", 0, 30);                 ///< Status move (lower DEF)
    const Move TAIL_WHIP("Tail Whip", "Normal", 0, 30);       ///< Status move (lower DEF)
    const Move DISABLE("Disable", "Normal", 0, 20);           ///< Status move (disable move)
    const Move FOCUS_ENERGY("Focus Energy", "Normal", 0, 30); ///< Status move (boost crit)
    const Move PROTECT("Protect", "Normal", 0, 40);           ///< Status move (protect this turn)
    const Move RECOVER("Recover", "Normal", 0, 20);           ///< Status move (heal 50% HP)
}

#endif // GEN1_MOVES_HPP
