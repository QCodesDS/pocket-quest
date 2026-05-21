# Phase 05 — Sort & Polish V1

## Precondition

Inventory hoạt động. World + Battle + Bag đều chạy được.

## Mục tiêu

Dùng `Algorithms` để sort party và items.
Hoàn thiện Gym Leaders + Elite Four Gen 1 (data + flow).
Kết quả: V1 đầy đủ — chơi được từ Pallet Town đến Champion Blue.

## Thư viện

`Algorithms` từ `lib/Algorithms.hpp`

## Checklist

### Sort

- [ ] Sort party theo HP giảm dần trước battle — `mergeSort` hoặc `quickSort`
- [ ] Sort bag theo tên item — `insertionSort` (bag nhỏ, phù hợp)
- [ ] Sort Pokédex theo ID — `mergeSort`
- [ ] Thêm option `[S] Sort party by HP` trong overworld menu

### Data — Gym Leaders

- [ ] `app/data/gen1_trainers.hpp` — 8 Gym Leaders + Elite Four + Champion:
  ```
  Brock      Rock    — Geodude Lv12, Onix Lv14
  Misty      Water   — Staryu Lv18, Starmie Lv21
  Lt. Surge  Elec    — Voltorb Lv21, Pikachu Lv18, Raichu Lv24
  Erika      Grass   — Victreebel Lv29, Tangela Lv24, Vileplume Lv29
  Koga       Poison  — Koffing Lv37, Muk Lv39, Koffing Lv37, Weezing Lv43
  Sabrina    Psychic — Kadabra Lv38, Mr.Mime Lv37, Alakazam Lv43
  Blaine     Fire    — Growlithe Lv42, Ponyta Lv40, Arcanine Lv47
  Giovanni   Ground  — Rhyhorn Lv45, Dugtrio Lv42, Nidoqueen Lv44
  ```
- [ ] Elite Four: Lorelei (Ice), Bruno (Fighting), Agatha (Ghost), Lance (Dragon)
- [ ] Champion: Blue — party 5 mon mixed

### Data — Rival

- [ ] Rival Blue xuất hiện 4 lần — dialog + battle:
  ```
  Lần 1: Pallet Town     — party: starter Lv5
  Lần 2: Cerulean City   — party: starter Lv18 + 1 mon
  Lần 3: Silph Co.       — party: starter Lv40 + 3 mon
  Lần 4: Indigo Plateau  — Champion, party: 5 mon
  ```

### Flow hoàn chỉnh

- [ ] Gym battle: thắng → nhận badge → lưu vào Player.badges
- [ ] Sau 8 badge → Indigo Plateau mở
- [ ] Elite Four liên tiếp: không hồi HP giữa các trận
- [ ] Thắng Champion → màn credits + "Gen 1 Complete!"

### UI

- [ ] Cập nhật title screen: thêm Charizard ASCII art nhỏ
- [ ] Màn Game Over: hiển thị stats (badges đạt được, số trận thắng)
- [ ] Màn Victory: hiện tên player, starter, số badge

## Expected output — Victory screen

```
╔══════════════════════════════════════╗
║                                      ║
║           ★  CHAMPION!  ★           ║
║                                      ║
║  Trainer : RED                       ║
║  Partner : CHARMANDER                ║
║  Badges  : 8/8                       ║
║                                      ║
║  "RED became the Pokémon League      ║
║   Champion!"                         ║
║                                      ║
║          [ PRESS ENTER ]             ║
╚══════════════════════════════════════╝
```

## Cách test

1. Chơi từ đầu → đến Pewter City → challenge Brock → thắng → badge +1
2. Đến Cerulean → Rival chặn → battle bắt buộc
3. Đủ 8 badge → Indigo Plateau mở
4. Elite Four 4 trận liên tiếp → HP không hồi giữa trận
5. Thắng Champion → Victory screen đúng
6. Sort party: `[S]` → party sắp xếp đúng theo HP
7. Bag: item sorted theo tên

## Ghi chú

- Đây là mốc V1 — sau phase này đã đủ điều kiện nộp bài
- Comment mọi chỗ dùng `Algorithms` (sort calls)
- Elite Four không hồi HP là cố ý — tăng độ khó, phải dùng bag
