# so_long

A small 2D game: walk around a map, collect every item, then reach the exit.

> Part of the **42 school curriculum**. Built by **Arda Aycan**.

Rendered with 42's MiniLibX (XPM textures, one 64×64 tile per map cell).

## The game

- The player moves one tile at a time with **W A S D**.
- Every `C` on the map must be collected before the exit opens.
- Reaching the exit closes the game; **ESC** and the window's close button also
  quit.
- The move counter is printed to stdout after every step.
- The player sprite flips depending on the direction of travel.

## Map format

Maps are plain text `.ber` files, one character per cell:

| Character | Meaning |
| --- | --- |
| `1` | wall |
| `0` | floor |
| `P` | player start |
| `C` | collectible |
| `E` | exit |

Two example maps ship in `maps/`.

Before the window opens, the map is checked for:

- a rectangle (every row the same width),
- walls all around the border,
- exactly one `P` and one `E`, and at least one `C`,
- no unknown characters,
- **reachability**: a flood fill from the player must reach every collectible
  and the exit, so an impossible map is rejected instead of being played.

A bad map prints an error and exits without opening a window.

## Build

Requires a C compiler and the X11 headers:

```bash
sudo apt install libx11-dev libxext-dev
make            # builds ./so_long
make clean
make fclean
make re
```

The Makefile builds the bundled `minilibx-linux` first. Two small adjustments
keep it building on current toolchains:

- MiniLibX is compiled with `-std=gnu89`, because its sources rely on
  pre-C99 implicit declarations.
- The two MiniLibX hooks are cast to the unprototyped callback type the library
  declares, with `-Wno-cast-function-type` so `-Werror` stays on for everything
  else.

## Run

```bash
./so_long maps/map.ber
./so_long maps/map_two.ber
```

## Project layout

| File | Contents |
| --- | --- |
| `so_long.c` | entry point, window and image setup |
| `map_utils_*.c` | parsing, validation and the reachability flood fill |
| `game_utils_*.c` | hooks, movement, rendering, win condition |
| `get_next_line*.c` | reads the map file line by line |
| `utils_pt_one.c` | cleanup and helpers |
| `textures/` | player, wall, floor, collectible and exit XPMs |
| `maps/` | example maps |

## Notes

- Mandatory part only: no enemies, timer or bonus levels.
- The map is held in memory as a grid of characters; the player's position and
  the collectible list are tracked separately.

## Author

**Arda Aycan** ([@EpicYamo](https://github.com/EpicYamo)).
