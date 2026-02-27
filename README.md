# Measure Concentration in 2-Ball and 3-Ball

Visualization of mild measure concentration by randomly sampling points
in a 2-ball and 3-ball and plotting their radial distance from the center.

## Overview

This project provides a geometric demonstration of how probability mass
distributes in finite-dimensional spaces. Points are sampled uniformly
inside a 2-ball (disk) and a 3-ball, and their distances from the origin
are visualized to illustrate the onset of measure concentration.

The program renders the sampling and statistics in real time using SFML.

## Features

- Random sampling in 2-ball and 3-ball
- Radial distance measurement
- Real-time visualization
- Interactive rendering window

## Requirements

- **Compiler:** Visual Studio 2026 (MSVC, x64)
- **Language:** C++17
- **Library:** SFML 2.6+
- **Runtime asset:** `arial.ttf`

## Dependencies

This project depends on:

- SFML (`graphics`, `window`, `system`)
- Arial font file placed in the executable directory

If the font is missing, text rendering will fail.

## Build Instructions (Visual Studio Developer Command Prompt)

```bash
cmake -S . -B build -G "Visual Studio 18 2026" -A x64
cmake --build build --config Release
