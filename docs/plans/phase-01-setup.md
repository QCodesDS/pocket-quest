# Phase 01 — Project Setup & Skeleton

## Mục tiêu

Cấu trúc thư mục chuẩn, Makefile chạy được trên Windows (MinGW),
skeleton code đủ để các phase sau implement ngay.
Flow mở đầu theo phong cách FireRed: title → Oak dialog → nhập tên → starter selection.

## Checklist

### Thư mục

- [ ] `app/core/`
- [ ] `app/entities/`
- [ ] `app/world/`
- [ ] `app/systems/`
- [ ] `app/data/`
- [ ] `app/ui/`

### Files cần tạo

- [ ] `app/main.cpp` — entry point, khởi động game loop
- [ ] `app/core/GameState.hpp` — enum State: MENU, INTRO, OVERWORLD, BATTLE, GAMEOVER, WIN
- [ ] `app/core/Game.hpp` / `Game.cpp` — skeleton class, chưa có logic
- [ ] `app/entities/Player.hpp` / `Player.cpp` — struct: name, badges=0, party rỗng
- [ ] `app/ui/UI.hpp` / `UI.cpp` — `clearScreen()`, `printBox()`, `printSeparator()`, `hpBar()`
- [ ] `app/ui/IntroUI.hpp` / `IntroUI.cpp` — `typeWrite()`, `showTitleScreen()`, `showOakDialog()`, `showNameInput()`, `showStarterSelect()`
- [ ] `app/ui/MenuUI.hpp` / `MenuUI.cpp` — `showGameOver()`, `showVictory()`

### Build

- [ ] `Makefile` — targets: `make`, `make run`, `make clean`
- [ ] Compile sạch: `g++ -std=c++17 -Wall -Wextra -I./lib`

## Expected output — 4 màn liên tiếp

**Màn 1 — Title screen**

```bash
╔══════════════════════════════════════╗
║                                      ║
║            MONSTER QUEST             ║
║                v1.0                  ║
║                                      ║
║            [PRESS ENTER]             ║
║                                      ║
╚══════════════════════════════════════╝
```

**Màn 2 — Oak dialog (typewriter effect)**

```bash
┌──────────────────────────────────────┐
│ PROF. OAK:                           │
│                                      │
│  "In the world you are about to      │
│   enter, you will embark on a grand  │
│   adventure as the hero.             │
│                                      │
│   Speak to people and gather hints   │
│   from every source you find."       │
│                                      │
│                        [ ENTER → ]   │
└──────────────────────────────────────┘
```

**Màn 3 — Nhập tên**

```bash
┌──────────────────────────────────────┐
│ PROF. OAK:                           │
│                                      │
│  "But first — let's begin with your  │
│   name. What is it?"                 │
│                                      │
│  > _                                 │
└──────────────────────────────────────┘
```

**Màn 4 — Starter selection**

```bash
┌──────────────────────────────────────┐
│ PROF. OAK:                           │
│  "Choose your first partner, RED."   │
├──────────────────────────────────────┤
│  [1] Bulbasaur   Grass   HP:45       │
│  [2] Charmander  Fire    HP:39       │
│  [3] Squirtle    Water   HP:44       │
├──────────────────────────────────────┤
│  > _                                 │
└──────────────────────────────────────┘
```

## Cách test

1. `make` → không lỗi, không warning
2. `make run` → 4 màn hiện đúng thứ tự
3. Typewriter effect hiển thị từng ký tự
4. Nhập tên → xác nhận đúng tên
5. Chọn starter 1/2/3 → xác nhận đúng
6. Nhập sai (0, 9, chữ) → in lại thông báo, không crash
7. `make clean` → xóa binary

## Ghi chú

- `typeWrite()` dùng `Sleep()` (Windows) — delay ~25ms/ký tự
- Phase này KHÔNG implement game logic, chỉ skeleton + intro flow
- Starter chọn xong lưu vào `Player.starter`, chưa cần dùng
