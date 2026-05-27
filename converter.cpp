/**
 * @file converter.cpp
 * @brief CSV → C++ Header Generator
 *        Đọc pokemon.csv, moves.csv, learnsets.csv
 *        → Generate gen1_monsters.hpp + gen1_learnsets.hpp
 *
 * Usage:
 *   g++ converter.cpp -o converter
 *   ./converter
 *   (Sẽ tạo 2 file .hpp trong app/data/)
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

struct Pokemon
{
    int id;
    std::string name;
    std::string type;
    int hp, atk, def, spd, spAtk, spDef;
    bool starter;
};

struct Move
{
    std::string name;
    std::string type;
    int power, pp;
};

struct Learnset
{
    int pokemon_id;
    std::string pokemon_name;
    int level;
    std::string move_name;
};

// Helpers
std::string sanitize(const std::string &s)
{
    std::string result = s;
    // Replace spaces with underscore
    std::replace(result.begin(), result.end(), ' ', '_');
    // Remove dots
    result.erase(std::remove(result.begin(), result.end(), '.'), result.end());
    // Replace special chars
    std::replace(result.begin(), result.end(), '/', '_');
    // Remove ♂ ♀
    result.erase(std::remove(result.begin(), result.end(), '♂'), result.end());
    result.erase(std::remove(result.begin(), result.end(), '♀'), result.end());
    return result;
}

std::string toUpper(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(), ::toupper);
    return s;
}

std::vector<std::string> split(const std::string &line, char delim = ',')
{
    std::vector<std::string> result;
    std::stringstream ss(line);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        // Trim spaces
        item.erase(0, item.find_first_not_of(" \t"));
        item.erase(item.find_last_not_of(" \t") + 1);
        result.push_back(item);
    }
    return result;
}

// ===== PARSERS =====

std::map<int, Pokemon> parsePokemon(const std::string &file)
{
    std::map<int, Pokemon> result;
    std::ifstream f(file);
    std::string line;
    bool header = true;

    while (std::getline(f, line))
    {
        if (header)
        {
            header = false;
            continue;
        }
        if (line.empty())
            continue;

        auto parts = split(line);
        if (parts.size() < 10)
            continue;

        Pokemon p;
        p.id = std::stoi(parts[0]);
        p.name = parts[1];
        p.type = parts[2];
        p.hp = std::stoi(parts[3]);
        p.atk = std::stoi(parts[4]);
        p.def = std::stoi(parts[5]);
        p.spd = std::stoi(parts[6]);
        p.spAtk = std::stoi(parts[7]);
        p.spDef = std::stoi(parts[8]);
        p.starter = (parts[9] == "yes");

        result[p.id] = p;
    }
    return result;
}

std::map<std::string, Move> parseMoves(const std::string &file)
{
    std::map<std::string, Move> result;
    std::ifstream f(file);
    std::string line;
    bool header = true;

    while (std::getline(f, line))
    {
        if (header)
        {
            header = false;
            continue;
        }
        if (line.empty())
            continue;

        auto parts = split(line);
        if (parts.size() < 4)
            continue;

        Move m;
        m.name = parts[0];
        m.type = parts[1];
        m.power = std::stoi(parts[2]);
        m.pp = std::stoi(parts[3]);

        result[m.name] = m;
    }
    return result;
}

std::vector<Learnset> parseLearnsets(const std::string &file)
{
    std::vector<Learnset> result;
    std::ifstream f(file);
    std::string line;
    bool header = true;

    while (std::getline(f, line))
    {
        if (header)
        {
            header = false;
            continue;
        }
        if (line.empty())
            continue;

        auto parts = split(line);
        if (parts.size() < 4)
            continue;

        Learnset l;
        l.pokemon_id = std::stoi(parts[0]);
        l.pokemon_name = parts[1];
        l.level = std::stoi(parts[2]);
        l.move_name = parts[3];

        result.push_back(l);
    }
    return result;
}

// ===== GENERATORS =====

void generateMonstersHeader(const std::map<int, Pokemon> &pokemons,
                            const std::string &output)
{
    std::ofstream f(output);

    f << "#ifndef GEN1_MONSTERS_ALL_HPP\n";
    f << "#define GEN1_MONSTERS_ALL_HPP\n\n";
    f << "#include \"../entities/Monster.hpp\"\n";
    f << "#include \"gen1_moves.hpp\"\n\n";
    f << "namespace Gen1Monsters\n";
    f << "{\n";
    f << "    // Generated from data/pokemon.csv\n";
    f << "    // Total: " << pokemons.size() << " Pokémon\n\n";

    for (const auto &p_pair : pokemons)
    {
        const Pokemon &p = p_pair.second;
        std::string safeName = toUpper(sanitize(p.name));

        f << "    /**\n";
        f << "     * @brief " << p.name << " - " << p.type << " (Dex #" << p.id << ")\n";
        if (p.starter)
            f << "     *        Starter Pokémon\n";
        f << "     */\n";
        f << "    const Monster " << safeName << "(\n";
        f << "        \"" << p.name << "\", \"" << p.type << "\", " << p.id << ", 5,\n";
        f << "        " << p.hp << ", " << p.atk << ", " << p.def << ", " << p.spd << ", " << p.spAtk << ", " << p.spDef << "\n";
        f << "    );\n\n";
    }

    f << "}\n\n";
    f << "#endif // GEN1_MONSTERS_ALL_HPP\n";

    std::cout << "✅ Generated: " << output << std::endl;
}

