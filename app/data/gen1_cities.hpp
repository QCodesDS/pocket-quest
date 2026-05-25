/**
 * @file  gen1_cities.hpp
 * @brief Dữ liệu hằng số thô cho 10 địa điểm Kanto.
 *        Được nạp vào Region thông qua LinkedList<City> khi khởi tạo.
 */

#ifndef GEN1_CITIES_HPP
#define GEN1_CITIES_HPP

/**
 * @struct CityData
 * @brief  Dữ liệu thô dạng POD để khởi tạo đối tượng City tại runtime.
 */
struct CityData
{
    const char *name;         ///< Tên thành phố
    const char *tag;          ///< Nhãn (GYM X, NO GYM, HOMETOWN, LEAGUE)
    const char *npcDialog[2]; ///< 2 dòng hội thoại NPC
    bool hasGym;              ///< True nếu có Gym Leader
    const char *gymLeader;    ///< Tên Gym Leader (nullptr nếu không có Gym)
};

/// 10 địa điểm Kanto theo thứ tự hành trình (Pallet Town → Indigo Plateau)
const CityData GEN1_CITIES[] = {
    {"Pallet Town",
     "HOMETOWN",
     {"Your journey begins here.",
      "Prof. Oak's lab is nearby."},
     false,
     nullptr},
    {"Viridian City",
     "NO GYM",
     {"The gym leader is away...",
      "Head north to Pewter City."},
     false,
     nullptr},
    {"Pewter City",
     "GYM 1",
     {"Brock's Pokemon are rock solid.",
      "You'll need Water or Grass types."},
     true,
     "Brock"},
    {"Cerulean City",
     "GYM 2",
     {"Misty's Starmie moves at incredible speed.",
      "Watch out for her Water types."},
     true,
     "Misty"},
    {"Vermilion City",
     "GYM 3",
     {"Lt. Surge is known as the Lightning American.",
      "Electric types are tough."},
     true,
     "Lt. Surge"},
    {"Lavender Town",
     "NO GYM",
     {"This town is home to Pokemon Tower...",
      "Team Rocket did something terrible here."},
     false,
     nullptr},
    {"Celadon City",
     "GYM 4",
     {"Strange men in black uniforms seen in the basement.",
      "Team Rocket hides in the Game Corner."},
     true,
     "Erika"},
    {"Fuchsia City",
     "GYM 5",
     {"Koga uses poison and confusion tactics.",
      "Bring Antidotes."},
     true,
     "Koga"},
    {"Saffron City",
     "GYM 6",
     {"Team Rocket has taken over Silph Co.!",
      "Sabrina's psychic powers are terrifying."},
     true,
     "Sabrina"},
    {"Cinnabar Island",
     "GYM 7",
     {"Blaine's Fire Pokemon are hot to handle!",
      "The Gym is locked. Find the Secret Key in the Pokemon Mansion."},
     true,
     "Blaine"},
    {"Indigo Plateau",
     "LEAGUE",
     {"The Pokemon League awaits.",
      "You need 8 badges to enter."},
     false,
     nullptr}};

const int GEN1_CITY_COUNT = 11;

#endif // GEN1_CITIES_HPP
