# BRD — Tài liệu Yêu cầu Dự án

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
| Dev env    | Antigravity (Windows)   |
| Chấm bài   | Windows (MinGW g++)     |

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
| `BST<MonsterEntry>`      | Pokédex                    | Index theo số ID, tìm kiếm O(log n)  |

> `BST<T>` trong lib chỉ nhận 1 type. Dùng struct `MonsterEntry` có field `id` làm key so sánh.

---

## 3. Phạm vi triển khai

**Ưu tiên:** Hoàn thiện **Gen 1 — Kanto** trước. Gen 2 và Gen 3 là mở rộng tùy chọn nếu còn thời gian sau khi Gen 1 ổn định.

| Gen           | Trạng thái        | Ghi chú                                |
| ------------- | ----------------- | -------------------------------------- |
| Gen 1 (Kanto) | 🎯 Mục tiêu chính | Bắt buộc hoàn thành                    |
| Gen 2 (Johto) | 🔒 Tùy chọn       | Mở sau khi Gen 1 xong và còn thời gian |
| Gen 3 (Hoenn) | 🔒 Tùy chọn       | Mở sau khi Gen 2 xong                  |

---

## 4. Functional Requirements

### 4.1 World System

- [ ] Gen 1 — Kanto: `LinkedList<City>` gồm 10 địa điểm theo đúng cốt truyện
- [ ] Di chuyển: chọn số thứ tự địa điểm kế tiếp
- [ ] Mỗi địa điểm có trạng thái: chưa đến / đang ở / đã qua
- [ ] Gen 2, 3 bị lock — chỉ mở sau khi thắng Champion gen trước

### 4.2 Starter Selection

- [ ] Gen 1: chọn 1 trong 3 — Bulbasaur / Charmander / Squirtle
- [ ] Gen 2 (nếu làm): Chikorita / Cyndaquil / Totodile
- [ ] Gen 3 (nếu làm): Treecko / Torchic / Mudkip

### 4.3 Overworld & NPC

- [ ] Mỗi thành phố có 1–2 dòng dialog NPC hint cốt truyện
- [ ] Wild encounter ngẫu nhiên 30% khi di chuyển giữa thành phố
- [ ] Rival xuất hiện 4 lần trong Gen 1 — bắt buộc đánh, có dialog trước trận

### 4.4 Battle System

- [ ] Turn-based: Player → Trainer/Wild lần lượt
- [ ] Player chọn: `[1] Fight  [2] Bag  [3] Switch  [4] Run`
- [ ] `Queue<Monster>` — mon đầu hàng ra đánh, faint → dequeue → con tiếp theo
- [ ] `PriorityQueue<Move>` — trainer AI chọn move damage cao nhất
- [ ] `Stack<BattleLog>` — lưu log, hiển thị 5 dòng gần nhất
- [ ] Damage formula: `dmg = (move.power * atk) / def`
- [ ] Run: chỉ được với wild encounter, không được với trainer/gym

### 4.5 Gym & Elite Four

- [ ] 8 Gym Leader theo đúng thứ tự Kanto
- [ ] Đánh thắng Gym → nhận Badge, lưu vào SaveData
- [ ] Cần đủ 8 Badge mới vào Indigo Plateau
- [ ] Elite Four: 4 trainer liên tiếp — Lorelei, Bruno, Agatha, Lance
- [ ] Champion: Blue (Rival) — trận cuối Gen 1

### 4.6 Inventory System

- [ ] `HashTable<string, Item>` lưu bag của player
- [ ] Item: Potion (+20HP), Super Potion (+50HP), Full Restore (full HP)
- [ ] Dùng item trong battle (`[2] Bag`) hoặc ngoài battle (menu)
- [ ] Giới hạn 10 loại item trong bag

### 4.7 Pokédex

- [ ] `BST<MonsterEntry>` — `MonsterEntry` có field `id` làm key so sánh
- [ ] Xem thông tin mon: ID, tên, type, HP/ATK/DEF/SPD, danh sách moves
- [ ] Sort theo ID (mặc định) hoặc tên (dùng `Algorithms`)

### 4.8 Save & Progress

- [ ] Lưu: gen đang chơi, badges đã có, party hiện tại, tên player
- [ ] Ghi vào file `save.txt` — đọc lại khi khởi động nếu tồn tại

---

## 5. Non-functional Requirements

- Compile sạch: `g++ -std=c++17 -Wall -Wextra` không warning, không error
- Không crash với mọi input — validate toàn bộ `cin`
- Chạy được trên Windows (MinGW g++)
- `make run` là lệnh duy nhất cần để build và chạy
- Demo được trong 5–10 phút

---

## 6. Data scope — Gen 1 (bắt buộc)

| Loại         | Số lượng             | Ghi chú                             |
| ------------ | -------------------- | ----------------------------------- |
| Starter      | 3                    | Bulbasaur, Charmander, Squirtle     |
| Wild mon     | 6                    | Đại diện các type khác nhau         |
| Gym leader   | 8 × (2–3 mon)        | Theo đúng thứ tự Kanto              |
| Rival        | 4 lần xuất hiện      | Pallet, Cerulean, Silph, Plateau    |
| Elite Four   | 4 trainer + Champion | Lorelei, Bruno, Agatha, Lance, Blue |
| Item         | 3 loại               | Potion, Super Potion, Full Restore  |
| Move mỗi mon | 2–4 moves            | Đủ để PriorityQueue có ý nghĩa      |

---

## 7. DO / DON'T

### ✅ DO

- Dùng thư viện tự cài cho mọi cấu trúc dữ liệu chính
- Comment rõ chỗ dùng lib để giảng viên nhận ra ngay
- Xử lý input sai nhẹ nhàng — in thông báo, re-prompt
- Có màn hình welcome, game over, victory rõ ràng
- Hoàn thiện Gen 1 trước khi nghĩ đến Gen 2

### ❌ DON'T

- Dùng `std::vector`, `std::map`, `std::queue`, `std::stack`, `std::priority_queue`
- Implement catch mechanic (ngoài scope)
- Để game crash với bất kỳ input nào
- Bắt đầu Gen 2 khi Gen 1 chưa chạy ổn định
