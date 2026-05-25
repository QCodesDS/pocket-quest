# CHANGELOG — MonsterQuest

## Quy ước

- Chỉ ghi những gì **đã thực sự hoàn thành**, không ghi kế hoạch
- Mỗi entry: ngày hoàn thành, phase, kết quả cụ thể
- Sau khi ghi, đánh dấu `[x]` tại `docs/plans/master-plan.md`

---

## [Chưa có entry]

Dự án đang ở giai đoạn: **Tài liệu hoàn chỉnh, sẵn sàng bắt đầu Phase 01.**

## [2026-05-21] — Phase 01: Project Setup & Skeleton

### Completed

- Added: Makefile, app/main.cpp, app/core/GameState.hpp, app/core/Game.hpp, app/core/Game.cpp, app/entities/Player.hpp, app/entities/Player.cpp, app/ui/UI.hpp, app/ui/UI.cpp, app/ui/IntroUI.hpp, app/ui/IntroUI.cpp, app/ui/MenuUI.hpp, app/ui/MenuUI.cpp
- Modified: (none)
- Feature: Intro flow works (Title, Oak dialog, name input, starter select) with input validation and aligned UI borders.

### Notes

- Borders aligned by extending top/bottom width by 2 characters in `printBox` and `typeWriteBox`.

## [2026-05-22] — Phase 02: World System

### Completed

- Added: app/data/gen1_cities.hpp (10 Kanto cities with NPC dialog and gym data)
- Added: app/world/City.hpp / City.cpp (LinkedList<std::string> for NPC dialog)
- Added: app/world/Region.hpp / Region.cpp (LinkedList<City> cursor navigation)
- Added: app/world/WorldMap.hpp / WorldMap.cpp (Kanto region manager)
- Added: app/ui/OverworldUI.hpp / OverworldUI.cpp (overworld render + input loop)
- Modified: app/core/Game.cpp (INTRO → OVERWORLD state transition)
- Modified: lib/LinkedList.hpp (added copy constructor + copy assignment operator)

### Features

- 10 Kanto cities navigable via LinkedList<City> cursor API
- NPC dialog stored in LinkedList<std::string> per city
- Wild encounter stub: 30% chance on [1] Go forward
- Gym stub: [3] Challenge Gym appears only at gym cities
- Indigo Plateau badge check: blocks entry if badges < 8
- All cin input validated — no crash on bad input

### Fixes

- Fixed shallow copy crash: added copy constructor/assignment to LinkedList<T>

## [2026-05-22] — Phase 03: Battle System

### Completed

- Added: app/entities/Move.hpp / Move.cpp
- Added: app/entities/Trainer.hpp / Trainer.cpp
- Added: app/entities/Monster.cpp (full implementation)
- Added: app/data/gen1_monsters.hpp (18 monsters: starters, wild, gym leaders, elite four)
- Added: app/data/gen1_moves.hpp (move database, 2-4 moves per monster)
- Added: app/systems/BattleSystem.hpp / BattleSystem.cpp
- Added: app/ui/BattleUI.hpp / BattleUI.cpp
- Modified: app/entities/Monster.hpp (added moves[4] array + level)
- Modified: app/entities/Player.hpp / Player.cpp (enqueue starter into Queue<Monster>)
- Modified: app/core/Game.hpp / Game.cpp (BATTLE state handler)
- Modified: app/ui/OverworldUI.hpp / OverworldUI.cpp (connect wild/gym stubs)
- Created: Makefile (automated build)

### Features

- Turn-based combat: player → enemy alternating
- Queue<Monster> party management — front mon fights, faint → dequeue → next
- Stack<std::string> battle log — max 5 lines displayed
- Damage formula: dmg = (move.power \* atk) / (def > 0 ? def : 1)
- Run attempt: 50% success, wild only — blocked for trainer/gym
- Switch: rotate Queue front → back
- Enemy AI: random move selection (PriorityQueue in Phase 06)

### Fixes

- BattleSystem.cpp: playerAttack() scope error fixed
- BattleUI.cpp: unused parameter suppressed
- OverworldUI.hpp: linker error fixed (include + signature mismatch)

### Notes

- [2] Bag in battle is stub — Phase 04
- Gym battle linkage is stub — Phase 05
- Build: zero warnings, zero errors, 19 .cpp files compiled
- Fixed infinite loop in NPC dialog rendering: check moveNext() return value

