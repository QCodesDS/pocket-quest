/**
 * @file  gen1_cities.hpp
 * @brief Dữ liệu hằng số thô cho 10 địa điểm Kanto.
 *        Được nạp vào Region thông qua LinkedList<City*> khi khởi tạo.
 */

#ifndef GEN1_CITIES_HPP
#define GEN1_CITIES_HPP

/**
 * @struct CityData
 * @brief  Dữ liệu thô dạng POD để khởi tạo đối tượng City tại runtime.
 */
struct CityData {
    const char* name;
    const char* tag;
    const char* dialog[3]; ///< Tối đa 3 dòng dialog NPC
    int         dialogCount;
    bool        hasGym;
    const char* gymLeader;
};

/// 10 địa điểm Kanto theo thứ tự hành trình (Pallet Town → Indigo Plateau)
const CityData GEN1_CITIES[] = {
    {
        "Pallet Town", "HOMETOWN",
        {
            "This peaceful town is where every",
            "legend begins. The road north",
            "leads to your destiny."
        },
        3, false, ""
    },
    {
        "Viridian City", "NO GYM",
        {
            "The Gym Leader seems to be away.",
            "Head north through Viridian Forest",
            "to reach Pewter City."
        },
        3, false, ""
    },
    {
        "Pewter City", "GYM 1",
        {
            "Brock's Rock-type Pokemon are",
            "unyielding as stone. Grass and",
            "Water moves are your best shot."
        },
        3, true, "BROCK"
    },
    {
        "Cerulean City", "GYM 2",
        {
            "Misty is a brilliant Water-type",
            "trainer. Her Starmie moves at",
            "incredible speed. Watch out."
        },
        3, true, "MISTY"
    },
    {
        "Vermilion City", "GYM 3",
        {
            "Lt. Surge, the Lightning American,",
            "swears by overwhelming force.",
            "Ground types are his weakness."
        },
        3, true, "LT. SURGE"
    },
    {
        "Lavender Town", "NO GYM",
        {
            "Pokemon Tower looms over this town.",
            "An eerie melody fills the air.",
            "Stay focused, trainer."
        },
        3, false, ""
    },
    {
        "Celadon City", "GYM 4",
        {
            "Erika's Grass-type team is elegant",
            "but deadly. Fire and Flying moves",
            "will cut right through her."
        },
        3, true, "ERIKA"
    },
    {
        "Fuchsia City", "GYM 5",
        {
            "Koga is a Poison-type ninja master.",
            "His toxic strategies wear you down",
            "slowly. Come prepared."
        },
        3, true, "KOGA"
    },
    {
        "Saffron City", "GYM 6",
        {
            "Sabrina wields Psychic power like",
            "no other. Ghost and Dark types",
            "are the only way forward."
        },
        3, true, "SABRINA"
    },
    {
        "Indigo Plateau", "LEAGUE",
        {
            "The Pokemon League awaits beyond",
            "these gates. Only trainers with",
            "all 8 badges may enter."
        },
        3, false, ""
    }
};

const int GEN1_CITY_COUNT = 10;

#endif // GEN1_CITIES_HPP
