# cub3D — Architecture

## Overview

cub3D is a single-binary C application. The entry point is `src/main.c`, which orchestrates five
sequential phases: **parse → init → window → render → event loop**.

```
main()
 ├── parse()          — read and validate .cub file
 ├── settings_init()  — compute derived settings (FOV, ray angles)
 ├── player_init()    — set starting position and direction
 ├── mlx_init()       — open MiniLibX connection
 ├── mlx_new_window() — create the OS window (1200×800)
 ├── set_image()      — allocate off-screen frame buffer
 ├── walls_create()   — load XPM wall textures into memory
 ├── mlx_hook()       — register keyboard + close-button handlers
 ├── draw()           — render first frame
 └── mlx_loop()       — hand control to MiniLibX event loop
```

---

## Module Breakdown

### `src/parse*.c` — Map and Element Parsing

| File | Responsibility |
|------|---------------|
| `parse.c` | Entry point; opens file, drives parsing pipeline |
| `parse_1.c` | Parses element lines (NO/SO/EA/WE/F/C) |
| `parse_2.c` | Parses map lines after elements |

The parser fills a `t_app` struct with texture paths, colors, and the 2D map grid. Validation
is strict: any missing element, invalid color, or non-enclosed map produces a fatal error.

### `src/map*.c` and `src/maplines*.c` — Map Grid

| File | Responsibility |
|------|---------------|
| `map.c` / `map_1.c` | Store and access the 2D character grid |
| `maplines.c` / `maplines_1.c` | Read raw lines from file; handle tabs/spaces |

The map is stored as a `char **` grid. Map cells use the encoding:
`'1'` = wall, `'0'` = floor, `'N'/'S'/'E'/'W'` = player start.

### `src/elements*.c` — Scene Elements

| File | Responsibility |
|------|---------------|
| `elements.c` / `elements_1.c` | Parse and store the six scene descriptors (4 textures + 2 colors) |

Textures are stored as file paths; colors are stored as packed 32-bit integers `0xRRGGBB`.

### `src/settings.c` — Engine Settings

Computes constants derived from the window size and FOV:
- Column-to-angle mapping for the 1200-column viewport
- Half-width/half-height constants for projection

### `src/player.c` — Player State

Initializes player position (center of start cell), facing angle from the map direction
character (`N/S/E/W`), and movement step size.

### `src/raycast*.c` — Raycasting Engine

| File | Responsibility |
|------|---------------|
| `raycast.c` | Outer loop: casts one ray per screen column |
| `raycast_1.c` | DDA step: advances ray through grid cells until wall hit |

For each screen column the engine:
1. Computes the ray angle (player angle ± FOV offset)
2. Steps through the grid using DDA until hitting a `'1'` cell
3. Calculates the perpendicular wall distance (fisheye-corrected)
4. Determines wall height, texture column, and tile direction (NSEW)

### `src/draw*.c` — Rendering

| File | Responsibility |
|------|---------------|
| `draw.c` | Drives per-column rendering: ceiling strip, wall strip, floor strip |
| `draw_1.c` | Samples texture pixels and writes to the frame buffer |

Rendering writes into an off-screen `t_image` buffer, then calls `mlx_put_image_to_window`
once per frame for tear-free display.

### `src/image.c` — Frame Buffer

Wraps MiniLibX image allocation (`mlx_new_image`) and pixel-write helpers.
The image is 1200×800 pixels, 32 bits per pixel.

### `src/hooks.c` — Event Handling

Handles two MiniLibX hooks:
- `ON_KEYDOWN` → `key_hook()`: dispatches movement and rotation, triggers `draw()`
- `ON_DESTROY` → `close_app()`: frees resources and exits cleanly

### `src/move.c` — Movement Logic

Translates key events into player position/angle deltas, applying collision detection
against wall cells before updating the player struct.

### `src/vector.c` and `src/point.c` — Math Utilities

Lightweight 2D vector (`t_vector`) and point (`t_point`) structs with arithmetic helpers
used throughout raycasting and movement calculations.

### `src/validation.c` — Input Validation

Validates command-line arguments (exactly one `.cub` file) and checks the map at load time
(enclosed by walls, exactly one player start).

### `src/helpers.c` and `src/test.c`

- `helpers.c`: small utilities (error exit, usage message)
- `test.c`: debug helpers used during development (not compiled in release)

---

## Data Flow

```
.cub file
    │
    ▼
parse() ──────────────────────────────────────────────────────────────────────┐
    │   elements: texture paths, F/C colors                                    │
    │   map: char** grid + dimensions                                          │
    ▼                                                                          │
settings_init() + player_init()                                                │
    │   ray angles, step sizes, start pos/dir                                  │
    ▼                                                                          │
walls_create() ── loads XPM textures into t_image[4]                          │
    │                                                                          │
    ▼                                                                          │
draw() ◄──── key_hook() (on move/rotate)                                      │
    │                                                                          │
    │   for each column 0..1199:                                               │
    │     raycast() → wall dist, hit side, texture column                      │
    │     draw_column(): ceiling | wall strip (textured) | floor               │
    │     write pixels to t_image buffer                                       │
    │                                                                          │
    ▼                                                                          │
mlx_put_image_to_window() ── flush buffer to screen                           │
```

---

## Key Types (`include/cub3d.h`)

| Type | Purpose |
|------|---------|
| `t_app` | Top-level application state (all modules hang off this) |
| `t_parser` | Temporary state used during `.cub` file parsing |
| `t_settings` | Pre-computed engine constants (FOV, step sizes) |
| `t_player` | Position, angle, movement state |
| `t_ray` | Per-column ray state during raycasting |
| `t_element` | One scene descriptor (texture path or RGB color) |
| `t_image` | MiniLibX image + raw pixel buffer pointer |
| `t_point` | 2D integer coordinate |
| `t_vector` | 2D float vector |

Window size: **1200 × 800** px. Map cell size: **64** px.
