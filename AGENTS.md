# AGENTS.md — MonsterQuest

> File hiến pháp. Đọc file này trước khi làm bất kỳ việc gì.

---

## Tổng quan

**Tên:** MonsterQuest  
**Loại:** Console RPG — Pokémon-inspired, 3 gen (Kanto / Johto / Hoenn)  
**Môn:** CSC10004 DSA — HCMUS  
**Mục tiêu:** Dùng ≥5/7 thư viện template tự cài có ý nghĩa trong gameplay

Đọc thêm: `docs/brief.md`, `docs/BRD.md`

---

## Môi trường

|               | Chi tiết                                |
| ------------- | --------------------------------------- |
| Dev           | GitHub Codespaces (Ubuntu)              |
| Chấm bài      | Windows (MinGW g++)                     |
| Compiler flag | `-std=c++17 -Wall -Wextra -I./lib`      |
| Clear screen  | `#ifdef _WIN32` → `cls`, else → `clear` |

---

## Ánh xạ thư viện → game

| Thư viện                 | Dùng ở đâu                           |
| ------------------------ | ------------------------------------ |
| `LinkedList<City>`       | Chuỗi thành phố mỗi Region           |
| `Queue<Monster>`         | Party battle — mon đầu tiên ra đánh  |
| `Stack<BattleLog>`       | Log 5 dòng gần nhất trong battle     |
| `HashTable<string,Item>` | Inventory — tra cứu item theo tên    |
| `Algorithms`             | Sort party theo HP/SPD, sort Pokédex |
| `PriorityQueue<Move>`    | Trainer AI — chọn move mạnh nhất     |
| `BST<int,Monster>`       | Pokédex — index theo ID              |

---

## Coding style

- Không magic numbers → dùng `const` hoặc `enum`
- Mỗi hàm một trách nhiệm
- Comment trên mỗi hàm quan trọng, đặc biệt chỗ dùng lib
- Không `using namespace std` trong `.hpp`
- Tách `.hpp` / `.cpp`
- Validate mọi `cin` input — không để crash

---

## Giới hạn cứng

- ❌ KHÔNG sửa `lib/`
- ❌ KHÔNG dùng STL containers thay lib tự cài
- ❌ KHÔNG GUI
- ❌ KHÔNG crash khi nhập sai

---

## Quy trình mỗi phase

1. Đọc file phase trong `docs/plans/`
2. Implement theo checklist
3. Báo cáo files thêm/sửa/xóa
4. Hướng dẫn manual test
5. Nhắc update `CHANGELOG.md` + tick `master-plan.md`

---

## Trạng thái hiện tại

Xem `docs/plans/master-plan.md` — tiến độ phases
Xem `docs/CHANGELOG.md` — những gì đã xong
