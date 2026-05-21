# Phase 07 — Pokédex

## Precondition

Trainer AI hoàn chỉnh. Monster data đã có từ Phase 03.

## Mục tiêu

Xây dựng Pokédex dùng `BST<MonsterEntry>` — index theo ID,
xem thông tin chi tiết, sort theo ID hoặc tên.

## Thư viện

`BST<MonsterEntry>` từ `lib/BST.hpp`

## Checklist

### Struct

- [ ] `MonsterEntry` trong `app/entities/Monster.hpp`:

  ```cpp
  struct MonsterEntry {
      int         id;
      std::string name;
      std::string type;
      int         hp, atk, def, spd;
      std::string moves[4];
      int         moveCount;

      bool operator<(const MonsterEntry& o) const { return id < o.id; }
      bool operator==(const MonsterEntry& o) const { return id == o.id; }
  };
  ```

### Systems

- [ ] `app/systems/PokedexSystem.hpp` / `PokedexSystem.cpp`:
  - `BST<MonsterEntry> _dex`
  - `load()` — insert tất cả 18 mon Gen 1 khi khởi động
  - `search(int id)` — tìm theo ID
  - `searchByName(string name)` — linear scan inorder
  - `listAll()` — inorder traversal, in từng entry
  - `listSortedByName()` — copy sang array, dùng `mergeSort` với name comparator

### UI

- [ ] Thêm `[P] Pokédex` vào overworld menu
- [ ] Màn Pokédex:
  ```
  [1] View by ID
  [2] List all (sorted by ID)
  [3] List all (sorted by name)
  [0] Back
  ```
- [ ] Xem chi tiết 1 mon: hiện đầy đủ stat + moves

## Expected output — Chi tiết mon

```
╔══════════════════════════════════════╗
║  POKÉDEX  #004                       ║
╠══════════════════════════════════════╣
║  CHARMANDER          Type: Fire      ║
║                                      ║
║  HP  [##########]  39                ║
║  ATK [##########]  52                ║
║  DEF [########..]  43                ║
║  SPD [############] 65               ║
║                                      ║
║  Moves:                              ║
║    Scratch   PWR 35                  ║
║    Ember     PWR 40                  ║
║    Growl     PWR  0                  ║
╚══════════════════════════════════════╝
```

## Cách test

1. Overworld → `[P]` → Pokédex menu hiện
2. `[1]` tìm ID 4 → Charmander hiện đúng stat
3. `[1]` tìm ID 999 → "Not found in Pokédex"
4. `[2]` list all → in theo thứ tự ID tăng dần (inorder BST)
5. `[3]` list sorted by name → thứ tự alphabet
6. BST search đúng với mọi ID trong data

## Ghi chú

- Comment rõ: "// BST<MonsterEntry>: Pokédex indexed by monster ID"
- Đây là thư viện thứ 7/7 — sau phase này đạt full coverage
- `listSortedByName()` kết hợp BST inorder + Algorithms sort — showcase 2 lib cùng lúc