void generateLearnsetHeader(const std::vector<Learnset> &learnsets,
                            const std::map<std::string, Move> &moves,
                            const std::string &output)
{
    std::ofstream f(output);

    f << "#ifndef GEN1_LEARNSETS_ALL_HPP\n";
    f << "#define GEN1_LEARNSETS_ALL_HPP\n\n";
    f << "#include \"../entities/Move.hpp\"\n";
    f << "#include \"gen1_moves.hpp\"\n\n";
    f << "namespace Gen1Learnsets\n";
    f << "{\n";
    f << "    // Generated from data/learnsets.csv\n";
    f << "    // Maps (pokemon_id, level) → Move\n\n";

    // Group learnsets by pokemon
    std::map<int, std::vector<Learnset>> by_pokemon;
    for (const auto &ls : learnsets)
    {
        by_pokemon[ls.pokemon_id].push_back(ls);
    }

    for (const auto &poke_pair : by_pokemon)
    {
        int poke_id = poke_pair.first;
        const std::vector<Learnset> &sets = poke_pair.second;

        if (sets.empty())
            continue;

        std::string pokemon_name = sets[0].pokemon_name;
        std::string safeName = toUpper(sanitize(pokemon_name));

        f << "    /**\n";
        f << "     * @brief " << pokemon_name << " learnset (Dex #" << poke_id << ")\n";
        f << "     */\n";
        f << "    struct " << safeName << "_Learnset {\n";
        f << "        static const Move MOVES[];\n";
        f << "        static constexpr int SIZE = " << sets.size() << ";\n";
        f << "    };\n\n";
    }

    // Implement learnsets
    f << "    // ===== IMPLEMENTATIONS =====\n\n";

    for (const auto &poke_pair : by_pokemon)
    {
        int poke_id = poke_pair.first;
        const std::vector<Learnset> &sets = poke_pair.second;

        if (sets.empty())
            continue;

        std::string pokemon_name = sets[0].pokemon_name;
        std::string safeName = toUpper(sanitize(pokemon_name));

        f << "    const Move " << safeName << "_Learnset::MOVES[] = {\n";

        for (const auto &ls : sets)
        {
            auto it = moves.find(ls.move_name);
            if (it != moves.end())
            {
                const Move &m = it->second;
                f << "        Move(\"" << m.name << "\", \"" << m.type << "\", "
                  << m.power << ", " << m.pp << "),  // Lv" << ls.level << "\n";
            }
            else
            {
                // Move not found, use empty move
                f << "        Move(\"" << ls.move_name << "\", \"Normal\", 0, 20),  // Lv" << ls.level << " (NOT FOUND)\n";
            }
        }

        f << "    };\n\n";
    }

    f << "}\n\n";
    f << "#endif // GEN1_LEARNSETS_ALL_HPP\n";

    std::cout << "✅ Generated: " << output << std::endl;
}

int main()
{
    std::cout << "🔄 CSV → C++ Header Generator\n";
    std::cout << "Reading CSV files...\n\n";

    // Parse
    auto pokemons = parsePokemon("data/pokemon.csv");
    auto moves = parseMoves("data/moves.csv");
    auto learnsets = parseLearnsets("data/learnsets.csv");

    std::cout << "✅ Loaded: " << pokemons.size() << " pokémon\n";
    std::cout << "✅ Loaded: " << moves.size() << " moves\n";
    std::cout << "✅ Loaded: " << learnsets.size() << " learnsets\n\n";

    // Generate
    generateMonstersHeader(pokemons, "app/data/gen1_monsters_all.hpp");
    generateLearnsetHeader(learnsets, moves, "app/data/gen1_learnsets_all.hpp");

    std::cout << "\n✨ Done! Generated 2 .hpp files in app/data/\n";

    return 0;
}
