#include "MapRenderer.hpp"

namespace MapRenderer {
    std::vector<std::string> getMapLines(const std::string& currentCity) {
        std::vector<std::string> mapLines = {
            "      [Indigo Plateau]                                                           ",
            "              |                                                                  ",
            "       (Victory Road)                                                            ",
            "              |                                                                  ",
            "        [Pewter City] ------- (Mt. Moon) ------- [Cerulean City] ---- (Rock Tun.)",
            "              |                                         |                   |    ",
            "      (Viridian Forest)                                 |                   |    ",
            "              |                                         |                   |    ",
            "       [Viridian City]       [Celadon City] ---- [Saffron City] ---- [Lavender]  ",
            "              |                     |                   |                   |    ",
            "          (Route 1)                 |                   |                   |    ",
            "              |               (Cycling Road)     [Vermilion City]       (Route 12)",
            "        [Pallet Town]               |                   |                   |    ",
            "              |                     +------------ [Fuchsia City] -----------+    ",
            "          (Route 21)                                    |                        ",
            "              |                                         |                        ",
            "      [Cinnabar Island] ---- (Seafoam Islands) ---------+                        "
        };

        // ANSI Color Codes
        std::string COLOR_GREEN = "\033[1;32m";
        std::string COLOR_RESET = "\033[0m";

        for (size_t i = 0; i < mapLines.size(); ++i) {
            std::string searchTarget = currentCity;
            // Xử lý một số tên bị viết tắt trên map
            if (currentCity == "Lavender Town") searchTarget = "Lavender";

            size_t pos = mapLines[i].find(searchTarget);

            if (pos != std::string::npos) {
                // Thay thế [City Name] bằng > City Name < và tô màu xanh
                size_t startBracket = mapLines[i].rfind('[', pos);
                size_t endBracket = mapLines[i].find(']', pos);
                
                if (startBracket != std::string::npos && endBracket != std::string::npos && startBracket < pos) {
                    std::string coloredTarget = COLOR_GREEN + "> " + searchTarget + " <" + COLOR_RESET;
                    // Xóa phần cũ (ví dụ: "[Pallet Town]") và thay bằng mới
                    mapLines[i].replace(startBracket, endBracket - startBracket + 1, coloredTarget);
                } else {
                    std::string coloredTarget = COLOR_GREEN + searchTarget + COLOR_RESET;
                    mapLines[i].replace(pos, searchTarget.length(), coloredTarget);
                }
            }
        }

        return mapLines;
    }
}
