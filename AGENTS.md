# AGENTS.md — MonsterQuest

> Read this file before doing anything. Rules here apply to all AI tools.

---

## Project

|            |                                                                     |
| ---------- | ------------------------------------------------------------------- |
| **Name**   | Pocket Quest                                                        |
| **Type**   | Console RPG — Pokémon-inspired, Gen 1 Kanto (expandable to Gen 2–3) |
| **Course** | CSC10004 DSA — HCMUS                                                |
| **Goal**   | Use ≥5/7 custom template lib components meaningfully in gameplay    |

---

## Environment

|                  |                                                          |
| ---------------- | -------------------------------------------------------- |
| **Dev**          | Antigravity (Windows)                                    |
| **Graded on**    | Windows (MinGW g++)                                      |
| **Compile**      | `g++ -std=c++17 -Wall -Wextra -I./lib`                   |
| **Clear screen** | `#ifdef _WIN32` → `system("cls")` else `system("clear")` |
| **UI**           | Terminal only — no GUI                                   |

---

## Library → Game Mapping

| Library                  | Used for                               |
| ------------------------ | -------------------------------------- |
| `LinkedList<City>`       | Chain of cities in each Region         |
| `Queue<Monster>`         | Battle party — front mon fights first  |
| `Stack<BattleLog>`       | Last 5 battle log lines                |
| `HashTable<string,Item>` | Inventory — O(1) lookup by item name   |
| `Algorithms`             | Sort party by HP/SPD, sort Pokédex     |
| `PriorityQueue<Move>`    | Trainer AI — highest damage move first |
| `BST<int,Monster>`       | Pokédex — indexed by monster ID        |

---

## Coding Style

- No magic numbers — use `const` or `enum`
- One responsibility per function
- Short comment above every important function, especially lib usage
- No `using namespace std` in `.hpp` files
- Separate `.hpp` (declaration) and `.cpp` (definition) in `app/`
- Validate all `cin` input — never crash on bad input

---

## Hard Rules

- NO STL containers (`std::vector`, `std::map`, `std::queue`, `std::stack`...) as lib replacements
- NO GUI libraries
- NO crashing on invalid input — always validate before use

---

## Per-Phase Workflow

1. Read the phase file: `@docs/plans/phase-XX.md`
2. Implement following the checklist
3. Report: files added / modified / deleted
4. Provide manual test steps
5. Remind to update `docs/CHANGELOG.md` and tick `docs/plans/master-plan.md`

---

## Key Docs

| File                        | Purpose                                  |
| --------------------------- | ---------------------------------------- |
| `docs/plans/master-plan.md` | Phase tracker — check before starting    |
| `docs/CHANGELOG.md`         | Update after every completed phase       |
| `docs/BRD.md`               | Full requirements — @mention when needed |
