# Phase 02 — World System

## Precondition

Player đã có tên + starter từ Phase 01.

## Mục tiêu

Xây dựng hệ thống di chuyển qua 10 địa điểm Kanto bằng `LinkedList<City>`.
Mỗi địa điểm có NPC dialog hint cốt truyện. Wild encounter ngẫu nhiên khi di chuyển.

## Thư viện

`LinkedList<City>` từ `lib/LinkedList.hpp`

## Checklist

### Data

- [ ] `app/data/gen1_cities.hpp` — 10 địa điểm Kanto với dialog NPC:

```bash
  Pallet Town, Viridian City, Pewter City, Cerulean City,
  Vermilion City, Lavender Town, Celadon City,
  Fuchsia City, Saffron City, Indigo Plateau
```

- [ ] Mỗi City có: `name`, `tag` (GYM 1 / NO GYM...), `npcDialog[]`, `hasGym`, `gymLeaderName`

### World

- [ ] `app/world/City.hpp` / `City.cpp` — struct City đầy đủ
- [ ] `app/world/Region.hpp` / `Region.cpp` — `LinkedList<City>`, load gen1_cities
- [ ] `app/world/WorldMap.hpp` / `WorldMap.cpp` — quản lý Region, cursor vị trí hiện tại

### UI

- [ ] `app/ui/OverworldUI.hpp` / `OverworldUI.cpp` — render màn overworld
- [ ] Hiển thị: tên thành phố, tag, dialog NPC, các lựa chọn

### Logic

- [ ] Di chuyển: `[1] Go forward` hoặc `[2] Stay / Check area`
- [ ] Wild encounter: random 30% khi di chuyển (dùng `rand() % 10 < 3`)
- [ ] Nếu gặp wild → trigger battle stub (chưa implement, chỉ print "A wild X appeared! [TODO]")
- [ ] Nếu có Gym → hiện `[3] Challenge Gym` (stub chưa implement)
- [ ] Nếu là Indigo Plateau và badges < 8 → "You need 8 badges!"

## Expected output

```bash
╔══════════════════════════════════════╗
║  GYM 2          CERULEAN CITY        ║
║  Trainer: RED        Badges: 1/8     ║
╠══════════════════════════════════════╣
║  NPC: "Misty is a brilliant Water-   ║
║  type trainer. Her Starmie moves     ║
║  at incredible speed. Watch out."    ║
╠══════════════════════════════════════╣
║  [1] Go forward                      ║
║  [2] Check area                      ║
║  [3] Challenge Gym — MISTY           ║
║  [4] View party                      ║
║  [5] Open bag                        ║
╚══════════════════════════════════════╝
> _
```

## Cách test

1. Chạy game → qua intro → vào Pallet Town
2. `[1]` di chuyển → đến Viridian City, dialog NPC đúng
3. Di chuyển nhiều lần → ít nhất 1 lần gặp wild encounter stub
4. Đến Pewter City → có option `[3] Challenge Gym`
5. Đến Indigo Plateau khi badges = 0 → thông báo cần 8 badges
6. Input sai → không crash

## Ghi chú

- Dùng `LinkedList<City>` cursor để track vị trí hiện tại
- Comment rõ chỗ dùng `LinkedList` để giảng viên thấy
- Wild encounter và Gym battle là stub — Phase 03 mới implement thật
