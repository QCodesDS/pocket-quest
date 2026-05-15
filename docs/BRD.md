# BRD — Business Requirements Document

## MonsterQuest v1.0

---

## 1. Thông tin dự án

| Thuộc tính | Giá trị                 |
| ---------- | ----------------------- |
| Môn học    | CSC10004 — DSA, HCMUS   |
| Vai trò    | Thành viên B — Ứng dụng |
| Ngôn ngữ   | C++17                   |
| Giao diện  | Console / Terminal      |
| Thời gian  | ~4 tuần                 |
| Dev env    | GitHub Codespaces       |
| Chấm bài   | Windows (MinGW)         |

---

## 2. Ánh xạ thư viện DSA → tính năng

| Thư viện                 | Tính năng                  | Lý do chọn                           |
| ------------------------ | -------------------------- | ------------------------------------ |
| `LinkedList<City>`       | Chuỗi thành phố mỗi Region | Di chuyển next/prev tuyến tính       |
| `Queue<Monster>`         | Party battle               | Mon đầu hàng ra đánh trước           |
| `Stack<BattleLog>`       | Log battle                 | LIFO — dòng mới nhất hiển thị cuối   |
| `HashTable<string,Item>` | Inventory                  | Tra cứu O(1) theo tên item           |
| `Algorithms`             | Sort party, Pokédex        | Sort theo HP/SPD/ID                  |
| `PriorityQueue<Move>`    | Trainer AI                 | Move damage cao → ưu tiên dùng trước |
| `BST<int,Monster>`       | Pokédex                    | Index theo số ID, tìm kiếm O(log n)  |

---

## 3. Functional Requirements

### 3.1 World System

- [ ] 3 Region (Kanto/Johto/Hoenn), mỗi Region là `LinkedList<City>` 5–6 thành phố
- [ ] Gen 2, 3 bị lock — chỉ mở sau khi thắng Champion gen trước
- [ ] Di chuyển: nhập tên thành phố hoặc chọn số thứ tự

### 3.2 Starter Selection

- [ ] Mỗi gen chọn 1 trong 3 starter
- [ ] Gen 1: Bulbasaur / Charmander / Squirtle
- [ ] Gen 2: Chikorita / Cyndaquil / Totodile
- [ ] Gen 3: Treecko / Torchic / Mudkip

### 3.3 Overworld & NPC

- [ ] Mỗi thành phố có 1–2 dòng dialog NPC hint cốt truyện
- [ ] Wild encounter ngẫu nhiên 30% xác suất khi di chuyển giữa thành phố
- [ ] Rival xuất hiện 2 lần mỗi gen — bắt buộc đánh, có dialog

### 3.4 Battle System

- [ ] Turn-based: Player → Trainer/Wild (lần lượt)
- [ ] Player chọn: `[1] Fight  [2] Bag  [3] Switch  [4] Run`
- [ ] `Queue<Monster>` — mon đầu hàng ra đánh, faint → pop → con tiếp theo
- [ ] `PriorityQueue<Move>` — trainer AI tự động chọn move damage cao nhất
- [ ] `Stack<BattleLog>` — lưu log, hiển thị 5 dòng gần nhất
- [ ] Damage formula đơn giản: `dmg = move.power * atk / def`
- [ ] Run: chỉ được bỏ chạy khỏi wild encounter, không được bỏ trainer

### 3.5 Gym & Elite Four

- [ ] Mỗi gen có 8 Gym Leader, mỗi người có party 2–3 mon
- [ ] Đánh thắng Gym → nhận Badge, ghi nhận vào SaveData
- [ ] Cần đủ 8 Badge mới vào được Pokemon League
- [ ] Elite Four: 4 trainer liên tiếp không hồi HP giữa trận
- [ ] Champion: trận cuối mỗi gen

### 3.6 Inventory System

- [ ] `HashTable<string, Item>` lưu bag của player
- [ ] Các item: Potion (+20HP), Super Potion (+50HP), Full Restore (full HP)
- [ ] Dùng item trong battle hoặc ngoài battle
- [ ] Drop item khi bag đầy (giới hạn 10 loại)

### 3.7 Pokédex

- [ ] `BST<int, Monster>` index theo Pokédex ID
- [ ] Xem thông tin mon: ID, tên, type, HP/ATK/DEF/SPD, moves
- [ ] Sort danh sách theo ID hoặc tên (dùng Algorithms)

### 3.8 Save & Progress

- [ ] Lưu tiến trình: gen đang chơi, badges đã có, party hiện tại
- [ ] Đơn giản: ghi vào file `.txt` hoặc hardcoded state trong Session

---

## 4. Non-functional Requirements

- Compile sạch: `g++ -std=c++17 -Wall -Wextra` không warning
- Không crash với mọi input hợp lệ — validate toàn bộ `cin`
- Cross-platform: chạy được cả Linux (Codespaces) và Windows (MinGW)
- `make run` là lệnh duy nhất cần để chạy game
- Demo được trong 5–10 phút

---

## 5. Data scope (không cần full Pokédex)

| Gen           | Monster | Gym Leaders         | Wild pool |
| ------------- | ------- | ------------------- | --------- |
| Gen 1 (Kanto) | 18 mon  | 8 leaders × 2–3 mon | 6 mon     |
| Gen 2 (Johto) | 18 mon  | 8 leaders × 2–3 mon | 6 mon     |
| Gen 3 (Hoenn) | 18 mon  | 8 leaders × 2–3 mon | 6 mon     |

---

## 6. DO / DON'T

### ✅ DO

- Dùng thư viện tự cài cho mọi cấu trúc dữ liệu chính
- Comment rõ chỗ dùng lib để giảng viên dễ nhận ra
- Xử lý input sai nhẹ nhàng — in thông báo, không crash
- Có màn hình welcome, game over, victory rõ ràng

### ❌ DON'T

- Dùng `std::vector`, `std::map`, `std::queue`, `std::stack`, `std::priority_queue`
- Sửa bất kỳ file nào trong `lib/`
- Implement catch mechanic (ngoài scope)
- Để game crash với input bất kỳ
