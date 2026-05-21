# Phase 03 — Battle System

## Precondition

World system hoạt động, wild encounter stub đã có từ Phase 02.

## Mục tiêu

Turn-based battle hoàn chỉnh: wild encounter + trainer battle.
Dùng `Queue<Monster>` cho party và `Stack<BattleLog>` cho log.

## Thư viện

`Queue<Monster>`, `Stack<BattleLog>` từ `lib/`

## Checklist

### Data

- [ ] `app/data/gen1_monsters.hpp` — 18 monster Gen 1:
  - 3 starter (Bulbasaur, Charmander, Squirtle + evolutions)
  - 6 wild (Pidgey, Rattata, Caterpie, Pikachu, Geodude, Gastly)
  - Gym leader mons (Geodude/Onix, Staryu/Starmie, Voltorb/Raichu...)
- [ ] `app/data/gen1_moves.hpp` — 2–4 moves mỗi mon: name, power, pp

### Entities

- [ ] `app/entities/Monster.hpp` / `Monster.cpp` — struct: name, type, hp, maxHp, atk, def, spd, moves[]
- [ ] `app/entities/Move.hpp` / `Move.cpp` — struct: name, power, pp, maxPp

### Systems

- [ ] `app/systems/BattleSystem.hpp` / `BattleSystem.cpp`:
  - `Queue<Monster>` — player party
  - `Stack<std::string>` — battle log (BattleLog = string)
  - `startWildBattle(Monster enemy)`
  - `startTrainerBattle(Trainer trainer)`
  - `playerAttack(int moveIdx)`
  - `enemyAttack()` — random move (PriorityQueue chưa dùng ở phase này)
  - `checkBattleEnd()` — thắng/thua/chạy

### UI

- [ ] `app/ui/BattleUI.hpp` / `BattleUI.cpp` — render màn battle
- [ ] HP bar dùng `hpBar()` từ UI.hpp
- [ ] Hiển thị 5 dòng log gần nhất từ Stack

### Logic

- [ ] Damage formula: `dmg = (move.power * atk) / def`
- [ ] Run: được với wild, không được với trainer/gym
- [ ] Mon faint → `party.dequeue()` → con tiếp theo lên
- [ ] Hết party → Game Over
- [ ] Thắng wild → về overworld, +gold nhỏ
- [ ] Thắng trainer → về overworld

## Expected output — Màn battle

```
╔══════════════════════════════════════╗
║  Wild PIDGEY   Lv.5                  ║
║  HP [##########]  35/35              ║
╠══════════════════════════════════════╣
║  CHARMANDER    Lv.7                  ║
║  HP [########..]  32/39              ║
╠══════════════════════════════════════╣
║  > CHARMANDER used Ember! 12 dmg     ║
║    Wild PIDGEY used Gust! 8 dmg      ║
║    Wild PIDGEY used Gust! 6 dmg      ║
╠══════════════════════════════════════╣
║     [1] Fight      [2] Bag           ║
║     [3] Switch     [4] Run           ║
╚══════════════════════════════════════╝
> _
```

## Cách test

1. Di chuyển đến khi gặp wild encounter → màn battle hiện đúng
2. `[1] Fight` → chọn move → damage tính đúng công thức
3. Enemy phản công → log cập nhật, HP giảm đúng
4. Mon faint → dequeue, con tiếp theo lên (nếu có)
5. Hết party → Game Over screen
6. `[4] Run` với wild → thoát được, về overworld
7. Battle với trainer → `[4] Run` không được
8. Stack log: chỉ hiển thị 5 dòng gần nhất

## Ghi chú

- Comment rõ chỗ dùng `Queue<Monster>` và `Stack<BattleLog>`
- Trainer AI ở phase này vẫn random move — Phase 06 mới dùng PriorityQueue
- `[2] Bag` và `[3] Switch` có thể là stub "Not implemented yet" — Phase 04 mới làm
