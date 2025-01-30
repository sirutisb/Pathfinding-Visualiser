# Pathfinding Visualiser

A comprehensive and interactive pathfinding algorithm visualiser built using C++, SFML, and Dear ImGui, with CMake for seamless cross-platform compilation. Visualise algorithms like Dijkstra's and A* in real-time, customize grids, and explore graph traversal dynamically.

## Features

### Grid Management
- **Dynamic Grid Creation**: Generate customizable grids with adjustable dimensions (e.g., 10x10 to 100x100).
- **Cell Interaction**: Left-click to toggle walls/obstacles, right-click to set start and end nodes.
- **Weighted Nodes** (Optional): Add weights to nodes for advanced algorithm visualization (if implemented).

### Visualization Tools
- **Pan & Zoom**: 
  - Drag with right click to pan.
  - Use the mouse wheel to zoom in/out.
- **Real-Time Editing**: Modify the grid in real-time using the left mouse button.
- **Path Reconstruction**: Visualise the shortest path with a distinct color and track explored nodes.

### Algorithms
- **Supported Algorithms**:
  - **Dijkstra's Algorithm**: Classic weighted graph traversal.
  - **A* Search**: Heuristic-based optimization with Euclidean or Manhattan distance.
- **Execution Controls**: 
  - Pause/resume visualization.
  - Adjust simulation speed dynamically.

### UI Controls (ImGui Panel)
- **Toggle Menu**: Press insert to toggle menu visibility.
- **Toolbar**: Start/stop/reset simulation, clear paths/walls, and adjust grid size.
- **Algorithm Settings**: Select algorithms
- **Save/Load System**: Save grid layouts to disk and reload them later.

## Installation

### Prerequisites
- **C++ Compiler**: Supports C++20 (e.g., GCC, Clang, MSVC).
- **CMake 3.28+**: Build system.

### Build Instructions

#### Linux/macOS
```bash
Clone the repo
cd pathfinding-visualizer
mkdir build && cd build
cmake ..
cmake --build .
./bin/PathfindingVisualiser
```
