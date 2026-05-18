# Skill: Terminal UI Rendering

Activation: Model Decision

## Box drawing characters

```
Single line:  ─ │ ┌ ┐ └ ┘ ├ ┤ ┬ ┴ ┼
Double line:  ═ ║ ╔ ╗ ╚ ╝ ╠ ╣ ╦ ╩ ╬
```

## HP bar pattern

```cpp
std::string hpBar(int cur, int max, int width = 10) {
    int filled = (cur * width) / max;
    filled = filled < 0 ? 0 : filled;
    return std::string(filled, '#') +
           std::string(width - filled, '.');
}
// Output: [######....] 60/100
```

## Standard screen layout

```
╔══════════════════════════════════╗
║  LOCATION NAME          [TAG]    ║
╠══════════════════════════════════╣
║  ENEMY NAME   Lv.X               ║
║  HP [##########]  80/80          ║
╠══════════════════════════════════╣
║  YOUR MON     Lv.X               ║
║  HP [######....]  60/80          ║
╠══════════════════════════════════╣
║  > Battle log line 1             ║
║    Battle log line 2             ║
╠══════════════════════════════════╣
║  [1] Fight    [2] Bag            ║
║  [3] Switch   [4] Run            ║
╚══════════════════════════════════╝
```

## Menu pattern

```cpp
void showMenu(const std::string& title,
              const std::string options[],
              int count) {
    std::cout << "\n  " << title << "\n";
    for (int i = 0; i < count; i++)
        std::cout << "  [" << (i+1) << "] " << options[i] << "\n";
    std::cout << "\n  > ";
}
```

## Clear + redraw

Always clear before redrawing a screen:

```cpp
clearScreen();
renderBattleScreen(...);
```

Never append screens — always full redraw.
