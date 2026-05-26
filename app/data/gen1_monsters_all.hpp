#ifndef GEN1_MONSTERS_ALL_HPP
#define GEN1_MONSTERS_ALL_HPP

#include "../entities/Monster.hpp"
#include "gen1_moves.hpp"

namespace Gen1Monsters
{
    // Generated from data/pokemon.csv
    // Total: 159 Pokémon

    /**
     * @brief Bulbasaur - Grass/Poison (Dex #1)
     *        Starter Pokémon
     */
    const Monster BULBASAUR(
        "Bulbasaur", "Grass/Poison", 1, 5,
        45, 49, 49, 45, 65
    );

    /**
     * @brief Ivysaur - Grass/Poison (Dex #2)
     */
    const Monster IVYSAUR(
        "Ivysaur", "Grass/Poison", 2, 5,
        60, 62, 63, 60, 80
    );

    /**
     * @brief Venusaur - Grass/Poison (Dex #3)
     */
    const Monster VENUSAUR(
        "Venusaur", "Grass/Poison", 3, 5,
        80, 82, 83, 80, 100
    );

    /**
     * @brief Charmander - Fire (Dex #4)
     *        Starter Pokémon
     */
    const Monster CHARMANDER(
        "Charmander", "Fire", 4, 5,
        39, 52, 43, 65, 60
    );

    /**
     * @brief Charmeleon - Fire (Dex #5)
     */
    const Monster CHARMELEON(
        "Charmeleon", "Fire", 5, 5,
        58, 64, 58, 80, 80
    );

    /**
     * @brief Charizard - Fire/Flying (Dex #6)
     */
    const Monster CHARIZARD(
        "Charizard", "Fire/Flying", 6, 5,
        78, 84, 78, 100, 109
    );

    /**
     * @brief Squirtle - Water (Dex #7)
     *        Starter Pokémon
     */
    const Monster SQUIRTLE(
        "Squirtle", "Water", 7, 5,
        44, 48, 65, 43, 50
    );

    /**
     * @brief Wartortle - Water (Dex #8)
     */
    const Monster WARTORTLE(
        "Wartortle", "Water", 8, 5,
        59, 63, 80, 58, 65
    );

    /**
     * @brief Blastoise - Water (Dex #9)
     */
    const Monster BLASTOISE(
        "Blastoise", "Water", 9, 5,
        79, 83, 100, 78, 85
    );

    /**
     * @brief Caterpie - Bug (Dex #10)
     */
    const Monster CATERPIE(
        "Caterpie", "Bug", 10, 5,
        45, 52, 43, 35, 20
    );

    /**
     * @brief Metapod - Bug (Dex #11)
     */
    const Monster METAPOD(
        "Metapod", "Bug", 11, 5,
        50, 65, 55, 30, 25
    );

    /**
     * @brief Butterfree - Bug/Flying (Dex #12)
     */
    const Monster BUTTERFREE(
        "Butterfree", "Bug/Flying", 12, 5,
        60, 55, 72, 65, 60
    );

    /**
     * @brief Weedle - Bug/Poison (Dex #13)
     */
    const Monster WEEDLE(
        "Weedle", "Bug/Poison", 13, 5,
        40, 35, 30, 50, 20
    );

    /**
     * @brief Kakuna - Bug/Poison (Dex #14)
     */
    const Monster KAKUNA(
        "Kakuna", "Bug/Poison", 14, 5,
        45, 25, 50, 35, 25
    );

    /**
     * @brief Beedrill - Bug/Poison (Dex #15)
     */
    const Monster BEEDRILL(
        "Beedrill", "Bug/Poison", 15, 5,
        65, 90, 40, 75, 45
    );

    /**
     * @brief Pidgeot - Normal/Flying (Dex #16)
     */
    const Monster PIDGEOT(
        "Pidgeot", "Normal/Flying", 16, 5,
        83, 100, 65, 111, 77
    );

    /**
     * @brief Pidgeotto - Normal/Flying (Dex #17)
     */
    const Monster PIDGEOTTO(
        "Pidgeotto", "Normal/Flying", 17, 5,
        63, 60, 55, 71, 50
    );

