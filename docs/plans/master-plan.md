# Master Plan — MonsterQuest

## Trạng thái tổng quan

| Phase | Tên                      | Thư viện                             | Mốc           | Trạng thái |
| ----- | ------------------------ | ------------------------------------ | ------------- | ---------- |
| 01    | Project Setup & Skeleton | —                                    |               | ✅         |
| 02    | World System             | `LinkedList<City>`                   |               | ✅         |
| 03    | Battle System            | `Queue<Monster>`, `Stack<BattleLog>` | **V1 ✅**     | ✅         |
| 04    | Inventory System         | `HashTable<string,Item>`             |               | ✅         |
| 05    | Sort & Polish V1         | `Algorithms`                         | **Nộp được**  | ✅         |
| 06    | Trainer AI               | `PriorityQueue<Move>`                |               | ⬜         |
| 07    | Pokédex                  | `BST<int,Monster>`                   | **V2 ✅ 7/7** | ⬜         |
| 08    | Gen 1 Complete           | Tất cả                               | **V3 ✅**     | ✅         |
| 09    | Demo Prep                | —                                    | **Nộp**       | ⬜         |

---

## Mốc quan trọng

| Mốc                    | Phase xong | Ý nghĩa                        |
| ---------------------- | ---------- | ------------------------------ |
| ✅ V1 — Safe to Submit | 01 → 05    | 5/7 thư viện, đủ điều kiện nộp |
| ⚡ V2 — Full Coverage  | 06 → 07    | 7/7 thư viện                   |
| 🏆 V3 — Full Game      | 08 → 09    | 3 gen hoàn chỉnh, demo đỉnh    |

---

## Chi tiết phases

### Phase 01 — Project Setup & Skeleton

**Mục tiêu:** Cấu trúc thư mục, Makefile chạy được, main.cpp welcome screen  
**Output:** `make run` → hiện màn hình title, nhập tên player  
**Trạng thái:** ⬜

### Phase 02 — World System

**Mục tiêu:** Di chuyển qua các thành phố bằng LinkedList, NPC dialog  
**Thư viện:** `LinkedList<City>`  
**Output:** Chọn thành phố → di chuyển → đọc dialog NPC  
**Trạng thái:** ✅

### Phase 03 — Battle System

**Mục tiêu:** Turn-based battle hoàn chỉnh với Queue party và Stack log  
**Thư viện:** `Queue<Monster>`, `Stack<BattleLog>`  
**Output:** Wild encounter → battle → thắng/thua → return overworld  
**Trạng thái:** ✅

### Phase 04 — Inventory System

**Mục tiêu:** Bag với HashTable, dùng item trong và ngoài battle  
**Thư viện:** `HashTable<string, Item>`  
**Output:** `[2] Bag` trong battle → chọn Potion → HP hồi phục  
**Trạng thái:** ✅

### Phase 05 — Sort & Polish V1

**Mục tiêu:** Sort party/Pokédex, UI đẹp hơn, Gym + Elite Four Gen 1  
**Thư viện:** `Algorithms`  
**Output:** V1 hoàn chỉnh — 1 gen chơi được từ đầu đến Champion  
**Trạng thái:** ✅

### Phase 06 — Trainer AI

**Mục tiêu:** PriorityQueue để trainer tự chọn move tốt nhất  
**Thư viện:** `PriorityQueue<Move>`  
**Output:** Trainer AI không random — ưu tiên move damage cao nhất  
**Trạng thái:** ⬜

### Phase 07 — Pokédex

**Mục tiêu:** BST index monster theo ID, xem thông tin, sort  
**Thư viện:** `BST<int, Monster>`  
**Output:** Menu Pokédex → tìm theo ID → xem stat đầy đủ  
**Trạng thái:** ⬜

### Phase 08 — Gen 1 Complete

**Mục tiêu:** Hoàn thiện toàn bộ cốt truyện Kanto (không bug, không crash), chơi được từ Pallet Town đến Champion Blue trong 10 phút  
**Output:** Phát hành Gen 1 hoàn chỉnh (Stability) và sẵn sàng cho Phase 09 (Demo Prep)  
**Trạng thái:** ✅

### Phase 09 — Demo Prep

**Mục tiêu:** Fix bug, README hoàn chỉnh, quay video demo  
**Output:** Bản nộp hoàn chỉnh — zip, demo.txt có link video  
**Trạng thái:** ⬜
