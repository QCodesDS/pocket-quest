#ifndef MAP_RENDERER_HPP
#define MAP_RENDERER_HPP

#include <vector>
#include <string>

namespace MapRenderer {
    /**
     * @brief Trả về một mảng chứa các dòng của màn hình Mini-Map.
     * @param currentCity Tên thành phố hiện tại để tô màu.
     * @return Mảng 2D (vector<string>) gồm 17 dòng.
     */
    std::vector<std::string> getMapLines(const std::string& currentCity);
}

#endif // MAP_RENDERER_HPP