    /**
     * @brief Pidgeot - Normal/Flying (Dex #18)
     */
    const Monster PIDGEOT(
        "Pidgeot", "Normal/Flying", 18, 5,
        83, 100, 65, 111, 77
    );

    /**
     * @brief Rattata - Normal (Dex #19)
     */
    const Monster RATTATA(
        "Rattata", "Normal", 19, 5,
        30, 56, 35, 72, 25
    );

    /**
     * @brief Raticate - Normal (Dex #20)
     */
    const Monster RATICATE(
        "Raticate", "Normal", 20, 5,
        55, 81, 60, 97, 50
    );

    /**
     * @brief Spearow - Normal/Flying (Dex #21)
     */
    const Monster SPEAROW(
        "Spearow", "Normal/Flying", 21, 5,
        40, 60, 30, 70, 31
    );

    /**
     * @brief Fearow - Normal/Flying (Dex #22)
     */
    const Monster FEAROW(
        "Fearow", "Normal/Flying", 22, 5,
        65, 90, 65, 100, 61
    );

    /**
     * @brief Ekans - Poison (Dex #23)
     */
    const Monster EKANS(
        "Ekans", "Poison", 23, 5,
        35, 60, 44, 55, 40
    );

    /**
     * @brief Arbok - Poison (Dex #24)
     */
    const Monster ARBOK(
        "Arbok", "Poison", 24, 5,
        60, 95, 69, 80, 65
    );

    /**
     * @brief Pikachu - Electric (Dex #25)
     */
    const Monster PIKACHU(
        "Pikachu", "Electric", 25, 5,
        35, 55, 40, 90, 50
    );

    /**
     * @brief Raichu - Electric (Dex #26)
     */
    const Monster RAICHU(
        "Raichu", "Electric", 26, 5,
        60, 90, 55, 100, 90
    );

    /**
     * @brief Sandshrew - Ground (Dex #27)
     */
    const Monster SANDSHREW(
        "Sandshrew", "Ground", 27, 5,
        50, 75, 66, 45, 30
    );

    /**
     * @brief Sandslash - Ground (Dex #28)
     */
    const Monster SANDSLASH(
        "Sandslash", "Ground", 28, 5,
        75, 100, 110, 65, 55
    );

    /**
     * @brief Nidoran♀ - Poison (Dex #29)
     */
    const Monster NIDORAN♀(
        "Nidoran♀", "Poison", 29, 5,
        55, 47, 52, 41, 40
    );

    /**
     * @brief Nidorina - Poison (Dex #30)
     */
    const Monster NIDORINA(
        "Nidorina", "Poison", 30, 5,
        70, 62, 67, 56, 55
    );

    /**
     * @brief Nidoqueen - Poison/Ground (Dex #31)
     */
    const Monster NIDOQUEEN(
        "Nidoqueen", "Poison/Ground", 31, 5,
        90, 92, 87, 76, 75
    );

    /**
     * @brief Nidoran♂ - Poison (Dex #32)
     */
    const Monster NIDORAN♂(
        "Nidoran♂", "Poison", 32, 5,
        46, 57, 40, 50, 40
    );

    /**
     * @brief Nidorino - Poison (Dex #33)
     */
    const Monster NIDORINO(
        "Nidorino", "Poison", 33, 5,
        61, 72, 55, 65, 55
    );

    /**
     * @brief Nidoking - Poison/Ground (Dex #34)
     */
    const Monster NIDOKING(
        "Nidoking", "Poison/Ground", 34, 5,
        81, 102, 77, 85, 75
    );

    /**
     * @brief Clefairy - Normal (Dex #35)
     */
    const Monster CLEFAIRY(
        "Clefairy", "Normal", 35, 5,
        35, 48, 48, 35, 60
    );

    /**
     * @brief Clefable - Normal (Dex #36)
     */
    const Monster CLEFABLE(
        "Clefable", "Normal", 36, 5,
        73, 60, 73, 60, 73
    );

    /**
     * @brief Vulpix - Fire (Dex #37)
     */
    const Monster VULPIX(
        "Vulpix", "Fire", 37, 5,
        38, 41, 40, 65, 65
    );

    /**
     * @brief Ninetales - Fire (Dex #38)
     */
    const Monster NINETALES(
        "Ninetales", "Fire", 38, 5,
        73, 76, 75, 100, 100
    );

