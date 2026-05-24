# Phase 08 — Gen 1 Complete

## Precondition

7/7 thư viện hoạt động. Pokédex, Battle AI, Inventory đều ổn.

## Mục tiêu

Hoàn thiện toàn bộ cốt truyện Kanto — không bug, không crash,
chơi được mượt từ Pallet Town đến Champion Blue trong 10 phút.

## Checklist

### Bug fix & polish

- [ ] Kiểm tra toàn bộ flow: Pallet → 8 Gym → Elite Four → Champion
- [ ] Rival xuất hiện đúng 4 lần, đúng địa điểm, đúng dialog
- [ ] Gym badge lưu đúng, Indigo Plateau unlock đúng
- [ ] Elite Four: HP không hồi giữa trận — kiểm tra lại
- [ ] Save state sau mỗi Gym thắng (ghi vào `save.txt`)
- [ ] Load save khi khởi động nếu `save.txt` tồn tại

### Cốt truyện đặc biệt

- [ ] **Lavender Town**: không có Gym — chỉ dialog buồn về Pokémon Tower:

```bash
  "This town is home to Pokémon Tower... where Pokémon rest in peace.
   Strange things happen here at night. Team Rocket did something terrible..."
```

- [ ] **Celadon City**: hint Team Rocket ở Game Corner:

```bash
  "Strange men in black uniforms have been seen in the basement..."
```

- [ ] **Saffron City**: Team Rocket chiếm Silph Co.:

```bash
  "Team Rocket has taken over Silph Co.! They want the Master Ball prototype!"
```

- [ ] **Giovanni Gym 8**: lộ mặt là trùm Team Rocket:

```bash
  "I am Giovanni — Leader of Team Rocket, and the final Gym Leader."
```

- [ ] Sau thắng Giovanni: Team Rocket tan rã dialog

### Edge cases

- [ ] Tất cả mon faint → Game Over → option restart hoặc load save
- [ ] Bag rỗng vào Elite Four → vẫn chơi được (khó hơn)
- [ ] Input bất kỳ không crash game

### Final polish

- [ ] Tất cả dialog NPC 10 thành phố đã điền đầy đủ
- [ ] HP bar hiển thị đúng mọi trường hợp (kể cả HP = 0, HP > max)
- [ ] Không còn "TODO" hay "stub" nào còn sót

## Cách test — Full playthrough

1. Chạy từ đầu, chọn Charmander
2. Qua hết 10 địa điểm, đọc dialog từng nơi
3. Gặp wild encounter ít nhất 3 lần
4. Rival xuất hiện đúng 4 lần
5. Đánh hết 8 Gym — badge tăng đúng
6. Lavender Town, Celadon, Saffron — dialog đặc biệt hiện đúng
7. Giovanni → dialog Team Rocket tan rã
8. Elite Four 4 trận liên tiếp
9. Champion Blue → Victory screen
10. Load save: tắt game → chạy lại → tiếp tục đúng chỗ

## Ghi chú

- Mục tiêu phase này là **stability**, không thêm feature mới
- Sau phase này: demo được cho giảng viên mà không lo crash
- Ghi lại bug đã fix vào CHANGELOG với ngày tháng cụ thể
