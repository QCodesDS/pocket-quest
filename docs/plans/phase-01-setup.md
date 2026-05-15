# Phase 01 — Project Setup & Skeleton

## Mục tiêu

Cấu trúc thư mục chuẩn, Makefile chạy được trên cả Linux và Windows,
skeleton code đủ để các phase sau bắt đầu implement ngay.

## Checklist

### Thư mục

- [ ] `app/core/`, `app/entities/`, `app/world/`, `app/systems/`, `app/data/`, `app/ui/`

### Files cần tạo

- [ ] `app/main.cpp` — welcome screen, nhập tên player
- [ ] `app/core/GameState.hpp` — enum State: MENU, OVERWORLD, BATTLE, GAMEOVER, WIN
- [ ] `app/core/Game.hpp` / `Game.cpp` — skeleton class, chưa có logic
- [ ] `app/entities/Player.hpp` / `Player.cpp` — struct: name, party (rỗng), badges=0
- [ ] `app/ui/UI.hpp` / `UI.cpp` — clearScreen(), printSeparator(), printTitle()
- [ ] `app/ui/MenuUI.hpp` / `MenuUI.cpp` — showWelcome(), showGameOver()

### Build

- [ ] `Makefile` compile toàn bộ app/ — `make`, `make run`, `make clean`
- [ ] Test compile trên Codespaces (Linux)

## Expected output

```bash
╔══════════════════════════════════╗
║       MONSTERQUEST  v1.0         ║
║   A Console RPG — 3 Generations  ║
╚══════════════════════════════════╝

Enter your name: Quoc
Welcome, Quoc! Your adventure begins in Kanto...

[Press Enter to continue]
```

## Cách test

1. `make` → không có lỗi, không có warning
2. `make run` → hiện title screen, nhập tên, tiếp tục
3. `make clean` → xóa binary

## Ghi chú

- Chưa cần implement bất kỳ logic game nào
- `lib/` chưa có → tạo thư mục rỗng tạm, include sau
