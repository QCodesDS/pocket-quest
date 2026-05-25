#ifndef GEN1_TRAINERS_HPP
#define GEN1_TRAINERS_HPP

#include "gen1_monsters.hpp"
#include "gen1_moves.hpp"
#include "../entities/Trainer.hpp"
#include "../entities/Monster.hpp"

namespace Gen1Trainers
{
    inline Monster levelUpMonster(const Monster &base, int level)
    {
        Monster copy = base;
        copy.level = level;
        return copy;
    }

    inline Trainer makeGymLeaderBrock()
    {
        Trainer trainer("Brock", TrainerType::GYM, 12, "Pewter City");
        trainer.party.enqueue(Gen1Monsters::GEODUDE);
        trainer.party.enqueue(Gen1Monsters::ONIX);
        return trainer;
    }

    inline Trainer makeGymLeaderMisty()
    {
        Trainer trainer("Misty", TrainerType::GYM, 18, "Cerulean City");
        trainer.party.enqueue(Gen1Monsters::STARYU);
        trainer.party.enqueue(Gen1Monsters::STARMIE);
        return trainer;
    }

    inline Trainer makeGymLeaderLtSurge()
    {
        Trainer trainer("Lt. Surge", TrainerType::GYM, 21, "Vermilion City");
        trainer.party.enqueue(Gen1Monsters::MAGNETON);
        trainer.party.enqueue(Gen1Monsters::PIKACHU);
        trainer.party.enqueue(Gen1Monsters::RAICHU);
        return trainer;
    }

    inline Trainer makeGymLeaderErika()
    {
        Trainer trainer("Erika", TrainerType::GYM, 24, "Celadon City");
        trainer.party.enqueue(Gen1Monsters::VILEPLUME);
        trainer.party.enqueue(Gen1Monsters::BULBASAUR);
        trainer.party.enqueue(Gen1Monsters::CATERPIE);
        return trainer;
    }

    inline Trainer makeGymLeaderKoga()
    {
        Trainer trainer("Koga", TrainerType::GYM, 37, "Fuchsia City");
        trainer.party.enqueue(Gen1Monsters::createMonster("Koffing", "Poison", 109, 37, 40, 65, 95, 35, Gen1Moves::SHADOW_BALL, Gen1Moves::DISABLE));
        trainer.party.enqueue(Gen1Monsters::createMonster("Muk", "Poison", 89, 39, 105, 105, 75, 50, Gen1Moves::SCRATCH, Gen1Moves::DISABLE));
        trainer.party.enqueue(Gen1Monsters::createMonster("Weezing", "Poison", 110, 43, 65, 90, 120, 60, Gen1Moves::SHADOW_BALL, Gen1Moves::DISABLE));
        return trainer;
    }

    inline Trainer makeGymLeaderSabrina()
    {
        Trainer trainer("Sabrina", TrainerType::GYM, 43, "Saffron City");
        trainer.party.enqueue(Gen1Monsters::createMonster("Kadabra", "Psychic", 64, 38, 40, 35, 30, 105, Gen1Moves::SHADOW_BALL, Gen1Moves::DISABLE));
        trainer.party.enqueue(Gen1Monsters::createMonster("Mr. Mime", "Psychic", 122, 37, 40, 45, 65, 90, Gen1Moves::SHADOW_BALL, Gen1Moves::FOCUS_ENERGY));
        trainer.party.enqueue(Gen1Monsters::createMonster("Alakazam", "Psychic", 65, 43, 55, 50, 45, 120, Gen1Moves::SHADOW_BALL, Gen1Moves::DISABLE));
        return trainer;
    }

    inline Trainer makeGymLeaderBlaine()
    {
        Trainer trainer("Blaine", TrainerType::GYM, 47, "Cinnabar Island");
        trainer.party.enqueue(Gen1Monsters::createMonster("Growlithe", "Fire", 58, 42, 55, 70, 45, 60, Gen1Moves::EMBER, Gen1Moves::SCRATCH));
        trainer.party.enqueue(Gen1Monsters::createMonster("Ponyta", "Fire", 77, 40, 50, 85, 55, 90, Gen1Moves::EMBER, Gen1Moves::SCRATCH));
        trainer.party.enqueue(levelUpMonster(Gen1Monsters::RAPIDASH, 42));
        trainer.party.enqueue(levelUpMonster(Gen1Monsters::ARCANINE, 47));
        return trainer;
    }

    inline Trainer makeGymLeaderGiovanni()
    {
        Trainer trainer("Giovanni", TrainerType::GYM, 50, "Viridian City");
        trainer.party.enqueue(Gen1Monsters::createMonster("Rhyhorn", "Ground/Rock", 111, 45, 80, 85, 95, 25, Gen1Moves::ROCK_THROW, Gen1Moves::SCRATCH));
        trainer.party.enqueue(Gen1Monsters::createMonster("Dugtrio", "Ground", 51, 42, 35, 80, 50, 120, Gen1Moves::SCRATCH, Gen1Moves::ROCK_THROW));
        trainer.party.enqueue(Gen1Monsters::createMonster("Nidoqueen", "Poison/Ground", 31, 44, 90, 82, 87, 76, Gen1Moves::SCRATCH, Gen1Moves::ROCK_THROW));
        trainer.party.enqueue(Gen1Monsters::createMonster("Nidoking", "Poison/Ground", 34, 45, 81, 92, 77, 85, Gen1Moves::SCRATCH, Gen1Moves::ROCK_THROW));
        return trainer;
    }

