# cub3D

> A 3D raycasting engine inspired by Wolfenstein 3D, built in C with MiniLibX.

[![42 School](https://img.shields.io/badge/42-cub3D-blue)](https://42.fr)
[![Language](https://img.shields.io/badge/language-C-lightgrey)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Norminette](https://img.shields.io/badge/norminette-passing-brightgreen)](https://github.com/42School/norminette)

---

## About

**cub3D** is a 42 School graphics project that implements a 3D game engine using the
[DDA raycasting algorithm](https://permadi.com/1996/05/ray-casting-tutorial-2/). The player
moves through a 2D grid map rendered in first-person 3D perspective, with textured walls and
configurable floor/ceiling colors.

### Features

- First-person 3D rendering via raycasting (no OpenGL)
- Cardinal-direction wall textures (North, South, East, West) via XPM images
- Configurable floor and ceiling colors (RGB)
- Smooth player movement and rotation (keyboard)
- Graceful window close (ESC key or red cross)
- Map validation with clear error messages
- Cross-platform: Linux and macOS (via MiniLibX)
- Bundled [`libft`](libft/) — custom C standard library

---

## Prerequisites

| Dependency | Notes |
|------------|-------|
| `gcc` | C compiler with `-Wall -Wextra -Werror` |
| `make` | GNU Make |
| `MiniLibX` | Bundled for Linux; install via Homebrew on macOS |
| **Linux only** | `libx11-dev`, `libxext-dev`, `libbsd-dev` |

Install Linux X11 dependencies:

```bash
sudo apt-get install libx11-dev libxext-dev libbsd-dev
```

---

## Build

```bash
# Clone the repository
git clone https://github.com/mlrcbsousa/cub3d.git
cd cub3d

# Build the binary
make

# Clean object files
make clean

# Full clean (objects + binary)
make fclean

# Rebuild from scratch
make re
```

---

## Usage

```bash
./cub3D <path/to/map.cub>
```

**Example:**

```bash
./cub3D assets/maps/example.cub
```

### Controls

| Key | Action |
|-----|--------|
| `W` | Move forward |
| `S` | Move backward |
| `A` | Strafe left |
| `D` | Strafe right |
| `←` | Rotate left |
| `→` | Rotate right |
| `ESC` | Quit |

---

## Map Format (`.cub`)

A `.cub` file describes the scene. It has two sections: **elements** (top) and **map** (bottom).

```
NO ./assets/walls/wall_north.xpm
SO ./assets/walls/wall_south.xpm
WE ./assets/walls/wall_west.xpm
EA ./assets/walls/wall_east.xpm

F 202,164,114
C 135,206,235

1111111111
1000000001
100N000001
1000000001
1111111111
```

| Token | Description |
|-------|-------------|
| `NO` | Path to north wall texture (XPM) |
| `SO` | Path to south wall texture (XPM) |
| `WE` | Path to west wall texture (XPM) |
| `EA` | Path to east wall texture (XPM) |
| `F`  | Floor color as `R,G,B` |
| `C`  | Ceiling color as `R,G,B` |
| `1`  | Wall |
| `0`  | Open floor |
| `N/S/E/W` | Player start position and facing direction |

**Rules:**
- Map must be fully enclosed by walls (`1`)
- Exactly one player start position required
- Element lines must come before the map

---

## Project Structure

```
cub3d/
├── src/             # C source files (raycasting, parsing, rendering)
├── include/         # Header files (cub3d.h, ft_mlx.h, ft_point.h, ft_vector.h)
├── libft/           # Bundled custom C standard library
├── assets/
│   ├── maps/        # Example .cub map files
│   └── walls/       # XPM wall textures (N/S/E/W)
└── docs/            # Architecture and usage documentation
```

See [`docs/architecture.md`](docs/architecture.md) for a detailed module breakdown.

---

## Resources

- [Ray Casting Tutorial (Permadi)](https://permadi.com/1996/05/ray-casting-tutorial-2/)
- [Make Your Own Raycaster — YouTube](https://www.youtube.com/watch?v=gYRrGTC7GtA)
- [MiniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx.html)
- [MLX Example Reference](https://github.com/terry-yes/mlx_example)
- [Reference implementation](https://github.com/gleal42/cub3d)

---

## Development Workflow

1. Branch off `main` using your initials: `git checkout -b ms/$FEATURE/$SUB-FEATURE`
2. Write full, capitalized, present-tense commit messages explaining *why* the change was made
3. Open a PR to merge back into `main`

To keep your branch up to date:

```bash
git checkout main && git pull origin main
git checkout ms/feature/sub-feature
git merge main
```
