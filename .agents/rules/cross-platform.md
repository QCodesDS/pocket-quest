---
trigger: glob
globs: app/**
---

# Rule: Cross-Platform Compatibility

Activation: Glob — app/**/\*.cpp, app/**/\*.hpp

Dev environment: Windows (Antigravity)
Graded on: Windows (MinGW g++)

## Clear screen

```cpp
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
```

## Forbidden

- `#include <windows.h>` — Windows only
- `#include <conio.h>` — Windows only (`_getch`, `kbhit`)
- `\` as path separator — use `/` or avoid hardcoded paths
- ANSI color codes without checking terminal support

## Required

- Compile clean on both `g++` (Linux) and `g++` (MinGW Windows)
- Use `int main()` — not `int main(void)` with Win-specific extensions
- `Makefile` must work with `make` on both platforms
