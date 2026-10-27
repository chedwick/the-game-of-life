# The Game of Life

## Overview

The Game of Life, devised in 1970 by the British mathematician
John Horton Conway, is a zero-player cellular automaton.

Its evolution is entirely determined by its initial state, requiring no further
input or interaction afterwards.

## The Rules of the Game

The universe is a 2D grid of cells, each either alive (1) or dead (0).

Every generation, all cells simultaneously update their state based on the count
of their 8 immediate neighbors (horizontal, vertical, and diagonal).

Rules:

- Birth: a dead cell with exactly 3 live neighbors becomes a live cell.
- Survival: a live cell with 2 or 3 live neighbors stays alive.
- Death by underpopulation: a live cell with fewer than 2 live neighbors dies.
- Death by overpopulation: a live cell with more than 3 live neighbors dies.

### Grid Edges

- Dead edges: out-of-bounds cells are treated as permanently dead.
- Toroidal (wrapping/periodic): the edges wrap around, so the left edge connects
  to the right, and top to bottom.

### Cell Patterns

- Still lifes: Block, Beehive, Loaf
- Oscillators:
  - Blinker (period 2)
  - Pulsar (period 3)
  - Pentadecathlon (period 15)
- Spaceships: Glider (moves diagonally), Lightweight spaceship (LWSS).
- Infinite growth: Gosper Glider Gun.

## Build

```bash
make help
```

### Dependencies

Libraries:

- NCURSES
- SDL2
