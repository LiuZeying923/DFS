# DFS
GridPath-Optimizer: DFS-based solver for energy-constrained terrain traversal. Given a height grid, find minimum energy path from left to right—climb costs, jump down is free. Extensible with custom constraints, obstacles, and visualization. Built from a parkour competition problem.
# 🏃 GridPath-Optimizer

[![C++](https://img.shields.io/badge/C++-11-blue.svg)](https://isocpp.org/)
[![CMake](https://img.shields.io/badge/CMake-3.10+-green.svg)](https://cmake.org/)

> A DFS-based solver for energy-constrained grid traversal. Find the minimum energy path from left to right across a terrain grid.

## 📋 Problem Statement

You are in a parkour competition. Given a grid of obstacle heights, find if you can traverse from the **left side** to the **right side**. Movement is allowed **up, down, left, right** only.

**Constraints:**
- 🧗 Climb up to **1.5 meters** (costs energy = height difference)
- 🪂 Jump down up to **2.5 meters** (free, no energy cost)
- Heights are integers (multiplied by 10 internally for precision)

**Goal:** Minimize total energy consumed while crossing from any cell in column 0 to any cell in column `cols-1`.

## 🎯 Features

- ✅ **DFS with Pruning** - Efficiently explores paths while discarding suboptimal branches
- ✅ **Memory Caching** - Stores minimum energy per cell to avoid redundant calculations
- ✅ **Customizable Constraints** - Easily modify max climb/jump heights
- ✅ **Verbose Mode** - View statistics: states explored, pruning hits, efficiency
- ✅ **Extensible Architecture** - Ready for new algorithms (BFS, Dijkstra, A*)
- ✅ **Test Suite Included** - Sample test cases with runner script

## 🔧Installation

### Prerequisites
- C++11 compatible compiler (g++ 4.9+, clang 3.4+, MSVC 2015+)
- CMake 3.10+ (optional)

### Build with CMake

```bash
git clone https://github.com/yourusername/GridPath-Optimizer.git
cd GridPath-Optimizer
mkdir build && cd build
cmake ..
make
./bin/gridpath