    inline Trainer makeEliteLorelei()
    {
        Trainer trainer("Lorelei", TrainerType::ELITE, 50, "Pokemon League");
        trainer.party.enqueue(levelUpMonster(Gen1Monsters::STARMIE, 50));
        trainer.party.enqueue(levelUpMonster(Gen1Monsters::LAPRAS, 50));
        trainer.party.enqueue(levelUpMonster(Gen1Monsters::GASTLY, 48));
        trainer.party.enqueue(levelUpMonster(Gen1Monsters::RAICHU, 49));
        return trainer;
    }

    inline Trainer makeEliteBruno()
    {
        Trainer trainer("Bruno", TrainerType::ELITE, 50, "Pokemon League");
        trainer.party.enqueue(Gen1Monsters::MACHAMP);
        trainer.party.enqueue(levelUpMonster(Gen1Monsters::ONIX, 50));
        trainer.party.enqueue(levelUpMonster(Gen1Monsters::RAPIDASH, 49));
        return trainer;
    }

    inline Trainer makeEliteAgatha()
    {
        Trainer trainer("Agatha", TrainerType::ELITE, 52, "Pokemon League");
        trainer.party.enqueue(levelUpMonster(Gen1Monsters::GASTLY, 52));
        trainer.party.enqueue(levelUpMonster(Gen1Monsters::STARMIE, 51));
        trainer.party.enqueue(levelUpMonster(Gen1Monsters::MAGNETON, 50));
        return trainer;
    }

    inline Trainer makeEliteLance()
    {
        Trainer trainer("Lance", TrainerType::ELITE, 55, "Pokemon League");
        trainer.party.enqueue(Gen1Monsters::DRAGONITE);
        trainer.party.enqueue(levelUpMonster(Gen1Monsters::GASTLY, 52));
        trainer.party.enqueue(levelUpMonster(Gen1Monsters::LAPRAS, 53));
        return trainer;
    }

    inline Trainer makeChampionBlue()
    {
        Trainer trainer("Blue", TrainerType::CHAMPION, 60, "Indigo Plateau");
        trainer.party.enqueue(Gen1Monsters::DRAGONITE);
        trainer.party.enqueue(Gen1Monsters::LAPRAS);
        trainer.party.enqueue(Gen1Monsters::ARCANINE);
        trainer.party.enqueue(Gen1Monsters::STARMIE);
        trainer.party.enqueue(Gen1Monsters::RAICHU);
        return trainer;
    }

    inline Trainer getGymLeaderByName(const std::string &name)
    {
        if (name == "Brock")
            return makeGymLeaderBrock();
        if (name == "Misty")
            return makeGymLeaderMisty();
        if (name == "Lt. Surge")
            return makeGymLeaderLtSurge();
        if (name == "Erika")
            return makeGymLeaderErika();
        if (name == "Koga")
            return makeGymLeaderKoga();
        if (name == "Sabrina")
            return makeGymLeaderSabrina();
        if (name == "Blaine")
            return makeGymLeaderBlaine();
        if (name == "Giovanni")
            return makeGymLeaderGiovanni();
        return Trainer();
    }

    inline Trainer getEliteTrainer(int index)
    {
        switch (index)
        {
        case 0:
            return makeEliteLorelei();
        case 1:
            return makeEliteBruno();
        case 2:
            return makeEliteAgatha();
        case 3:
            return makeEliteLance();
        default:
            return Trainer();
        }
    }

    inline Trainer getChampionTrainer()
    {
        return makeChampionBlue();
    }

    inline Monster getRivalStarter(const std::string &starterName, int level)
    {
        if (starterName == "Bulbasaur")
        {
            Monster mon = Gen1Monsters::CHARMANDER; // Charmander khắc Bulbasaur
            mon.level = level;
            return mon;
        }
        if (starterName == "Charmander")
        {
            Monster mon = Gen1Monsters::SQUIRTLE;   // Squirtle khắc Charmander
            mon.level = level;
            return mon;
        }
        if (starterName == "Squirtle")
        {
            Monster mon = Gen1Monsters::BULBASAUR;  // Bulbasaur khắc Squirtle
            mon.level = level;
            return mon;
        }
        return levelUpMonster(Gen1Monsters::CHARMANDER, level);
    }

    inline Trainer getRivalEncounter(int stage, const std::string &starterName)
    {
        Trainer rival("Blue", TrainerType::GYM, 5, "Rival");
        if (stage == 0)
        {
            rival.party.enqueue(getRivalStarter(starterName, 5));
            return rival;
        }

        if (stage == 1)
        {
            rival.party.enqueue(getRivalStarter(starterName, 18));
            rival.party.enqueue(levelUpMonster(Gen1Monsters::PIKACHU, 18));
            return rival;
        }

        if (stage == 2)
        {
            rival.party.enqueue(getRivalStarter(starterName, 40));
            rival.party.enqueue(levelUpMonster(Gen1Monsters::GEODUDE, 35));
            rival.party.enqueue(levelUpMonster(Gen1Monsters::RATTATA, 34));
            rival.party.enqueue(levelUpMonster(Gen1Monsters::GASTLY, 36));
            return rival;
        }

        rival.type = TrainerType::CHAMPION;
        rival.city = "Indigo Plateau";
        rival.party.enqueue(levelUpMonster(Gen1Monsters::DRAGONITE, 55));
        rival.party.enqueue(levelUpMonster(Gen1Monsters::LAPRAS, 52));
        rival.party.enqueue(levelUpMonster(Gen1Monsters::ARCANINE, 53));
        rival.party.enqueue(levelUpMonster(Gen1Monsters::STARMIE, 50));
        rival.party.enqueue(levelUpMonster(Gen1Monsters::RAICHU, 51));
        return rival;
    }
}

#endif // GEN1_TRAINERS_HPP