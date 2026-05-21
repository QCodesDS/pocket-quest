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
