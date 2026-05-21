# Phase 06 — Trainer AI

## Precondition

V1 hoàn chỉnh. Battle system chạy tốt, trainer AI đang random move.

## Mục tiêu

Thay random move bằng `PriorityQueue<Move>` — trainer luôn chọn
move có damage cao nhất còn PP.

## Thư viện

`PriorityQueue<Move>` từ `lib/PriorityQueue.hpp`

## Checklist

### Logic

- [ ] `Move` struct thêm `operator<` so sánh theo `power`:
  ```cpp
  bool operator<(const Move& o) const { return power < o.power; }
  ```
- [ ] `BattleSystem::enemyAttack()` — refactor:
  - Trước: `rand() % moveCount`
  - Sau: insert tất cả moves vào `PriorityQueue<Move>`, extract move tốt nhất
- [ ] Chỉ insert moves còn PP > 0
- [ ] Nếu tất cả PP = 0 → dùng move mặc định "Struggle" (power 50, không tốn PP)

### Test AI behavior

- [ ] Trainer luôn dùng move damage cao nhất trước
- [ ] Khi move mạnh nhất hết PP → chuyển sang move tiếp theo
- [ ] Behavior đúng với cả wild encounter và trainer battle

## Expected output — Log thay đổi

```
-- Trước (random):
║  > Wild PIDGEY used Tackle! 8 dmg    ║

-- Sau (PriorityQueue AI):
║  > BROCK's ONIX used Rock Throw!     ║  ← move mạnh nhất
║    58 dmg!                           ║
```

## Cách test

1. Battle với Brock nhiều lần → ONIX luôn dùng Rock Throw trước Tackle
2. Hết PP Rock Throw → chuyển sang Tackle
3. Wild encounter → AI cũng dùng move mạnh nhất
4. Log hiển thị đúng move được chọn

## Ghi chú

- Comment rõ: "// PriorityQueue<Move>: trainer AI selects highest power move"
- Đây là thư viện thứ 6/7 — quan trọng cho điểm bao phủ
- Wild AI cũng nên dùng PriorityQueue để đồng nhất behavior
