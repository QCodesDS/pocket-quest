---
trigger: glob
globs: app/**
---

# Rule: Input Validation & Safety

Activation: Glob — app/\*_/_.cpp

## cin input

Always validate before using:

```cpp
// WRONG
int choice;
cin >> choice;

// CORRECT
int choice = 0;
if (!(cin >> choice)) {
    cin.clear();
    cin.ignore(1000, '\n');
    // re-prompt or use default
}
```

## Data structure safety

Always check before access:

```cpp
// WRONG
Monster m = party.dequeue();

// CORRECT
if (!party.empty()) {
    Monster m = party.dequeue();
}
```

Same applies to: `stack.pop()`, `stack.top()`, `pq.extract()`, `pq.peek()`

## Menu input

```cpp
// Pattern for all menus
int getMenuChoice(int min, int max) {
    int choice;
    while (true) {
        if (cin >> choice && choice >= min && choice <= max)
            return choice;
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. Enter " << min << "-" << max << ": ";
    }
}
```

## Never

- `exit()` on bad input — always re-prompt instead
- Assume cin always succeeds
- Access index without bounds check
