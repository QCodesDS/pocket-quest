# Phase 04 — Inventory System

## Precondition

Battle system hoạt động, `[2] Bag` trong battle hiện đang là stub.

## Mục tiêu

Hệ thống bag dùng `HashTable<string, Item>`.
Dùng được item trong battle (`[2] Bag`) và ngoài battle (overworld menu).

## Thư viện

`HashTable<string, Item>` từ `lib/HashTable.hpp`

## Checklist

### Data

- [ ] `app/data/items.hpp` — 3 loại item:

```bash
  Potion       heal +20 HP
  SuperPotion  heal +50 HP
  FullRestore  heal full HP
```

### Entities

- [ ] `app/entities/Item.hpp` / `Item.cpp` — struct: name, healAmount, quantity

### Systems

- [ ] `app/systems/InventorySystem.hpp` / `InventorySystem.cpp`:
  - `HashTable<std::string, Item>` — bag, key = item name
  - `addItem(string name, int qty)` — insert hoặc update quantity
  - `useItem(string name, Monster& target)` — heal target, giảm qty
  - `removeItem(string name)` — xóa khi qty = 0
  - `listItems()` — forEach in danh sách
  - `hasItem(string name)` — contains check

### UI — trong battle

- [ ] `[2] Bag` → hiện danh sách item có trong bag
- [ ] Chọn item → dùng cho mon đang đánh
- [ ] Sau khi dùng → enemy phản công 1 lần (turn tiếp tục)

### UI — ngoài battle

- [ ] Overworld menu thêm `[5] Open bag`
- [ ] Xem danh sách, dùng Potion hồi HP

### Logic

- [ ] Player bắt đầu với: Potion ×3
- [ ] Giới hạn 10 loại item trong bag
- [ ] Dùng item khi HP đã full → thông báo "HP is already full!"

## Expected output — Bag trong battle

```
╔══════════════════════════════════════╗
║  BAG                                 ║
╠══════════════════════════════════════╣
║  [1] Potion        ×3   (+20 HP)     ║
║  [2] Super Potion  ×1   (+50 HP)     ║
║  [3] Full Restore  ×0   (EMPTY)      ║
╠══════════════════════════════════════╣
║  [0] Cancel                          ║
╚══════════════════════════════════════╝
> _
```

## Cách test

1. Vào battle → `[2] Bag` → hiện đúng danh sách
2. Chọn Potion → HP mon tăng đúng 20
3. Qty giảm từ 3 → 2 sau khi dùng
4. Dùng hết Potion → qty = 0, item vẫn hiện nhưng đánh dấu EMPTY
5. Dùng item khi HP full → thông báo, không trừ qty
6. Ngoài battle: `[5] Open bag` → dùng Potion → HP hồi
7. Bag trống → "Your bag is empty."

## Ghi chú

- Comment rõ chỗ dùng `HashTable` — đây là điểm chấm điểm quan trọng
- `HashTable::forEach` dùng để list items khi hiển thị bag
- Không cần sort item ở phase này — Phase 05 mới sort