    /**
     * @brief Jigglypuff - Normal (Dex #39)
     */
    const Monster JIGGLYPUFF(
        "Jigglypuff", "Normal", 39, 5,
        115, 40, 20, 20, 25
    );

    /**
     * @brief Wigglytuff - Normal (Dex #40)
     */
    const Monster WIGGLYTUFF(
        "Wigglytuff", "Normal", 40, 5,
        140, 70, 45, 45, 75
    );

    /**
     * @brief Zubat - Poison/Flying (Dex #41)
     */
    const Monster ZUBAT(
        "Zubat", "Poison/Flying", 41, 5,
        40, 45, 35, 55, 30
    );

    /**
     * @brief Golbat - Poison/Flying (Dex #42)
     */
    const Monster GOLBAT(
        "Golbat", "Poison/Flying", 42, 5,
        75, 80, 70, 90, 65
    );

    /**
     * @brief Oddish - Grass/Poison (Dex #43)
     */
    const Monster ODDISH(
        "Oddish", "Grass/Poison", 43, 5,
        45, 50, 55, 30, 75
    );

    /**
     * @brief Gloom - Grass/Poison (Dex #44)
     */
    const Monster GLOOM(
        "Gloom", "Grass/Poison", 44, 5,
        60, 65, 70, 40, 85
    );

    /**
     * @brief Vileplume - Grass/Poison (Dex #45)
     */
    const Monster VILEPLUME(
        "Vileplume", "Grass/Poison", 45, 5,
        75, 80, 85, 50, 100
    );

    /**
     * @brief Paras - Bug/Grass (Dex #46)
     */
    const Monster PARAS(
        "Paras", "Bug/Grass", 46, 5,
        35, 70, 55, 25, 55
    );

    /**
     * @brief Parasect - Bug/Grass (Dex #47)
     */
    const Monster PARASECT(
        "Parasect", "Bug/Grass", 47, 5,
        60, 95, 80, 30, 60
    );

    /**
     * @brief Venonat - Bug/Poison (Dex #48)
     */
    const Monster VENONAT(
        "Venonat", "Bug/Poison", 48, 5,
        60, 55, 50, 45, 40
    );

    /**
     * @brief Venomoth - Bug/Poison (Dex #49)
     */
    const Monster VENOMOTH(
        "Venomoth", "Bug/Poison", 49, 5,
        70, 65, 60, 90, 75
    );

    /**
     * @brief Diglett - Ground (Dex #50)
     */
    const Monster DIGLETT(
        "Diglett", "Ground", 50, 5,
        10, 55, 25, 95, 35
    );

    /**
     * @brief Dugtrio - Ground (Dex #51)
     */
    const Monster DUGTRIO(
        "Dugtrio", "Ground", 51, 5,
        35, 80, 50, 120, 70
    );

    /**
     * @brief Meowth - Normal (Dex #52)
     */
    const Monster MEOWTH(
        "Meowth", "Normal", 52, 5,
        40, 45, 35, 90, 40
    );

    /**
     * @brief Persian - Normal (Dex #53)
     */
    const Monster PERSIAN(
        "Persian", "Normal", 53, 5,
        65, 70, 60, 115, 65
    );

    /**
     * @brief Psyduck - Water (Dex #54)
     */
    const Monster PSYDUCK(
        "Psyduck", "Water", 54, 5,
        50, 52, 48, 55, 65
    );

    /**
     * @brief Golduck - Water (Dex #55)
     */
    const Monster GOLDUCK(
        "Golduck", "Water", 55, 5,
        80, 82, 78, 85, 95
    );

    /**
     * @brief Mankey - Fighting (Dex #56)
     */
    const Monster MANKEY(
        "Mankey", "Fighting", 56, 5,
        40, 80, 35, 70, 35
    );

    /**
     * @brief Primeape - Fighting (Dex #57)
     */
    const Monster PRIMEAPE(
        "Primeape", "Fighting", 57, 5,
        65, 105, 60, 95, 60
    );

    /**
     * @brief Growlithe - Fire (Dex #58)
     */
    const Monster GROWLITHE(
        "Growlithe", "Fire", 58, 5,
        55, 70, 45, 60, 70
    );

