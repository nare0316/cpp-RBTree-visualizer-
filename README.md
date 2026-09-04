# Red-Black Tree with SFML Visualizer

A C++ templated Red-Black Tree implementation with an integrated SFML graphical visualization tool.

✔️ When inserting sequential elements into a Binary Search Tree (BST), the tree degrades into a standard linked list, and the time complexity of the search algorithm can drop to $O(n)$. On the other hand, the strict balancing of an AVL tree can significantly slow down operations. Red-Black (RB) Trees, however, find the golden mean. By using red and black colors, self-balancing provides a looser balance compared to AVL, but offers higher performance during data insertion and deletion processes.

✔️ For the most part, C++ STL containers such as std::map, std::set, std::multimap, and std::multiset are implemented using Red-Black trees, as are Java's TreeMap and TreeSet. Additionally, the Linux kernel's Completely Fair Scheduler module, which is responsible for distributing CPU time allocated to running programs, uses an RB tree for its operation.

✔️ A red-black tree is a binary search tree that satisûes the following red-black
properties:

    1. Every node is either red or black.
    
    2. The root is black.
    
    3. Every leaf ( NIL) is black.
    
    4. If a node is red, then both its children are black.
    
    5. For each node, all simple paths from the node to descendant leaves contain the
same number of black nodes.


## Features

* **Generic Implementation:** Supports custom and built-in data types (e.g., `int`, `char`, `std::string`).
* **Self-Balancing Operations:** Handles standard insertion, deletion, and rotation fixups using a sentinel NIL node.
* **Invariant Verification:** Includes test utilities verifying Black-Height consistency, color invariants, and BST ordering.
* **Graphical Visualization:** Uses SFML to render tree nodes with accurate parent-child connections and Red/Black coloring.

## Project Structure

```text
RBTree/
├── assets/
│   └── Roboto.ttf         # Font file for rendering SFML node labels
├── build/                 # Created automatically during build (stores .o files)
├── include/
│   ├── rbt.hpp            # RBTree class template declaration
│   ├── rbt.tpp            # Template method definitions
│   └── visual.hpp         # SFML Visualizer implementation
├── src/
│   └── main_test.cpp      # Correctness tests and visualizer launcher
└── Makefile               # Build script

### Dependencies
    C++17 or higher
    SFML (Simple and Fast Multimedia Library) v2.x or v3.x


### Build
make all

### Run
make run

### Clean
make clean
