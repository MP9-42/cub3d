*This project has been created as part of the 42 curriculum by mikjimen, alegeber*

# cub3D

A first-person raycasting engine written in C with [MLX42](https://github.com/codam-coding-college/MLX42), in the spirit of Wolfenstein 3D.

The program reads a `.cub` scene file describing the textures, the floor/ceiling colors and the map grid, then renders the map from the player's point of view: one ray per screen column, DDA traversal of the grid, textured wall columns, and a solid floor/ceiling. Sprites are drawn as billboards against a per-column depth buffer so they are correctly occluded by walls.

## Build

Dependencies:

- `cc`, `make`
- `cmake` (MLX42 is built with it)
- `glfw` (plus the usual OpenGL dev packages on Linux)

MLX42 is **not** vendored in this repository. On the first build the Makefile clones it from `https://github.com/codam-coding-college/MLX42.git` into `./MLX42` and builds it with cmake, so the first build needs an internet connection.

```sh
make        # builds MLX42 (first time), libft, and the cub3d binary
```

Other rules:

| Rule | Effect |
| --- | --- |
| `make` / `make all` | Build `./cub3d` |
| `make clean` | Remove object files |
| `make fclean` | `clean` + remove the `cub3d` binary and the whole `MLX42` directory |
| `make re` | `fclean` + `all` |

Note that `make fclean` deletes `./MLX42`, so the next `make` will clone and rebuild it again.

There is no separate `make bonus` rule — the bonus features are compiled into the single `cub3d` binary.

Linux and macOS are both supported; the Makefile picks the right link flags from `uname -s` and errors out on any other OS.

## Usage

```sh
./cub3d maps/valid_maps/map1.cub
```

Other scenes are available in `maps/valid_maps/` (`map1.cub`, `map2.cub`, `map3.cub`) and `maps/bonus_maps/` (`bonus.cub`, `cube.cub`, `garden.cub`, `hbf.cub`, `school.cub`). `maps/invalid_maps/` holds deliberately broken scenes (`imap1.cub` … `imap6.cub`) used to test the parser.

The program takes exactly one argument and it must end in `.cub`. Texture paths inside the scene file, as well as the built-in sprite/finish textures, are resolved relative to the current working directory, so run the binary from the project root.

### Controls

| Key | Action |
| --- | --- |
| `W` / `S` | Move forward / backward |
| `A` / `D` | Strafe left / right |
| `←` / `→` | Rotate the camera left / right |
| `Esc` | Close the window and quit |

The window's red cross also closes the game. The window can be resized, but the frame itself is always rendered at the fixed internal resolution of 800×600 (`WIDTH` / `HEIGHT` in `includes/cub3d.h`).

## Scene file format (`.cub`)

A scene file contains six required elements followed by the map.

| Identifier | Meaning | Value |
| --- | --- | --- |
| `NO` | North wall texture | path to a `.png` |
| `SO` | South wall texture | path to a `.png` |
| `WE` | West wall texture | path to a `.png` |
| `EA` | East wall texture | path to a `.png` |
| `F` | Floor color | `R,G,B` with each component in `0-255` |
| `C` | Ceiling color | `R,G,B` with each component in `0-255` |

Rules:

- The six elements may appear in **any order**, and may be separated by empty lines. Each one must appear exactly once.
- The **map must be the last thing in the file**; nothing that looks like a map line is allowed after it.
- The map must be **closed / surrounded by walls** (`1`). This is checked with a flood fill starting from the spawn.
- There must be **exactly one spawn**: a single `N`, `S`, `E` or `W`, which also sets the initial facing direction.
- Rows may have different lengths; they are padded internally. Tabs are expanded to four spaces while the file is read.

### Map characters

| Char | Meaning |
| --- | --- |
| `0` | Walkable floor |
| `1` | Wall |
| `N` `S` `E` `W` | Player spawn + initial facing direction (exactly one per map) |
| space / tab | Void outside the map |
| `6` | Police NPC spawn (bonus) |
| `7` | Collectible can (bonus) |
| `9` | Finish tile (bonus) — solid, only opens once every can is collected |
| `8` | Accepted by the parser, currently unused |

Any other character makes the map invalid.

### Example

Based on `maps/valid_maps/map1.cub`:

```
NO textures/maps/map1/NO.png     # north wall texture
SO textures/maps/map1/SO.png     # south wall texture
WE textures/maps/map1/WE.png     # west wall texture
EA textures/maps/map1/EA.png     # east wall texture

F 220,100,0                      # floor color   R,G,B
C 225,30,0                       # ceiling color R,G,B

111111
100001
1000N1                           # N = spawn, facing north
100001
100001
100001111111111111111111111111111111111111111111
100000000000000000000000000000000000000000000001
111111111111111111111111111111111111111111111111
```

(The `#` comments above are only for illustration — do not put them in a real scene file.)

## Bonus

The bonus features are always active; they simply do nothing if the map does not contain the corresponding tiles.

**Minimap** (`srcs/window/minimap.c`, `srcs/window/minimap_grid.c`)
A top-right minimap showing a fixed radius of tiles around the player. The player is a red dot with a green line indicating the facing direction, the NPC is a blue dot, walls and floor are shaded differently, and the finish tile is drawn green once unlocked and dark green while still locked.

**Chasing NPC with BFS pathfinding** (`srcs/bonus/police*.c`)
A tile marked `6` spawns a "police" NPC. It runs a breadth-first search over the map grid to find a path to the player, recomputes that path a few times per second, and walks it while respecting wall collisions. It is rendered in the world as a billboard sprite (`textures/sprites/POLICE.png`). If it gets close enough to the player, the game is lost and the screen turns red.

**Collectible cans + HUD** (`srcs/bonus/items.c`, `srcs/bonus/items_hud.c`)
Tiles marked `7` are cans, drawn as billboard sprites and picked up by walking over them. A HUD row in the top-left corner shows one slot per can on the map: a grey dot for a can still out there, a can icon for one already collected.

**Finish tile** (`srcs/bonus/finish.c`)
A tile marked `9` is a solid wall drawn with a dedicated finish texture. While cans are still missing it is rendered dimmed and touching it does nothing. Once every can on the map has been collected the finish lights up and walking into it wins the game, turning the screen green.

`maps/bonus_maps/bonus.cub` is a small scene containing all of these.

The tunables for these features (NPC speed, catch distance, path recompute interval, minimap size and colors, HUD icon size, finish touch distance) all live as `#define`s at the top of `includes/cub3d.h`.

## How it works

**1. Parsing** (`srcs/parsing/`, `srcs/map/`)
The whole scene file is read with `get_next_line` into an array of lines. The six elements are looked up by identifier anywhere before the map, the four texture paths are loaded as PNGs through MLX42, and `F` / `C` are parsed into packed `0xRRGGBBAA` values. Everything from the first map line onward is copied into the map grid, with tabs expanded and rows padded to the widest row.

**2. Validation** (`srcs/parsing/map_parse.c`, `srcs/map/map_assign.c`)
The grid is checked for allowed characters and exactly one spawn, then a recursive flood fill runs on a copy of the grid starting from the spawn. Reaching a space, a tab or the edge of the grid means the map leaks, and the program exits with `Error`.

**3. Setup** (`srcs/player/player_init.c`, `srcs/window/init.c`)
The spawn cell becomes the player position; its letter sets the direction vector and the perpendicular camera plane (a 66° field of view). The window and the frame image are created, and four loop hooks are registered: `update_player`, `update_npc`, `update_items` and `render_frame`.

**4. Ray casting** (`srcs/raycaster/dda.c`)
For each of the 800 screen columns, a ray direction is built from `dir + plane * camera_x`, where `camera_x` runs from -1 to 1 across the screen. A DDA loop then steps the ray from gridline to gridline until it lands on a solid cell. Anything outside the grid counts as solid, so a ray can never escape even if validation is bypassed. The distance is taken perpendicular to the view direction, which removes the fisheye distortion.

**5. Drawing the frame** (`srcs/raycaster/render_wall.c`, `render_sprite.c`, `render.c`)
Wall slice height is `HEIGHT / perp_wall_dist`. The texture is chosen from which side of the cell was hit and the step direction (or the finish texture for a `9`), the hit's fractional position gives the texture column, and the column is sampled top to bottom; ceiling and floor colors fill the rest. Each column's distance is stored in a per-frame depth buffer, and the sprites (NPC, cans) are drawn afterwards: transformed into camera space with the inverse camera matrix, sized inversely to their depth, and blitted stripe by stripe only where the stripe is closer than the wall behind it. Transparent texels are skipped. The minimap and the can HUD are drawn last, on top of everything.

**6. Movement** (`srcs/player/player_move.c`)
Movement and rotation are polled per frame with `mlx_is_key_down`. Collision is resolved one axis at a time, so sliding along a wall works instead of getting stuck. The finish tile counts as a wall here too — you can walk up to it but never onto it.

## Memory management

All allocations go through a small garbage collector in `garbage/`. The binary is linked with `-Wl,--wrap=malloc,--wrap=free,--wrap=exit`, so every `malloc` is recorded in a linked list, every `free` removes its node, and `exit` frees whatever is left before terminating. A failed `malloc` prints an error and exits through the same path. The upshot is that no cleanup code is needed on the error paths, and the program exits leak-free from anywhere.

## Error handling

Errors print to standard error, always starting with a line containing `Error`, and exit with status 1:

| Message | Cause |
| --- | --- |
| `Error\nUsage: ./cub3D <scene.cub>` | Wrong number of arguments, or the file does not end in `.cub` |
| `Error\nInvalid map` | A missing/duplicate element, a bad map, or an unopenable file |
| `Error\nInvalid color (need R,G,B in 0-255)` | Malformed `F` or `C` line |
| `Error\nFailed to load textures` | A texture path in the scene file (or a built-in sprite) could not be loaded as a PNG |

## Project structure

```
srcs/parsing/    scene-file elements: textures, F/C colors, character checks
srcs/map/        reading the file, extracting the map grid, flood-fill validation
srcs/raycaster/  DDA ray casting, wall columns, billboard sprites, frame loop
srcs/player/     spawn/direction setup and per-frame movement and rotation
srcs/window/     MLX window and image setup, minimap rendering
srcs/bonus/      NPC + BFS pathfinding, cans, HUD, finish tile
srcs/utils/      small shared helpers
srcs/errors/     error messages and exit
includes/        cub3d.h (prototypes, constants) and structs.h
libftV2/         libft
gnl/             get_next_line, used to read the scene file
garbage/         garbage collector wrapping malloc/free/exit
textures/        wall textures per map, sprites, finish texture
maps/            valid, bonus and invalid example scenes
```

## Resources

alegeber:

- [Lode Vandevenne's raycasting tutorial](https://lodev.org/cgtutor/raycasting.html) — the reference for this whole engine. Part 1 is the untextured DDA loop and the fisheye correction, [part 2](https://lodev.org/cgtutor/raycasting2.html) adds textured walls, [part 3](https://lodev.org/cgtutor/raycasting3.html) covers the sprite billboards and the depth buffer used in `render_sprite.c`.
- [Permadi's ray-casting tutorial](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/) — the same ideas derived with more geometry and diagrams; useful when the vector form in Lode's code stops being obvious.
- Fabien Sanglard, *Game Engine Black Book: Wolfenstein 3D* — how id actually shipped this in 1992, on hardware without a floating-point unit.


Built on [MLX42](https://github.com/codam-coding-college/MLX42) by Codam Coding College. The raycasting approach follows the classic [Lode Vandevenne raycasting tutorial](https://lodev.org/cgtutor/raycasting.html).
