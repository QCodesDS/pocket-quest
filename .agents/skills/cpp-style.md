# Skill: C++ Coding Style

Activation: Model Decision

## Naming

| Element        | Convention  | Example                         |
| -------------- | ----------- | ------------------------------- |
| Class / Struct | PascalCase  | `BattleSystem`, `GameState`     |
| Function       | camelCase   | `startBattle()`, `getInput()`   |
| Variable       | camelCase   | `playerHp`, `currentCity`       |
| Constant       | UPPER_SNAKE | `MAX_PARTY_SIZE`, `BASE_DAMAGE` |
| File           | PascalCase  | `BattleSystem.cpp`              |

## Constants over magic numbers

```cpp
// WRONG
if (party.size() >= 6) { ... }
if (hp <= 0) { ... }

// CORRECT
const int MAX_PARTY_SIZE = 6;
const int MIN_HP         = 0;
if (party.size() >= MAX_PARTY_SIZE) { ... }
if (hp <= MIN_HP) { ... }
```

## Function structure

```cpp
// Short comment explaining purpose + lib usage
// Uses Queue<Monster> to get front fighter
Monster& BattleSystem::getActiveMon() {
    return party.front();
}
```

## Header guard

```cpp
// Use #pragma once — not #ifndef guards
#pragma once
```

## No `using namespace std` in headers

```cpp
// WRONG in .hpp
using namespace std;

// CORRECT — always qualify
std::string name;
std::cout << message;
```

## Struct vs Class

Use `struct` for data containers, `class` for logic-heavy objects:

```cpp
struct Monster { ... };      // data
class BattleSystem { ... };  // logic
```
