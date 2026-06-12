# cub3D

*This project was created as part of the 42 curriculum by __bmoreira__ and __lsarraci__.*

## Description

cub3D is a 3D raycasting project inspired by the classic game Wolfenstein 3D. The goal of this project is to create a realistic 3D representation of a maze from a first-person perspective using the MiniLibX library. This project serves as an introduction to graphical programming and explores the fundamentals of raycasting.

## Project Structure
```
cub3d/
|-- include/
|   |-- cub.h
|   |-- cub_engine.h
|   |-- cub_input.h
|   |-- cub_parser.h
|   |-- cub_render.h
|   |-- cub_structs.h
|   |-- cub_types.h
|   |-- cub_utils.h
|   `-- cub_validation.h
|-- lib/
|   |-- libft/
|   `-- minilibx-linux/
|-- src/
|   |-- assets/
|   |   |-- maps/
|   |   `-- textures/
|   |-- engine/
|   |-- input/
|   |-- parser/
|   |-- render/
|   |-- utils/
|   |-- frees.c
|   |-- hooks.c
|   |-- init.c
|   |-- main.c
|   `-- window.c
|-- Makefile
`-- mlx.supp
```

### Features
- **Raycasting Engine:** Real-time 3D rendering with stable frame updates.
- **Directional Textures:** Independent wall textures for North, South, East, and West faces.
- **Scene Parsing:** Custom `.cub` format with strict validation and explicit error messages.
- **Player Movement:** WASD navigation with smooth camera rotation via arrow keys.
- **Collision Handling:** Wall collision checks using a player hitbox radius.
- **Visual Setup:** Configurable floor and ceiling RGB colors.
- **Minimap Overlay:** Live map view with player position and facing direction.
- **Clean Exit:** Proper window lifecycle handling for ESC and window close.

### Technical Stack
- **Language:** C (C99)
- **Graphics:** MiniLibX (MLX)
- **Utilities:** libft (custom standard library)
- **Build System:** Make

## Instructions

### Compilation
To compile the project, run the following command:
```bash
make
```
This will generate the `cub3D` executable.

### Other Make Targets
- `make clean`: Removes object files and intermediate build artifacts.
- `make fclean`: Removes object files and the `cub3D` executable.
- `make re`: Full rebuild (fclean + all).
- `make valgrind`: Runs the executable with a leak check preset using `mlx.supp`.

### Execution
To run the program, provide a `.cub` configuration file as an argument:
```bash
./cub3D path_to_map.cub
```

### Controls
| Key | Action |
| --- | --- |
| W | Move forward |
| A | Strafe left |
| S | Move backward |
| D | Strafe right |
| <- | Rotate left |
| -> | Rotate right |
| ESC | Exit program |

### Example Map File
```text
NO ./path_to_north_texture
SO ./path_to_south_texture
WE ./path_to_west_texture
EA ./path_to_east_texture
F 220,100,0
C 225,30,0
111111
100101
101001
1100N1
111111
```

### Map File Format
- **Required elements:** `NO`, `SO`, `WE`, `EA`, `F`, `C` (textures + floor/ceiling colors).
- **Texture lines:** `ID path/to/texture` where `ID` is one of `NO`, `SO`, `WE`, `EA`.
- **Color lines:** `F R,G,B` and `C R,G,B` with values in `[0,255]`.
- **Map layout:** Must be the last block in the file and can include spaces; valid tiles are `1`, `0`, `N`, `S`, `E`, `W`.
- **Player spawn:** Exactly one of `N`, `S`, `E`, `W` appears in the map grid.
- **Walls:** The map must be closed by walls or parsing fails.
- **Spacing:** Empty lines are allowed between elements; order of elements is flexible.

## Resources
### Documentation & References
- **[Raycasting Fundamentals](https://lodev.org/cgtutor/raycasting.html):** Camera plane, ray direction, and wall projection math.
- **[DDA Traversal](https://lodev.org/cgtutor/raycasting.html):** Grid stepping, side hits, and perpendicular distance correction.
- **[Texture Mapping](https://lodev.org/cgtutor/raycasting.html):** Choosing texture by wall side and sampling texels per column.
- **[MiniLibX Pipeline](https://harm-smits.github.io/42docs/libs/minilibx/introduction.html):** Window creation, image buffers, and per-frame blitting.
- **[Event Handling](https://harm-smits.github.io/42docs/libs/minilibx/introduction.html):** Keyboard hooks and window close events for clean exits.
- **[Wolfenstein 3D](http://users.atw.hu/wolf3d/):** Original inspiration and historical reference.

### Key Concepts
- **[Collision Checks](https://lodev.org/cgtutor/raycasting.html):** Player hitbox sampling against map grid cells.
- **[Level Design Constraints](http://users.atw.hu/wolf3d/):** Closed maps and spawn orientation rules.

### Use of AI
AI tools were used to assist in code review, documentation generation, and debugging. All generated content was reviewed and validated to ensure accuracy and compliance with project requirements.


## Authors
- **[bmoreira](https://github.com/BabiDrummond)**
- **[lsarraci](https://github.com/HellionZero)**