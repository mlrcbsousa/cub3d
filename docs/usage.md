# cub3D — Usage Guide

## Building

```bash
make          # build ./cub3D
make clean    # remove object files
make fclean   # remove objects + binary
make re       # fclean then rebuild
make bonus    # alias for all (no separate bonus files)
```

**Linux only** — install X11 dependencies first:

```bash
sudo apt-get install libx11-dev libxext-dev libbsd-dev
```

---

## Running

```bash
./cub3D <map.cub>
```

The only argument is a path to a valid `.cub` map file. The window opens at **1200 × 800** pixels.

---

## Controls

| Key | Action |
|-----|--------|
| `W` | Move forward |
| `S` | Move backward |
| `A` | Strafe left |
| `D` | Strafe right |
| `←` (left arrow) | Rotate camera left |
| `→` (right arrow) | Rotate camera right |
| `ESC` | Quit |
| Window close button | Quit |

---

## Map File Format (`.cub`)

A `.cub` file has two ordered sections:

1. **Element lines** — must appear before the map
2. **Map lines** — the 2D grid

### Element Lines

```
NO <path>     # north wall texture (XPM image)
SO <path>     # south wall texture (XPM image)
WE <path>     # west wall texture (XPM image)
EA <path>     # east wall texture (XPM image)
F R,G,B       # floor color
C R,G,B       # ceiling color
```

All six elements are **required**. Order within the element section does not matter.
Paths must be valid relative to the working directory.

### Map Lines

```
1111111
1000001
100N001
1000001
1111111
```

| Character | Meaning |
|-----------|---------|
| `1` | Wall |
| `0` | Open floor |
| `N` | Player start, facing **North** |
| `S` | Player start, facing **South** |
| `E` | Player start, facing **East** |
| `W` | Player start, facing **West** |
| ` ` (space) | Outside the map (treated as void — must be bordered by walls) |

**Map rules:**
- Must be fully enclosed by `1` walls (no open edges)
- Exactly **one** player start character (`N`, `S`, `E`, or `W`)
- May contain spaces/tabs for irregular shapes, but all reachable floor cells must be enclosed

---

## Example Map

```
NO ./assets/walls/wall_north.xpm
SO ./assets/walls/wall_south.xpm
WE ./assets/walls/wall_west.xpm
EA ./assets/walls/wall_east.xpm

F 202,164,114
C 135,206,235

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111110111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000000001
10000000000000001100000010001
10000000000000000001010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

Run it with:

```bash
./cub3D assets/maps/example.cub
```

---

## Error Handling

cub3D prints a descriptive error and exits with status `1` on:

| Condition | Message |
|-----------|---------|
| Wrong number of arguments | Usage hint |
| File not found or unreadable | `Error\n<description>` |
| Missing element (NO/SO/WE/EA/F/C) | `Error\n<description>` |
| Invalid color value | `Error\n<description>` |
| Map not enclosed by walls | `Error\n<description>` |
| Multiple or no player start | `Error\n<description>` |

---

## Norminette / Style

Run norminette across all C and header files:

```bash
make style
```

Check for leftover TODO comments:

```bash
make check
```
