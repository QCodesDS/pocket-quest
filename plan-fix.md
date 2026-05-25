# Kế hoạch sửa đổi cốt truyện & Khắc phục lỗi tiến trình (plan-fix.md)

Tài liệu này ghi lại danh sách các nhiệm vụ cần thực hiện để đồng bộ mã nguồn với **Kịch bản Kanto Gen 1** và sửa đổi các lỗi logic/chiến đấu/bản đồ cốt lõi.

## Tiến độ sửa đổi

- `[ ]` **Phần 1: Cấu trúc thực thể & Dữ liệu cốt truyện (Player & Cities)**
  - `[ ]` Thêm các cờ nhiệm vụ cốt truyện vào `Player.hpp` và `Player.cpp`.
  - `[ ]` Mở rộng danh sách `GEN1_CITIES` trong `gen1_cities.hpp` từ 10 lên 11 địa điểm (thêm Cinnabar Island).
  - `[ ]` Sửa đổi đội hình của Koga, Sabrina và Giovanni trong `gen1_trainers.hpp` đúng hệ Độc, Siêu linh và Đất.

- `[ ]` **Phần 2: Trận đấu Rival mở màn ở Pallet Town**
  - `[ ]` Cập nhật `Game.cpp` để kích hoạt Rival Stage 0 ngay sau khi người chơi chọn Starter.
  - `[ ]` Tự động phân phối Starter đối nghịch cho Rival.

- `[ ]` **Phần 3: Logic Overworld & Rào cản nhiệm vụ tuyến tính**
  - `[ ]` **Nhiệm vụ 1 (Oak's Parcel):** Khóa đường Pewter City tại Viridian Mart cho đến khi mang Oak's Parcel về Pallet Town giao cho Oak.
  - `[ ]` **Nhiệm vụ 2 (S.S. Anne & Cut):** Tích hợp sự kiện S.S. Anne tại cảng Vermilion, đánh Rival lấy HM01 Cut. Khóa Gym Lt. Surge nếu chưa có Cut.
  - `[ ]` **Nhiệm vụ 3 (Lavender Tower & Silph Scope):** Khóa Lavender Tower cho đến khi đánh bại sào huyệt Rocket tại Celadon City nhận Silph Scope. Giải cứu Fuji nhận Poké Flute.
  - `[ ]` **Nhiệm vụ 4 (Snorlax & Safari Zone):** Dùng Poké Flute gọi Snorlax để mở Cycling Road đi Fuchsia City. Vào Safari Zone tìm Gold Teeth đổi lấy HM04 Strength và nhặt HM03 Surf.
  - `[ ]` **Nhiệm vụ 5 (Cinnabar Mansion Key):** Yêu cầu tìm Secret Key tại Pokemon Mansion để mở Gym Blaine tại Cinnabar Island.
  - `[ ]` **Nhiệm vụ 6 (Giovanni Gym 8):** Khi đạt 7 badges, tự động mở khóa và kích hoạt Gym Leader Giovanni tại Viridian City Gym.

- `[ ]` **Phần 4: Tích hợp hiệu ứng chỉ số của Badges**
  - `[ ]` Cập nhật `BattleSystem.cpp` tự động nhân $12.5\%$ ($9/8$) chỉ số tương ứng khi Pokémon vào trận nếu Player sở hữu các badges tương ứng:
    - **Boulder Badge:** $+12.5\%$ Attack
    - **Thunder Badge:** $+12.5\%$ Defense
    - **Soul Badge:** $+12.5\%$ Speed
    - **Volcano Badge:** $+12.5\%$ Special (S.Atk / S.Def)

---

## Danh sách tệp tin sẽ chỉnh sửa
1. `app/entities/Player.hpp` (Thêm các cờ quest)
2. `app/entities/Player.cpp` (Khởi tạo cờ quest)
3. `app/data/gen1_cities.hpp` (Mở rộng bản đồ, thêm Cinnabar)
4. `app/data/gen1_trainers.hpp` (Sửa party Gyms & Rival)
5. `app/core/Game.cpp` (Trận Rival 0 đầu game)
6. `app/ui/OverworldUI.cpp` (Logic các quest, mở khóa Gym Giovanni, Cinnabar Island)
7. `app/systems/BattleSystem.cpp` (Hiệu ứng cộng chỉ số Badge)

---

*Ghi chú: Kế hoạch này tập trung hoàn toàn vào LOGIC, WORLD, BATTLE trước để game chạy mượt, đúng cốt truyện và phá đảo được, giao diện (UI) phức tạp sẽ được cải tiến ở bước tiếp theo.*