    /**
     * @brief Arcanine - Fire (Dex #59)
     */
    const Monster ARCANINE(
        "Arcanine", "Fire", 59, 5,
        90, 110, 80, 100, 80
    );

    /**
     * @brief Poliwag - Water (Dex #60)
     */
    const Monster POLIWAG(
        "Poliwag", "Water", 60, 5,
        40, 50, 40, 90, 40
    );

    /**
     * @brief Poliwhirl - Water (Dex #61)
     */
    const Monster POLIWHIRL(
        "Poliwhirl", "Water", 61, 5,
        65, 65, 65, 90, 50
    );

    /**
     * @brief Poliwrath - Water/Fighting (Dex #62)
     */
    const Monster POLIWRATH(
        "Poliwrath", "Water/Fighting", 62, 5,
        90, 95, 95, 70, 70
    );

    /**
     * @brief Abra - Psychic (Dex #63)
     */
    const Monster ABRA(
        "Abra", "Psychic", 63, 5,
        25, 20, 15, 90, 105
    );

    /**
     * @brief Kadabra - Psychic (Dex #64)
     */
    const Monster KADABRA(
        "Kadabra", "Psychic", 64, 5,
        40, 35, 30, 105, 120
    );

    /**
     * @brief Alakazam - Psychic (Dex #65)
     */
    const Monster ALAKAZAM(
        "Alakazam", "Psychic", 65, 5,
        55, 50, 45, 120, 135
    );

    /**
     * @brief Machop - Fighting (Dex #66)
     */
    const Monster MACHOP(
        "Machop", "Fighting", 66, 5,
        70, 80, 50, 35, 35
    );

    /**
     * @brief Machoke - Fighting (Dex #67)
     */
    const Monster MACHOKE(
        "Machoke", "Fighting", 67, 5,
        80, 100, 70, 45, 50
    );

    /**
     * @brief Machamp - Fighting (Dex #68)
     */
    const Monster MACHAMP(
        "Machamp", "Fighting", 68, 5,
        80, 130, 65, 65, 65
    );

    /**
     * @brief Bellsprout - Grass/Poison (Dex #69)
     */
    const Monster BELLSPROUT(
        "Bellsprout", "Grass/Poison", 69, 5,
        50, 75, 35, 40, 70
    );

    /**
     * @brief Weepinbell - Grass/Poison (Dex #70)
     */
    const Monster WEEPINBELL(
        "Weepinbell", "Grass/Poison", 70, 5,
        65, 90, 50, 55, 85
    );

    /**
     * @brief Victreebel - Grass/Poison (Dex #71)
     */
    const Monster VICTREEBEL(
        "Victreebel", "Grass/Poison", 71, 5,
        80, 105, 65, 72, 100
    );

    /**
     * @brief Tentacool - Water/Poison (Dex #72)
     */
    const Monster TENTACOOL(
        "Tentacool", "Water/Poison", 72, 5,
        40, 40, 35, 70, 100
    );

    /**
     * @brief Tentacruel - Water/Poison (Dex #73)
     */
    const Monster TENTACRUEL(
        "Tentacruel", "Water/Poison", 73, 5,
        80, 70, 65, 100, 120
    );

    /**
     * @brief Geodude - Rock/Ground (Dex #74)
     */
    const Monster GEODUDE(
        "Geodude", "Rock/Ground", 74, 5,
        40, 80, 100, 20, 30
    );

    /**
     * @brief Graveler - Rock/Ground (Dex #75)
     */
    const Monster GRAVELER(
        "Graveler", "Rock/Ground", 75, 5,
        55, 95, 115, 35, 45
    );

    /**
     * @brief Golem - Rock/Ground (Dex #76)
     */
    const Monster GOLEM(
        "Golem", "Rock/Ground", 76, 5,
        80, 120, 130, 45, 55
    );

    /**
     * @brief Ponyta - Fire (Dex #77)
     */
    const Monster PONYTA(
        "Ponyta", "Fire", 77, 5,
        50, 85, 55, 90, 65
    );

    /**
     * @brief Rapidash - Fire (Dex #78)
     */
    const Monster RAPIDASH(
        "Rapidash", "Fire", 78, 5,
        65, 100, 70, 105, 80
    );

