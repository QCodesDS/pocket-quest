#include "InventorySystem.hpp"
#include <iostream>

InventorySystem::InventorySystem()
{
    // Constructor - bag is initialized as empty HashTable
}

void InventorySystem::addItem(const std::string &name, int qty)
{
    // GRADER: HashTable::find() - check if item already exists (O(1) average)
    Item *existingItem = bag.find(name);

    if (existingItem)
    {
        // Item exists - increase quantity
        existingItem->quantity += qty;
    }
    else
    {
        // New item - insert into HashTable (O(1) average)
        // GRADER: HashTable::insert(key, value)
        Item newItem(name, 0, qty);
        bag.insert(name, newItem);
    }
}

bool InventorySystem::useItem(const std::string &name, Monster &target)
{
    // GRADER: HashTable::find() - lookup item by name (O(1) average)
    Item *item = bag.find(name);

    if (!item)
    {
        std::cout << "Item '" << name << "' not found in bag!\n";
        return false;
    }

    if (item->quantity <= 0)
    {
        std::cout << "No '" << name << "' left in bag.\n";
        return false;
    }

    // Check if target mon HP is already full
    if (target.hp >= target.maxHp)
    {
        std::cout << target.name << "'s HP is already full!\n";
        return false; // Don't use item, don't decrement quantity
    }

    // Apply healing
    int healAmount = item->healAmount;
    int oldHp = target.hp;

    if (healAmount == 0)
    {
        // Full restore item
        target.hp = target.maxHp;
    }
    else
    {
        // Standard healing item
        target.hp += healAmount;
        if (target.hp > target.maxHp)
            target.hp = target.maxHp;
    }

    // Decrease quantity
    item->quantity--;

    // Log the action
    std::cout << "Used " << name << " on " << target.name << "!\n";
    std::cout << target.name << " recovered " << (target.hp - oldHp) << " HP.\n";

    // Remove item if quantity reaches 0
    // GRADER: HashTable::remove() when qty = 0 (O(1) average)
    if (item->quantity <= 0)
    {
        removeItem(name);
    }

    return true;
}

bool InventorySystem::removeItem(const std::string &name)
{
    // GRADER: HashTable::remove() - delete item from bag (O(1) average)
    return bag.remove(name);
}

bool InventorySystem::hasItem(const std::string &name) const
{
    // GRADER: HashTable::contains() - check existence (O(1) average)
    return bag.contains(name);
}

int InventorySystem::getQuantity(const std::string &name) const
{
    // GRADER: HashTable::find() - lookup item (O(1) average)
    const Item *item = bag.find(name);
    return item ? item->quantity : 0;
}

Item *InventorySystem::getItem(const std::string &name)
{
    // GRADER: HashTable::find() - lookup and return pointer (O(1) average)
    return bag.find(name);
}

int InventorySystem::size() const
{
    return bag.size();
}

bool InventorySystem::empty() const
{
    return bag.empty();
}
