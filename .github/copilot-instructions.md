# MonsterQuest — Copilot Instructions

## Dự án
Console Pokémon-inspired RPG viết bằng C++17.  
Đồ án môn CSC10004 — DSA, HCMUS. Thành viên B phụ trách toàn bộ phần app/.

## Techstack
- Ngôn ngữ: C++17
- Compiler: g++ với `-std=c++17 -Wall -Wextra`
- Thư viện tự cài: `lib/` — TUYỆT ĐỐI không sửa
- UI: Terminal/console thuần — không GUI
- Cross-platform: Linux (Codespaces) + Windows (MinGW)
- Build: Makefile

## Cấu trúc app/
```
app/
├── main.cpp
├── core/        Game, GameState, SaveData
├── entities/    Monster, Move, Trainer, Player
├── world/       City, Region, WorldMap
├── systems/     BattleSystem, InventorySystem, PokedexSystem, WildSystem
├── data/        gen1/2/3 monsters, trainers, items (hardcoded)
└── ui/          UI, BattleUI, OverworldUI, MenuUI
```

## Ánh xạ thư viện DSA → game
- `LinkedList<City>`      → chuỗi thành phố trong mỗi Region
- `Queue<Monster>`        → party battle, lần lượt đưa mon ra đánh
- `Stack<BattleLog>`      → log 5 dòng gần nhất trong battle
- `HashTable<string,Item>`→ inventory tra cứu item theo tên
- `Algorithms`            → sort party theo HP/SPD, sort Pokédex
- `PriorityQueue<Move>`   → trainer AI chọn move damage cao nhất
- `BST<int,Monster>`      → Pokédex index theo ID

## Coding style
- Tên biến/hàm có nghĩa, không magic numbers — dùng const hoặc enum
- Mỗi hàm một trách nhiệm duy nhất
- Comment ngắn trên mỗi hàm, đặc biệt chỗ dùng lib
- Không `using namespace std` trong .hpp
- Tách .hpp (khai báo) và .cpp (định nghĩa)
- Cross-platform: dùng `#ifdef _WIN32` để xử lý cls/clear

## Giới hạn cứng
- KHÔNG sửa bất kỳ file nào trong lib/
- KHÔNG dùng std::vector, std::map, std::queue, std::stack thay lib tự cài
- KHÔNG implement GUI
- KHÔNG để crash khi nhập sai input — luôn validate cin

## Sau mỗi task
Báo cáo: files thêm/sửa/xóa, cách test, nhắc update CHANGELOG.md