    /**
     * @brief Slowpoke - Water/Psychic (Dex #79)
     */
    const Monster SLOWPOKE(
        "Slowpoke", "Water/Psychic", 79, 5,
        90, 65, 65, 40, 40
    );

    /**
     * @brief Slowbro - Water/Psychic (Dex #80)
     */
    const Monster SLOWBRO(
        "Slowbro", "Water/Psychic", 80, 5,
        95, 75, 110, 30, 80
    );

    /**
     * @brief Seel - Water (Dex #81)
     */
    const Monster SEEL(
        "Seel", "Water", 81, 5,
        65, 45, 55, 45, 70
    );

    /**
     * @brief Dewgong - Water/Ice (Dex #82)
     */
    const Monster DEWGONG(
        "Dewgong", "Water/Ice", 82, 5,
        90, 70, 80, 70, 95
    );

    /**
     * @brief Shellder - Water (Dex #83)
     */
    const Monster SHELLDER(
        "Shellder", "Water", 83, 5,
        30, 65, 100, 40, 45
    );

    /**
     * @brief Cloyster - Water (Dex #84)
     */
    const Monster CLOYSTER(
        "Cloyster", "Water", 84, 5,
        50, 95, 180, 70, 85
    );

    /**
     * @brief Gastly - Ghost/Poison (Dex #85)
     */
    const Monster GASTLY(
        "Gastly", "Ghost/Poison", 85, 5,
        30, 35, 30, 80, 100
    );

    /**
     * @brief Haunter - Ghost/Poison (Dex #86)
     */
    const Monster HAUNTER(
        "Haunter", "Ghost/Poison", 86, 5,
        45, 50, 45, 95, 115
    );

    /**
     * @brief Gengar - Ghost/Poison (Dex #87)
     */
    const Monster GENGAR(
        "Gengar", "Ghost/Poison", 87, 5,
        65, 65, 60, 130, 130
    );

    /**
     * @brief Onix - Rock/Ground (Dex #88)
     */
    const Monster ONIX(
        "Onix", "Rock/Ground", 88, 5,
        35, 45, 160, 30, 30
    );

    /**
     * @brief Drowzee - Psychic (Dex #89)
     */
    const Monster DROWZEE(
        "Drowzee", "Psychic", 89, 5,
        60, 48, 45, 42, 43
    );

    /**
     * @brief Hypno - Psychic (Dex #90)
     */
    const Monster HYPNO(
        "Hypno", "Psychic", 90, 5,
        85, 73, 70, 67, 73
    );

    /**
     * @brief Krabby - Water (Dex #91)
     */
    const Monster KRABBY(
        "Krabby", "Water", 91, 5,
        30, 105, 90, 50, 25
    );

    /**
     * @brief Kingler - Water (Dex #92)
     */
    const Monster KINGLER(
        "Kingler", "Water", 92, 5,
        55, 130, 115, 75, 50
    );

    /**
     * @brief Voltorb - Electric (Dex #93)
     */
    const Monster VOLTORB(
        "Voltorb", "Electric", 93, 5,
        40, 30, 50, 100, 55
    );

    /**
     * @brief Electrode - Electric (Dex #94)
     */
    const Monster ELECTRODE(
        "Electrode", "Electric", 94, 5,
        60, 50, 70, 140, 80
    );

    /**
     * @brief Exeggcute - Grass/Psychic (Dex #95)
     */
    const Monster EXEGGCUTE(
        "Exeggcute", "Grass/Psychic", 95, 5,
        60, 40, 80, 40, 60
    );

    /**
     * @brief Exeggutor - Grass/Psychic (Dex #96)
     */
    const Monster EXEGGUTOR(
        "Exeggutor", "Grass/Psychic", 96, 5,
        95, 95, 85, 55, 125
    );

    /**
     * @brief Cubone - Ground (Dex #97)
     */
    const Monster CUBONE(
        "Cubone", "Ground", 97, 5,
        50, 75, 40, 35, 40
    );

    /**
     * @brief Marowak - Ground (Dex #98)
     */
    const Monster MAROWAK(
        "Marowak", "Ground", 98, 5,
        60, 80, 100, 45, 50
    );