### Notes

- Gym battle, wild encounter, inventory, bag are stubs — Phase 03/04 will implement
- Build: zero warnings, zero errors on g++ -std=c++17 -Wall -Wextra

## [2026-05-22] — Phase 04: Inventory System

### Completed

- Added: app/entities/Item.hpp (Item struct: name, healAmount, quantity)
- Added: app/data/items.hpp (POTION +20HP, SUPER_POTION +50HP, FULL_RESTORE full HP)
- Modified: app/systems/InventorySystem.hpp / InventorySystem.cpp (full implementation)
- Modified: app/entities/Player.hpp / Player.cpp (added InventorySystem inventory, init Potion x3)
- Modified: app/systems/BattleSystem.cpp (showBag() replacing case 2 stub)
- Modified: app/ui/BattleUI.hpp / BattleUI.cpp (displayBagMenu using forEach)
- Modified: app/ui/OverworldUI.hpp / OverworldUI.cpp (handleBagMenu outside battle)

### Features

- HashTable<string, Item> from lib/ — O(1) item lookup by name
- Player starts with Potion x3
- [2] Bag in battle: select item → heal active mon → enemy counter-attacks
- Bag outside battle: select item → select target mon → heal
- HP full check: reject use with message, qty unchanged
- Bag empty: show "Your bag is empty." message
- Max 10 item types in bag

### Fixes

- BattleUI.hpp: missing #endif header guard added
- lib/HashTable.hpp: const find() corrected to return &node->value

### Notes

- GRADER comments on all HashTable operations (insert, find, remove, contains, forEach)
- Build: zero warnings, zero errors

## [2026-05-25] — Phase 05: Sort & Polish V1

### Completed

- Added: app/data/gen1_trainers.hpp (8 Gym Leaders, Rival x4, Elite Four, Champion Blue)
- Modified: app/world/City.hpp (added gymCleared field)
- Modified: app/entities/Player.hpp / Player.cpp (added rivalDefeated[4] array)
- Modified: app/ui/OverworldUI.cpp (gym battle flow, rival encounter triggers, Elite Four + Champion sequence, [S] Sort party)
- Modified: app/ui/BattleUI.cpp (bag sorted by name using insertionSort)
- Modified: app/ui/UI.hpp / UI.cpp (added showVictoryScreen)
- Modified: app/core/Game.cpp (WIN state cleanup)
- Modified: lib/Queue.hpp (added copy constructor + copy assignment)
- Modified: lib/Stack.hpp (added copy constructor + copy assignment)

### Features

- 8 Gym Leaders wired: challenge → battle → badge on win → gymCleared
- Rival Blue appears at Cerulean, Saffron, Indigo Plateau (stage-based party)
- Elite Four: 4 consecutive battles, no auto HP restore, bag option between matches
- Champion Blue: final battle → Victory screen on win
- [S] Sort party by HP descending — mergeSort from lib/Algorithms.hpp
- Bag display sorted by name — insertionSort from lib/Algorithms.hpp

### Notes

- GRADER: mergeSort used for party sort, insertionSort used for bag sort
- Build: zero warnings, zero errors, 452KB executable
- V1 milestone reached — project is submittable at this checkpoint

## [2026-05-25] — Phase 08: Gen 1 Complete & Stability Polish

### Completed

- Added: `spc` (Special) field to `Monster` struct & constructors
- Added: Badge boosts logic in `BattleSystem.hpp` / `BattleSystem.cpp` via `applyBadgeBoosts` method
- Modified: `app/ui/OverworldUI.cpp` (Fixed compilation issues with namespace and enum matching, fixed warnings)
- Modified: `app/entities/Player.hpp` & `Player.cpp` (Story quest flags and item collection hooks)
- Modified: `docs/plans/master-plan.md` & `task.md` (Updated project completion status)

### Features

- **Gym Badge Stat Multipliers (Gen 1 mechanics)**: Applied 9/8 (~12.5%) stat multiplier in battles to corresponding attributes based on Gym Badges owned.
  - Boulder (Atk), Cascade (Def), Thunder (Spd), Rainbow (Special), Soul (Def), Marsh (Special), Volcano (Special), Earth (Atk).
- **Core Stability**: All compile-time bugs and warnings are fully resolved. Program builds 100% cleanly on Windows using standard Mingw g++.

