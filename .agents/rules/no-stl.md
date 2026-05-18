---
trigger: always_on
---

# Rule: No STL Containers

Activation: Always On

NEVER use the following as replacements for lib/ implementations:

- `std::vector`, `std::list`, `std::forward_list`
- `std::stack`, `std::queue`, `std::deque`
- `std::priority_queue`
- `std::map`, `std::unordered_map`, `std::set`

## Allowed STL usage

- `std::string` — for text only
- `std::cin`, `std::cout`, `std::cerr` — I/O only
- `std::iomanip` — formatting only

## Use instead

| Need            | Use                                |
| --------------- | ---------------------------------- |
| Dynamic list    | `LinkedList<T>` from lib/          |
| Stack           | `Stack<T>` from lib/               |
| Queue           | `Queue<T>` from lib/               |
| Priority queue  | `PriorityQueue<T>` from lib/       |
| Key-value store | `HashTable<K,V>` from lib/         |
| Sorted index    | `BST<T>` or `AVL<T>` from lib/     |
| Sorting         | `mergeSort`, `quickSort` from lib/ |