    /**
     * @brief Hitmonlee - Fighting (Dex #99)
     */
    const Monster HITMONLEE(
        "Hitmonlee", "Fighting", 99, 5,
        50, 120, 53, 87, 35
    );

    /**
     * @brief Hitmonchan - Fighting (Dex #100)
     */
    const Monster HITMONCHAN(
        "Hitmonchan", "Fighting", 100, 5,
        50, 105, 79, 76, 35
    );

    /**
     * @brief Lickitung - Normal (Dex #101)
     */
    const Monster LICKITUNG(
        "Lickitung", "Normal", 101, 5,
        90, 55, 75, 30, 60
    );

    /**
     * @brief Koffing - Poison (Dex #102)
     */
    const Monster KOFFING(
        "Koffing", "Poison", 102, 5,
        40, 65, 95, 35, 60
    );

    /**
     * @brief Weezing - Poison (Dex #103)
     */
    const Monster WEEZING(
        "Weezing", "Poison", 103, 5,
        65, 90, 120, 60, 85
    );

    /**
     * @brief Rhyhorn - Ground/Rock (Dex #104)
     */
    const Monster RHYHORN(
        "Rhyhorn", "Ground/Rock", 104, 5,
        80, 85, 95, 32, 30
    );

    /**
     * @brief Rhydon - Ground/Rock (Dex #105)
     */
    const Monster RHYDON(
        "Rhydon", "Ground/Rock", 105, 5,
        105, 130, 120, 40, 45
    );

    /**
     * @brief Chansey - Normal (Dex #106)
     */
    const Monster CHANSEY(
        "Chansey", "Normal", 106, 5,
        250, 5, 5, 30, 35
    );

    /**
     * @brief Tangela - Grass (Dex #107)
     */
    const Monster TANGELA(
        "Tangela", "Grass", 107, 5,
        65, 55, 115, 60, 100
    );

    /**
     * @brief Kangaskhan - Normal (Dex #108)
     */
    const Monster KANGASKHAN(
        "Kangaskhan", "Normal", 108, 5,
        105, 95, 80, 90, 40
    );

    /**
     * @brief Horsea - Water (Dex #109)
     */
    const Monster HORSEA(
        "Horsea", "Water", 109, 5,
        30, 40, 70, 60, 70
    );

    /**
     * @brief Seadra - Water (Dex #110)
     */
    const Monster SEADRA(
        "Seadra", "Water", 110, 5,
        55, 65, 95, 85, 95
    );

    /**
     * @brief Goldeen - Water (Dex #111)
     */
    const Monster GOLDEEN(
        "Goldeen", "Water", 111, 5,
        45, 67, 60, 63, 50
    );

    /**
     * @brief Seaking - Water (Dex #112)
     */
    const Monster SEAKING(
        "Seaking", "Water", 112, 5,
        80, 92, 65, 68, 80
    );

    /**
     * @brief Staryu - Water (Dex #113)
     */
    const Monster STARYU(
        "Staryu", "Water", 113, 5,
        30, 45, 55, 85, 70
    );

    /**
     * @brief Starmie - Water/Psychic (Dex #114)
     */
    const Monster STARMIE(
        "Starmie", "Water/Psychic", 114, 5,
        60, 75, 85, 115, 100
    );

    /**
     * @brief Mr. Mime - Psychic (Dex #115)
     */
    const Monster MR_MIME(
        "Mr. Mime", "Psychic", 115, 5,
        40, 45, 65, 90, 100
    );

    /**
     * @brief Scyther - Bug/Flying (Dex #116)
     */
    const Monster SCYTHER(
        "Scyther", "Bug/Flying", 116, 5,
        70, 110, 80, 105, 55
    );

    /**
     * @brief Jynx - Ice/Psychic (Dex #117)
     */
    const Monster JYNX(
        "Jynx", "Ice/Psychic", 117, 5,
        65, 50, 35, 95, 95
    );

    /**
     * @brief Electabuzz - Electric (Dex #118)
     */
    const Monster ELECTABUZZ(
        "Electabuzz", "Electric", 118, 5,
        65, 83, 57, 105, 85
    );

