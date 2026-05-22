# MonsterQuest

Console RPG game inspired by Pokémon Gen 1–3, written in C++17.
Đồ án môn CSC10004 — Cấu trúc dữ liệu và Giải thuật, HCMUS.

---

## Yêu cầu

|            | Linux / Codespaces | Windows      |
| ---------- | ------------------ | ------------ |
| Compiler   | g++ (Ubuntu)       | MinGW g++    |
| Version    | C++17              | C++17        |
| Build tool | make               | make (MinGW) |

---

## Build & Run

```bash
rm -rf deps obj monsterquest && make
./monsterquest
```

---

## Cấu trúc thư mục

```bash
lib/        Thư viện template tự cài (Thành viên A)
app/        Mã nguồn game (Thành viên B)
  core/     Game loop, state machine, save
  entities/ Monster, Move, Trainer, Player
  world/    City, Region, WorldMap
  systems/  BattleSystem, Inventory, Pokédex, WildEncounter
  data/     Data monster/trainer/item 3 gen (hardcoded)
  ui/       Render terminal, input handling
docs/       Tài liệu dự án
```

---

## Thư viện DSA được sử dụng

| Thư viện                 | Vai trò trong game             |
| ------------------------ | ------------------------------ |
| `LinkedList<City>`       | Chuỗi thành phố trong mỗi vùng |
| `Queue<Monster>`         | Party battle theo lượt         |
| `Stack<BattleLog>`       | Log các dòng battle gần nhất   |
| `HashTable<string,Item>` | Inventory tra cứu theo tên     |
| `Algorithms`             | Sort party, sort Pokédex       |
| `PriorityQueue<Move>`    | Trainer AI chọn move tốt nhất  |
| `BST<int,Monster>`       | Pokédex index theo ID          |

---

## Demo

Xem file `demo.txt` để truy cập link video demo.
