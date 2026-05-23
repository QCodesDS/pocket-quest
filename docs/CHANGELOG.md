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
- Fixed infinite loop in NPC dialog rendering: check moveNext() return value

### Notes

- Gym battle, wild encounter, inventory, bag are stubs — Phase 03/04 will implement
- Build: zero warnings, zero errors on g++ -std=c++17 -Wall -Wextra
