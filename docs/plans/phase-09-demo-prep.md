# Phase 09 — Demo Prep

## Precondition

Gen 1 hoàn chỉnh, không bug, không crash.

## Mục tiêu

Chuẩn bị bản nộp hoàn chỉnh: README, Makefile kiểm tra lại,
zip đúng tên, quay video demo theo yêu cầu đề bài.

## Checklist

### README.md

- [ ] Hướng dẫn build: `make` và `make run`
- [ ] Yêu cầu: Windows + MinGW g++ (C++17)
- [ ] Bảng 7 thư viện DSA → dùng ở đâu trong game
- [ ] Cấu trúc thư mục ngắn gọn
- [ ] Tên thành viên + MSSV

### Makefile kiểm tra

- [ ] `make` compile sạch không warning
- [ ] `make run` chạy đúng
- [ ] `make clean` xóa binary

### Video demo (~5–10 phút)

Script demo:

```
[0:00–0:30] Giới thiệu project, tên thành viên
[0:30–1:30] Chạy make, compile thành công
[1:30–2:00] Title screen → nhập tên → chọn Charmander
[2:00–3:30] Di chuyển qua 3 thành phố, đọc NPC dialog
[3:30–5:00] Wild encounter → battle → dùng Potion từ bag
[5:00–6:30] Gym 1 Brock → thắng → nhận badge
[6:30–7:30] Pokédex → xem Charmander → sort by name
[7:30–8:30] Trainer AI demo: Brock's Onix luôn dùng Rock Throw trước
[8:30–9:30] Rival xuất hiện → battle bắt buộc
[9:30–10:00] Kết: show master-plan, giải thích 7/7 lib coverage
```

### Nộp bài

- [ ] Đặt tên folder: `24120421_XXXXXXXX`
- [ ] Bên trong: `lib/`, `app/`, `docs/`, `Makefile`, `README.md`, `demo.txt`
- [ ] `demo.txt` — điền link video Google Drive (public)
- [ ] Zip thành `24120421_XXXXXXXX.zip`
- [ ] Kiểm tra zip: giải nén → `make run` chạy được ngay

### Checklist cuối

- [ ] Không còn file `.o`, binary trong zip
- [ ] Không còn `save.txt` cũ trong zip
- [ ] `lib/` là bản final của Thành viên A (hoặc stub đã dùng)
- [ ] Tất cả comment tiếng Việt hoặc tiếng Anh, nhất quán
- [ ] Không có hardcoded path tuyệt đối

## Cách test trước khi nộp

1. Giải nén zip ra folder mới (không phải folder dev)
2. Chạy `make` → compile sạch
3. Chạy `make run` → game chạy đúng
4. Chơi 5 phút không crash
5. Kiểm tra link video demo còn truy cập được

## Ghi chú

- Quay video trên Windows (môi trường giảng viên chấm)
- Nói to rõ tên từng thư viện DSA khi demo để giảng viên nghe thấy
- Nếu lib/ của Thành viên A chưa xong → dùng stub lib đã có, ghi chú rõ trong README
