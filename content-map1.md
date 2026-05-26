### Bản đồ mô phỏng vùng Kanto (ASCII Map)

```bash
      [Indigo Plateau]
              |
       (Victory Road)
              |
        [Pewter City] ------- (Mt. Moon) ------- [Cerulean City] ---- (Rock Tunnel)
              |                                         |                   |
      (Viridian Forest)                                 |                   |
              |                                         |                   |
       [Viridian City]       [Celadon City] ---- [Saffron City] ---- [Lavender Town]
              |                     |                   |                   |
          (Route 1)                 |                   |                   |
              |               (Cycling Road)     [Vermilion City]       (Route 12)
        [Pallet Town]               |                   |                   |
              |                     +------------ [Fuchsia City] ------------+
          (Route 21)                                    |
              |                                         |
      [Cinnabar Island] ---- (Seafoam Islands) ---------+
```

_(Chú thích: Các ô vuông `[...]` đại diện cho các thành phố/thị trấn; các ngoặc tròn `(...)` đại diện cho tuyến đường hoang dã hoặc hầm ngục kết nối)._

---

### Chi tiết Lộ trình Tuyến tính từ Đầu đến Cuối Game

Dưới đây là bảng tiến trình phân chia theo cốt truyện tuyến tính, giúp bạn dễ dàng thiết kế logic lập trình chuyển cảnh (map transition) và điều kiện mở khóa nhiệm vụ (flag/trigger):

| Bước | Điểm bắt đầu    | Điểm đến        | Sự kiện chính & Chướng ngại vật                                                                                                                           | Nhận được / Key Item                                              |
| ---- | --------------- | --------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------- | ----------------------------------------------------------------- |
| 1    | Pallet Town     | Viridian City   | Nhận Pokémon khởi đầu từ Giáo sư Oak. Băng qua Route 1 hoang dã.                                                                                          | 1 Starter Pokémon, Kiện hàng Oak's Parcel                         |
| 2    | Viridian City   | Pallet Town     | Mang kiện hàng về giao cho Giáo sư Oak để kích hoạt nhiệm vụ chính của cốt truyện.                                                                        | Bản đồ Pokédex, Bản đồ Town Map                                   |
| 3    | Pallet Town     | Pewter City     | Vượt qua mê cung Rừng Viridian Forest. Thách thức Gym Đá của Brock.                                                                                       | Boulder Badge, TM34 (Bide)                                        |
| 4    | Pewter City     | Cerulean City   | Đột kích Mt. Moon, đụng độ Team Rocket và chọn hóa thạch. Thách thức Gym Nước của Misty.                                                                  | Hóa thạch cổ đại, Cascade Badge, TM11                             |
| 5    | Cerulean City   | Vermilion City  | Vượt qua cầu Nugget , cứu nhà phát minh Bill để lấy vé tàu. Băng qua hầm ngầm Route 5 & 6 xuống phía Nam.                                                 | Vé tàu S.S. Ticket , Thỏi vàng Nugget                             |
| 6    | Vermilion City  | Vermilion Gym   | Lên du thuyền S.S. Anne, đánh bại đối thủ và lấy kỹ năng chặt cây. Thách thức Gym Điện của Lt. Surge.                                                     | HM01 (Cut) , Thunder Badge, TM24                                  |
| 7    | Vermilion City  | Lavender Town   | Đi xuyên hầm Diglett để lấy kỹ năng Flash. Băng qua hang tối Rock Tunnel để đến thị trấn nghĩa trang.                                                     | HM05 (Flash), Cây sáo Poké Flute (nhận sau bước 8)                |
| 8    | Lavender Town   | Celadon City    | Tạm thời bỏ qua tháp ma. Đi qua Route 8 & 7 tới Celadon, đánh bại Gym Cỏ của Erika và sào huyệt ngầm Rocket.                                              | Kính Silph Scope , Rainbow Badge, TM21                            |
| 9    | Celadon City    | Fuchsia City    | Quay lại Lavender dùng Silph Scope giải cứu Tháp ma lấy sáo. Thổi sáo dọn dẹp Snorlax chặn đường. Vượt qua Cycling Road để đến Fuchsia đánh bại Gym Koga. | Soul Badge, TM06 , HM03 (Surf), HM04 (Strength)                   |
| 10   | Fuchsia City    | Saffron City    | Mua nước ngọt hối lộ lính gác để vào Saffron. Đột kích Silph Co. đánh đuổi Giovanni. Thách thức Gym Siêu linh của Sabrina.                                | Master Ball , Marsh Badge, TM46 , Hitmonlee/Hitmonchan ở võ đường |
| 11   | Saffron City    | Cinnabar Island | Dùng Surf bơi qua Route 19, 20 và Seafoam Islands. Đột nhập biệt thự hoang tìm chìa khóa mở Gym Lửa của Blaine.                                           | Chìa khóa Secret Key , Volcano Badge, TM38                        |
| 12   | Cinnabar Island | Viridian City   | Surf ngược về Pallet Town (Route 21) để lên Viridian. Lúc này Gym 8 mới mở cửa, đánh bại thủ lĩnh ẩn mặt Giovanni.                                        | Earth Badge, TM27                                                 |
| 13   | Viridian City   | Indigo Plateau  | Đi qua cổng kiểm tra 8 Huy hiệu, vượt qua Victory Road để thách thức Tứ đại Thiên vương và Rival ở trận chung kết.                                        | Danh hiệu Nhà vô địch (Champion)                                  |
| 14   | Indigo Plateau  | Cerulean Cave   | _(Hậu game)_ Lối vào hang Cerulean phía bắc Cerulean City mở ra cho bạn thám hiểm.                                                                        | Cơ hội chạm trán và thu phục Pokémon huyền thoại Mewtwo           |

