---

## Recommended Task Division for Two People: cub3D Project

To maximize efficiency and minimize duplicated work in the cub3D project, divide the main tasks into **Engine Implementation** and **Game Data & Logic Handling**. Here is a recommended two-person split:

---

## 1. Graphics Rendering & Input Handling

For the team member with some experience in graphics/math programming:

- Initialize and manage the miniLibX window (including event response, handling ESC and window close button, etc.)
- Implement the core RayCasting rendering algorithm
- Load, switch, and render different wall textures (according to North/South/East/West)
- Handle view rotation (arrow keys) and player movement (WASD), including coordinate transformations
- Render different floor and ceiling colors
- (Optionally, take on bonus features such as mouse-controlled view, HUD, health bar, weapon display, etc.)

This person ensures the rendering pipeline and user interaction logic are coherent and well-structured.

---

## 2. Map Parsing & Game Logic

For the team member who is meticulous and good with text/data processing:

- Parse the .cub map file, supporting all its elements (map layout, texture paths, colors) in various orders and spacings
- Validate map correctness: surrounded by walls, valid characters, one player start point, etc.
- Present parsed map and configuration in accessible data structures for the renderer
- Initialize player start position and orientation
- Provide error and exception handling (“Error\n” and clear error messaging)
- Manage memory and resource release (eliminate memory leaks and ensure clean exits)

If workload allows, this person can also take on bonus features such as:

- Wall collision detection (preventing “walking through walls”)
- Door open/close logic inside the map
- Sprite/enemy/collectible object management (if implementing animated sprites/objects)

---

## Collaboration Principles and Practice

- Keep one person focused on graphics handling and control, the other on backend data and logic.
- Agree on **clear interfaces**: for example, decide early on the data structures through which the renderer obtains map, textures, and color info.
- Each side develops independently testable modules.
- Collaborate on Makefile and documentation (README, compile instructions, etc.).
- Communicate often regarding function names, struct definitions, and code style to ease future integration.

---

## Example Division Table

| Task | Person A (Rendering/Input) | Person B (Parsing/Logic) |
| --- | --- | --- |
| miniLibX window/events | ✓ |  |
| RayCasting algorithm | ✓ |  |
| Keyboard (WASD/Arrows) | ✓ |  |
| Texture loading/rendering | ✓ |  |
| Floor/Ceiling color render | ✓ |  |
| .cub file parsing |  | ✓ |
| Texture path/color reading |  | ✓ |
| Map format/validity check |  | ✓ |
| Player spawn/init |  | ✓ |
| Map data structures | Cooperate | Cooperate |
| Error/memory management | Cooperate | Cooperate |
| Makefile/docs | Cooperate | Cooperate |
| Bonus: Collision/Doors | Optional | Optional |
| Bonus: Mouse look/animation | Optional | Optional |

---

This approach keeps both members productive, minimizes redundant work, and ensures modules are loosely coupled with well-defined interfaces. Active communication, especially about data structures and logic flow, is critical for final integration!
