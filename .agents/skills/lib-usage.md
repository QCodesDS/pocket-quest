# Skill: lib/ Usage Patterns

Activation: Model Decision

## LinkedList<T> — room/city traversal

```cpp
#include "lib/LinkedList.hpp"

LinkedList<City> region;
region.insertBack(City("Pallet Town"));
region.insertBack(City("Pewter City"));

// Traverse forward
region.resetCursor();
while (region.hasCurrent()) {
    process(region.getCurrent());
    if (!region.moveNext()) break;
}
```

## Queue<T> — battle party

```cpp
#include "lib/Queue.hpp"

Queue<Monster> party;
party.enqueue(Monster("Charmander", 39));

// Safe access pattern
if (!party.empty()) {
    Monster& active = party.front(); // currently fighting
}

// On faint: remove and send next
if (!party.empty()) party.dequeue();
```

## Stack<T> — battle log

```cpp
#include "lib/Stack.hpp"

Stack<std::string> battleLog;
battleLog.push("Charmander used Ember! 12 dmg");

// Display last 5 lines
// Tip: copy to array first, print in reverse
```

## HashTable<K,V> — inventory

```cpp
#include "lib/HashTable.hpp"

HashTable<std::string, int> bag;
bag.insert("Potion", 3);

// Safe lookup
int* count = bag.find("Potion");
if (count) {
    std::cout << "Potions: " << *count << "\n";
}

// Use item
if (bag.contains("Potion")) {
    int* qty = bag.find("Potion");
    if (*qty > 1) bag.insert("Potion", *qty - 1);
    else          bag.remove("Potion");
}
```

## PriorityQueue<T> — trainer AI

```cpp
#include "lib/PriorityQueue.hpp"

// Move with higher power = higher priority
struct Move {
    std::string name;
    int power;
    bool operator<(const Move& o) const { return power < o.power; }
};

PriorityQueue<Move> moveQueue;
moveQueue.insert({"Ember", 40});
moveQueue.insert({"Scratch", 35});

// AI picks best move
Move best = moveQueue.extract(); // Ember (40)
```

## BST<T> — Pokédex

```cpp
#include "lib/BST.hpp"

// Store monster ID as comparable key
struct MonsterEntry {
    int id;
    std::string name;
    bool operator<(const MonsterEntry& o) const { return id < o.id; }
    bool operator==(const MonsterEntry& o) const { return id == o.id; }
};

BST<MonsterEntry> pokedex;
pokedex.insert({4, "Charmander"});

// Print all in order
pokedex.inorder([](const MonsterEntry& e) {
    std::cout << "#" << e.id << " " << e.name << "\n";
});
```

## Algorithms — sorting

```cpp
#include "lib/Algorithms.hpp"

// Sort array of monsters by HP descending
Monster arr[6] = { ... };
mergeSort(arr, 6, [](const Monster& a, const Monster& b) {
    return a.hp > b.hp; // descending
});
```
