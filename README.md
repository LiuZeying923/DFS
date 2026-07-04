# 🏃 GridPath-Optimizer-3D

[![C++](https://img.shields.io/badge/C++-11-blue.svg)](https://isocpp.org/)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](https://opensource.org/licenses/MIT)

> A 3D DFS-based solver for energy-constrained grid traversal. Navigate through **multiple layers (floors/time/states)** to find the minimum energy path from left to right.

## 📋 Problem Statement

You are in a **3D parkour** competition. Given a 3D grid of obstacle heights (depth × rows × columns), find if you can traverse from the **left side** to the **right side** across any layer. Movement: **up/down/left/right + layer switching**.

| Dimension | Meaning |
|-----------|---------|
| **Depth** | Floor / Time / State layer |
| **Row** | Vertical position |
| **Col** | Horizontal position |

**Constraints:**
- 🧗 Climb up to **1.5m** (same layer) / **3.0m** (cross-layer) → costs energy
- 🪂 Jump down up to **2.5m** (same layer) / **10.0m** (cross-layer) → free
- ⚡ Cross-layer movement = stairs/elevator (more forgiving)

**Goal:** Minimize total energy consumed from any cell in column 0 to any cell in column `cols-1` (any layer).

## 🚀 Features

- ✅ **3D DFS with Pruning** — Depth, row, column triple-layer search
- ✅ **Cross-Layer Support** — Move between floors/time slices with custom constraints
- ✅ **Memory Caching** — Stores minimum energy per 3D cell
- ✅ **Verbose Mode** — Statistics: states explored, pruning efficiency
- ✅ **Single-File Implementation** — One `.cpp`, no external dependencies
- ✅ **Makefile Included** — Build with one command

## 🔧 Installation

### Prerequisites
- C++11 compiler (g++, clang, MSVC)

### Build

```bash
git clone https://github.com/yourusername/GridPath-Optimizer-3D.git
cd GridPath-Optimizer-3D
make
