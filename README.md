# Red-Black Tree with SFML Visualizer

A C++ templated Red-Black Tree implementation with an integrated SFML graphical visualization tool.

A red-black tree is a binary search tree that satisûes the following red-black
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
