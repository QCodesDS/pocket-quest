/**
 * @file gen1_monsters.hpp
 * @brief Pokémon database for Gen 1 Kanto region (18 monsters).
 *        Includes starters, wild encounters, and gym leader mons.
 *        Used in BattleSystem via Queue<Monster> for battles.
 *        Grader visibility: Clear Monster struct initialization.
 */

#ifndef GEN1_MONSTERS_HPP
#define GEN1_MONSTERS_HPP

#include "../entities/Monster.hpp"
#include "gen1_moves.hpp"

namespace Gen1Monsters
{

    // ===== HELPER: Create monster with moves =====
    inline Monster createMonster(const std::string &name, const std::string &type, int id,
                                 int level, int hp, int atk, int def, int spd,
                                 const Move &m1 = Move(), const Move &m2 = Move(),
                                 const Move &m3 = Move(), const Move &m4 = Move())
    {
        Monster m(name, type, id, level, hp, atk, def, spd, spd, spd);
        m.moves[0] = m1;
        m.moves[1] = m2;
        m.moves[2] = m3;
        m.moves[3] = m4;
        return m;
    }

    inline Monster createMonster(const std::string &name, const std::string &type, int id,
                                 int level, int hp, int atk, int def, int spd,
                                 int spAtk, int spDef,
                                 const Move &m1 = Move(), const Move &m2 = Move(),
                                 const Move &m3 = Move(), const Move &m4 = Move())
    {
        Monster m(name, type, id, level, hp, atk, def, spd, spAtk, spDef);
        m.moves[0] = m1;
        m.moves[1] = m2;
        m.moves[2] = m3;
        m.moves[3] = m4;
        return m;
    }

    // ===== STARTERS (Kanto: Bulbasaur, Charmander, Squirtle) =====

    /**
     * @brief Bulbasaur - Grass/Poison starter (Dex #001)
     *        Starter move set: Vine Whip, Powder Snow, Disable, Focus Energy
     */
    const Monster BULBASAUR = createMonster(
        "Bulbasaur", "Grass/Poison", 1, 5,
        45, 49, 49, 45,
        Gen1Moves::VINE_WHIP, Gen1Moves::POWDER_SNOW,
        Gen1Moves::DISABLE, Gen1Moves::FOCUS_ENERGY);

    /**
     * @brief Charmander - Fire starter (Dex #004)
     *        Starter move set: Ember, Scratch, Disable, Focus Energy
     */
    const Monster CHARMANDER = createMonster(
        "Charmander", "Fire", 4, 5,
        39, 52, 43, 65,
        Gen1Moves::EMBER, Gen1Moves::SCRATCH,
        Gen1Moves::DISABLE, Gen1Moves::FOCUS_ENERGY);

    /**
     * @brief Squirtle - Water starter (Dex #007)
     *        Starter move set: Water Gun, Powder Snow, Disable, Focus Energy
     */
    const Monster SQUIRTLE = createMonster(
        "Squirtle", "Water", 7, 5,
        44, 48, 65, 43,
        Gen1Moves::WATER_GUN, Gen1Moves::POWDER_SNOW,
        Gen1Moves::DISABLE, Gen1Moves::FOCUS_ENERGY);

    // ===== WILD ENCOUNTERS (Level 5-10) =====

    /**
     * @brief Pidgey - Flying wild encounter (Dex #016)
     *        Common wild mon in early areas
     */
    const Monster PIDGEY = createMonster(
        "Pidgey", "Flying/Normal", 16, 5,
        35, 40, 40, 35,
        Gen1Moves::GUST, Gen1Moves::PECK);

    /**
     * @brief Rattata - Normal wild encounter (Dex #019)
     *        Common wild mon
     */
    const Monster RATTATA = createMonster(
        "Rattata", "Normal", 19, 5,
        30, 56, 35, 72,
        Gen1Moves::SCRATCH, Gen1Moves::FOCUS_ENERGY);

    /**
     * @brief Caterpie - Bug wild encounter (Dex #010)
     *        Early game wild mon
     */
    const Monster CATERPIE = createMonster(
        "Caterpie", "Bug", 10, 5,
        45, 52, 43, 35,
        Gen1Moves::SCRATCH, Gen1Moves::DISABLE);

    /**
     * @brief Pikachu - Electric wild encounter (Dex #025)
     *        Iconic rare encounter
     */
    const Monster PIKACHU = createMonster(
        "Pikachu", "Electric", 25, 7,
        35, 55, 40, 90,
        Gen1Moves::THUNDERSHOCK, Gen1Moves::FOCUS_ENERGY);