    /**
     * @brief Magby - Fire (Dex #119)
     */
    const Monster MAGBY(
        "Magby", "Fire", 119, 5,
        65, 83, 57, 105, 85
    );

    /**
     * @brief Magnemite - Electric/Steel (Dex #120)
     */
    const Monster MAGNEMITE(
        "Magnemite", "Electric/Steel", 120, 5,
        25, 35, 70, 45, 95
    );

    /**
     * @brief Magneton - Electric/Steel (Dex #121)
     */
    const Monster MAGNETON(
        "Magneton", "Electric/Steel", 121, 5,
        50, 60, 95, 70, 120
    );

    /**
     * @brief Farfetch'd - Normal/Flying (Dex #122)
     */
    const Monster FARFETCH'D(
        "Farfetch'd", "Normal/Flying", 122, 5,
        52, 90, 55, 58, 58
    );

    /**
     * @brief Doduo - Normal/Flying (Dex #123)
     */
    const Monster DODUO(
        "Doduo", "Normal/Flying", 123, 5,
        35, 85, 45, 75, 35
    );

    /**
     * @brief Dodrio - Normal/Flying (Dex #124)
     */
    const Monster DODRIO(
        "Dodrio", "Normal/Flying", 124, 5,
        60, 110, 70, 100, 60
    );

    /**
     * @brief Seel - Water (Dex #125)
     */
    const Monster SEEL(
        "Seel", "Water", 125, 5,
        65, 45, 55, 45, 70
    );

    /**
     * @brief Dewgong - Water/Ice (Dex #126)
     */
    const Monster DEWGONG(
        "Dewgong", "Water/Ice", 126, 5,
        90, 70, 80, 70, 95
    );

    /**
     * @brief Shellder - Water (Dex #127)
     */
    const Monster SHELLDER(
        "Shellder", "Water", 127, 5,
        30, 65, 100, 40, 45
    );

    /**
     * @brief Cloyster - Water (Dex #128)
     */
    const Monster CLOYSTER(
        "Cloyster", "Water", 128, 5,
        50, 95, 180, 70, 85
    );

    /**
     * @brief Krabby - Water (Dex #129)
     */
    const Monster KRABBY(
        "Krabby", "Water", 129, 5,
        30, 105, 90, 50, 25
    );

    /**
     * @brief Kingler - Water (Dex #130)
     */
    const Monster KINGLER(
        "Kingler", "Water", 130, 5,
        55, 130, 115, 75, 50
    );

    /**
     * @brief Horsea - Water (Dex #131)
     */
    const Monster HORSEA(
        "Horsea", "Water", 131, 5,
        30, 40, 70, 60, 70
    );

    /**
     * @brief Seadra - Water (Dex #132)
     */
    const Monster SEADRA(
        "Seadra", "Water", 132, 5,
        55, 65, 95, 85, 95
    );

    /**
     * @brief Goldeen - Water (Dex #133)
     */
    const Monster GOLDEEN(
        "Goldeen", "Water", 133, 5,
        45, 67, 60, 63, 50
    );

    /**
     * @brief Seaking - Water (Dex #134)
     */
    const Monster SEAKING(
        "Seaking", "Water", 134, 5,
        80, 92, 65, 68, 80
    );

    /**
     * @brief Staryu - Water (Dex #135)
     */
    const Monster STARYU(
        "Staryu", "Water", 135, 5,
        30, 45, 55, 85, 70
    );

    /**
     * @brief Starmie - Water/Psychic (Dex #136)
     */
    const Monster STARMIE(
        "Starmie", "Water/Psychic", 136, 5,
        60, 75, 85, 115, 100
    );

    /**
     * @brief Magikarp - Water (Dex #137)
     */
    const Monster MAGIKARP(
        "Magikarp", "Water", 137, 5,
        20, 10, 55, 80, 20
    );

    /**
     * @brief Gyarados - Water/Flying (Dex #138)
     */
    const Monster GYARADOS(
        "Gyarados", "Water/Flying", 138, 5,
        95, 125, 79, 81, 100
    );

    /**
     * @brief Lapras - Water/Ice (Dex #139)
     */
    const Monster LAPRAS(
        "Lapras", "Water/Ice", 139, 5,
        130, 85, 80, 60, 95
    );

    /**
     * @brief Ditto - Normal (Dex #140)
     */
    const Monster DITTO(
        "Ditto", "Normal", 140, 5,
        48, 48, 48, 48, 48
    );

    /**
     * @brief Eevee - Normal (Dex #141)
     */
    const Monster EEVEE(
        "Eevee", "Normal", 141, 5,
        55, 55, 50, 55, 65
    );

    /**
     * @brief Vaporeon - Water (Dex #142)
     */
    const Monster VAPOREON(
        "Vaporeon", "Water", 142, 5,
        130, 65, 60, 65, 110
    );

    /**
     * @brief Jolteon - Electric (Dex #143)
     */
    const Monster JOLTEON(
        "Jolteon", "Electric", 143, 5,
        65, 65, 60, 130, 110
    );

    /**
     * @brief Flareon - Fire (Dex #144)
     */
    const Monster FLAREON(
        "Flareon", "Fire", 144, 5,
        65, 130, 60, 65, 110
    );

    /**
     * @brief Porygon - Normal (Dex #145)
     */
    const Monster PORYGON(
        "Porygon", "Normal", 145, 5,
        65, 60, 70, 40, 75
    );

    /**
     * @brief Omanyte - Rock/Water (Dex #146)
     */
    const Monster OMANYTE(
        "Omanyte", "Rock/Water", 146, 5,
        35, 40, 100, 35, 90
    );

    /**
     * @brief Omastar - Rock/Water (Dex #147)
     */
    const Monster OMASTAR(
        "Omastar", "Rock/Water", 147, 5,
        70, 60, 125, 55, 115
    );

    /**
     * @brief Kabuto - Rock/Water (Dex #148)
     */
    const Monster KABUTO(
        "Kabuto", "Rock/Water", 148, 5,
        30, 80, 90, 55, 45
    );

    /**
     * @brief Kabutops - Rock/Water (Dex #149)
     */
    const Monster KABUTOPS(
        "Kabutops", "Rock/Water", 149, 5,
        60, 115, 105, 80, 70
    );

    /**
     * @brief Aerodactyl - Rock/Flying (Dex #150)
     */
    const Monster AERODACTYL(
        "Aerodactyl", "Rock/Flying", 150, 5,
        80, 105, 65, 130, 60
    );

    /**
     * @brief Snorlax - Normal (Dex #151)
     */
    const Monster SNORLAX(
        "Snorlax", "Normal", 151, 5,
        150, 110, 65, 30, 65
    );

    /**
     * @brief Articuno - Ice/Flying (Dex #152)
     */
    const Monster ARTICUNO(
        "Articuno", "Ice/Flying", 152, 5,
        90, 85, 100, 85, 95
    );

    /**
     * @brief Zapdos - Electric/Flying (Dex #153)
     */
    const Monster ZAPDOS(
        "Zapdos", "Electric/Flying", 153, 5,
        90, 90, 85, 100, 125
    );

    /**
     * @brief Moltres - Fire/Flying (Dex #154)
     */
    const Monster MOLTRES(
        "Moltres", "Fire/Flying", 154, 5,
        90, 100, 90, 90, 125
    );

    /**
     * @brief Dratini - Dragon (Dex #155)
     */
    const Monster DRATINI(
        "Dratini", "Dragon", 155, 5,
        41, 64, 45, 50, 50
    );

    /**
     * @brief Dragonair - Dragon (Dex #156)
     */
    const Monster DRAGONAIR(
        "Dragonair", "Dragon", 156, 5,
        61, 84, 65, 70, 70
    );

    /**
     * @brief Dragonite - Dragon/Flying (Dex #157)
     */
    const Monster DRAGONITE(
        "Dragonite", "Dragon/Flying", 157, 5,
        91, 134, 95, 80, 100
    );

    /**
     * @brief Mewtwo - Psychic (Dex #158)
     */
    const Monster MEWTWO(
        "Mewtwo", "Psychic", 158, 5,
        106, 110, 90, 130, 154
    );

    /**
     * @brief Mew - Psychic (Dex #159)
     */
    const Monster MEW(
        "Mew", "Psychic", 159, 5,
        100, 100, 100, 100, 100
    );

}

#endif // GEN1_MONSTERS_ALL_HPP