---

### Gợi ý thiết kế cơ chế chặn Map (Blocking Mechanics) cho game của bạn

Để đảm bảo người chơi đi đúng lộ trình tuyến tính trên mà không bị đi lạc sang các khu vực cấp độ cao quá sớm, game Pokémon nguyên bản sử dụng các "chướng ngại vật" tương ứng với các cột mốc sức mạnh:

1. **Cây nhỏ cản đường (Cut):** Ngăn không cho người chơi tự do đi sang Route 9 (đến Rock Tunnel) hoặc vào thẳng Gym của Lt. Surge. Buộc người chơi phải hoàn thành nhiệm vụ trên tàu S.S. Anne để có HM01 trước.

2. **Bóng tối vô hình (Flash):** Hang Rock Tunnel hoàn toàn tối đen nếu người chơi không có HM05 (yêu cầu bắt đủ 10 loài Pokémon trong Pokédex để trợ lý của Oak trao tặng).

3. **Hồn ma bất tử (Ghost):** Trong tháp Pokémon Tower tại Lavender, người chơi không thể chiến đấu hay đi lên tầng cao nếu không có kính Silph Scope để lột mặt nạ các bóng ma.

4. **Snorlax ngủ chặn đường:** Hai con Snorlax chặn đứng hai ngả đường đi xuống phía nam (Route 12 và Route 16). Người chơi bắt buộc phải giải thoát ông Fuji tại Lavender để nhận Poké Flute mới đánh thức được chúng.

5. **Lính gác khát nước:** Lính gác chặn mọi ngả đường dẫn vào thành phố trung tâm Saffron. Người chơi buộc phải ghé qua siêu thị Celadon, mua nước ngọt đưa cho họ thì mới được cho qua.

6. **Cửa Gym khóa bảo mật:** Viridian Gym (Gym 8) khóa chặt cửa suốt cả game và chỉ mở khi bạn đã sở hữu đủ 7 huy hiệu khác. Cinnabar Gym (Gym 7) cũng bị khóa cho đến khi người chơi giải được câu đố tìm chìa khóa trong ngôi biệt thự đổ nát bên cạnh.

Cơ cấu bản đồ và hệ thống khóa này sẽ giúp bạn dễ dàng triển khai thiết kế màn chơi (Level Design) mạch lạc, tạo cảm giác thế giới mở nhưng thực chất vẫn định hướng người chơi đi đúng quỹ đạo kịch bản mà bạn mong muốn!