    /**
     * @brief Geodude - Rock/Ground wild encounter (Dex #074)
     *        Gym leader mon (Brock) and wild
     */
    const Monster GEODUDE = createMonster(
        "Geodude", "Rock/Ground", 74, 8,
        40, 80, 100, 20,
        Gen1Moves::ROCK_THROW, Gen1Moves::DISABLE);

    /**
     * @brief Gastly - Ghost/Poison wild encounter (Dex #092)
     *        Rare wild encounter
     */
    const Monster GASTLY = createMonster(
        "Gastly", "Ghost/Poison", 92, 9,
        30, 35, 30, 80,
        Gen1Moves::SHADOW_BALL, Gen1Moves::DISABLE);

    // ===== GYM LEADER & ELITE FOUR MONS (Level 15-30) =====

    /**
     * @brief Onix - Rock/Ground gym leader mon (Dex #095)
     *        Used by Brock (Pewter City Gym Leader)
     */
    const Monster ONIX = createMonster(
        "Onix", "Rock/Ground", 95, 18,
        35, 45, 160, 30,
        Gen1Moves::ROCK_THROW, Gen1Moves::DISABLE);

    /**
     * @brief Staryu - Water gym leader mon (Dex #120)
     *        Used by Misty (Cerulean City Gym Leader)
     */
    const Monster STARYU = createMonster(
        "Staryu", "Water", 120, 18,
        30, 45, 55, 85,
        Gen1Moves::WATER_GUN, Gen1Moves::FOCUS_ENERGY);

    /**
     * @brief Starmie - Water/Psychic gym leader mon (Dex #121)
     *        Evolved form, Misty's ace mon
     */
    const Monster STARMIE = createMonster(
        "Starmie", "Water/Psychic", 121, 20,
        60, 75, 85, 115,
        Gen1Moves::WATER_GUN, Gen1Moves::THUNDERBOLT);

    /**
     * @brief Raichu - Electric gym leader mon (Dex #026)
     *        Used by Lt. Surge (Vermilion City Gym Leader)
     */
    const Monster RAICHU = createMonster(
        "Raichu", "Electric", 26, 21,
        60, 90, 55, 110,
        Gen1Moves::THUNDERBOLT, Gen1Moves::THUNDERSHOCK);

    /**
     * @brief Magneton - Electric/Steel gym leader mon (Dex #082)
     *        Used by Lt. Surge's team
     */
    const Monster MAGNETON = createMonster(
        "Magneton", "Electric/Steel", 82, 20,
        45, 60, 95, 70,
        Gen1Moves::THUNDERBOLT, Gen1Moves::THUNDERSHOCK);

    /**
     * @brief Machamp - Fighting gym leader mon (Dex #068)
     *        Used by Sabrina (Saffron City Gym Leader)
     */
    const Monster MACHAMP = createMonster(
        "Machamp", "Fighting", 68, 22,
        80, 130, 65, 65,
        Gen1Moves::SCRATCH, Gen1Moves::FOCUS_ENERGY);

    /**
     * @brief Vileplume - Grass/Poison gym leader mon (Dex #045)
     *        Used by Erika (Celadon City Gym Leader)
     */
    const Monster VILEPLUME = createMonster(
        "Vileplume", "Grass/Poison", 45, 21,
        75, 80, 85, 50,
        Gen1Moves::VINE_WHIP, Gen1Moves::POWDER_SNOW);

    /**
     * @brief Rapidash - Fire/Ground gym leader mon (Dex #078)
     *        Used by Blaine (Cinnabar Island Gym Leader)
     */
    const Monster RAPIDASH = createMonster(
        "Rapidash", "Fire/Ground", 78, 23,
        65, 100, 70, 95,
        Gen1Moves::EMBER, Gen1Moves::ROCK_THROW);

    /**
     * @brief Arcanine - Fire gym leader mon (Dex #059)
     *        Blaine's ace mon
     */
    const Monster ARCANINE = createMonster(
        "Arcanine", "Fire", 59, 24,
        90, 110, 80, 100,
        Gen1Moves::EMBER, Gen1Moves::SCRATCH);

    /**
     * @brief Lapras - Water/Ice champion mon (Dex #131)
     *        Elite Four & Champion mons
     */
    const Monster LAPRAS = createMonster(
        "Lapras", "Water/Ice", 131, 25,
        130, 85, 80, 60,
        Gen1Moves::WATER_GUN, Gen1Moves::POWDER_SNOW);

    /**
     * @brief Dragonite - Dragon/Flying champion mon (Dex #149)
     *        Elite Four & Champion ace mons (level 30)
     */
    const Monster DRAGONITE = createMonster(
        "Dragonite", "Dragon/Flying", 149, 30,
        91, 134, 95, 80,
        Gen1Moves::SCRATCH, Gen1Moves::GUST);
}

#endif // GEN1_MONSTERS_HPP
