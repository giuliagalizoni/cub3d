Here is the main content from your “cub3D My first RayCaster with miniLibX” project specification, structured in Markdown and in English:

***

# cub3D  
*My first RayCaster with miniLibX*

**Summary:**  
This project is inspired by the world-famous Wolfenstein 3D game, considered the first FPS ever created. It enables you to explore ray-casting. Your goal is to make a dynamic view inside a maze, finding your way through it.

***

## Table of Contents

- I. Foreword
- II. Goals
- III. Common Instructions
- IV. AI Instructions
- V. Mandatory part - cub3D
- VI. Bonus part
- VII. Examples
- VIII. Submission and Peer-Evaluation

***

## I. Foreword

Developed by Id Software, led by John Carmack and John Romero, and published in 1992 by Apogee Software, Wolfenstein 3D is considered the first true "First Person Shooter" (FPS) in video game history.

> Wolfenstein 3D is the ancestor of games such as Doom (Id Software, 1993), Doom II (Id Software, 1994), Duke Nukem 3D (3D Realm, 1996), and Quake (Id Software, 1996), which are also milestones in video game history.  
> Now, it's your turn to relive History...

> **Note:** Wolfenstein 3D is set in Nazi Germany, which may be disturbing. Its pictures and history are included for technical and cultural reasons, as the game was considered a technical masterpiece.

***

## II. Goals

This project's goals are similar to most first-year objectives: rigor, use of C, mastering basic algorithms, information research, etc.

- Improve skills in graphical programming: windows, colors, events, shapes.
- Use mathematics as a tool for creating elegant and efficient algorithms (no need for deep mathematical background).
- Explore ray-casting with the help of online resources.

You can try the original game at:  
`http://users.atw.hu/wolf3d/`

***

## III. Common Instructions

- The project **must be written in C** and comply with the Norm.
- If there are norm errors (including in bonus files/functions), you will receive a 0.
- Functions must not quit unexpectedly (segmentation fault, bus error, double free, etc.) except for undefined behavior; otherwise, the project will be considered non-functional.
- All heap-allocated memory must be properly freed; memory leaks will not be tolerated.
- A Makefile is required, compiling with `-Wall -Wextra -Werror` and necessary rules: `$(NAME)`, `all`, `clean`, `fclean`, `re`. Avoid unnecessary relinking.
- To submit bonuses, include a bonus rule in your Makefile and place all bonus files as `_bonus.c/h`.
- If allowed, include your libft by copying its source and Makefile into a `libft` folder; compile it via your main Makefile.
- You are encouraged to create test programs, even though they are not graded or submitted.
- Only the work in the assigned Git repository will be graded.

***

## IV. AI Instructions

### Context

During your learning journey, AI can assist with many tasks.  
Explore AI tools, but always approach results critically—AI outputs should be reviewed, questioned, and tested, and peers are invaluable resources for avoiding mistakes.

### Main Message

- Use AI to reduce repetitive/tedious tasks.
- Develop both coding and non-coding prompting skills.
- Learn how AI systems work for awareness of risks and biases.
- Use AI-generated content only if you fully understand and take responsibility for it.

#### Learner Rules

- Know how AI tools work for ethical use and bias reduction.
- Reflect before prompting: write clear and detailed prompts.
- Review, question, and test any AI-generated content.
- Always seek peer review—don't rely solely on your own judgment.

#### Good Practice Examples

- Ask AI for ideas, then review results with a peer.
- Use AI to help design a parser, then discuss and rewrite together.

#### Bad Practice Examples

- Copy-pasting AI-generated code you don't understand.
- Failing to explain how copied code works during an evaluation.

***

## V. Mandatory Part - cub3D

| Program name | cub3D |

### Requirements

- Display different wall textures (customizable), varying by wall side (North, South, East, West).
- Floor and ceiling colors must be settable to two different values.
- The program displays the image in a window, respecting these rules:
  - Left/right arrow keys: look left/right in the maze.
  - W/A/S/D: move viewpoint.
  - ESC: close window and quit cleanly.
  - Clicking the window "red cross": closes window and quits cleanly.
- **Recommended:** use MiniLibX image functions.
- The program must take as its first argument a scene description file with a `.cub` extension.

#### Map Characters

- Only 6 possible characters:  
  - `0`: empty space  
  - `1`: wall  
  - `N,S,E,W`: player starting position and orientation

**Example valid map:**
```
111111
100101
101001
1100N1
111111
```

- The map must be closed/surrounded by walls; if not, the program must return an error.
- Except for the map, each type of element can be separated by one or more empty lines and appear in any order.
- The map must be the last file element and parsed as it looks in the file (spaces are part of the map).
- Each element (except the map) begins with a type identifier (NO, SO, WE, EA, F, C).

#### Texture and Color Examples

- North texture:  
  `NO ./path_to_the_north_texture`
- South texture:  
  `SO ./path_to_the_south_texture`
- West texture:  
  `WE ./path_to_the_west_texture`
- East texture:  
  `EA ./path_to_the_east_texture`
- Floor color:  
  `F 220,100,0`  (RGB, 0-255)
- Ceiling color:  
  `C 225,30,0`   (RGB, 0-255)

#### Example .cub Scene
```
NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture
F 220,100,0
C 225,30,0
111111
100101
101001
1100N1
111111
```

- If any misconfiguration is found, the program must return "Error\n" followed by an explicit error message.

***

## VI. Bonus Part

*Bonuses will only be evaluated if your mandatory part is perfect (i.e., complete and robust, no failures).*

Bonus list:

- Wall collisions
- A minimap system
- Doors (open/close)
- Animated sprites
- Rotate the viewpoint with the mouse

> You may use extra functions/symbols or modify the scene file format for the bonus part as long as you justify their use during your evaluation.

***

## VII. Examples

- Wolfenstein 3D original design replica using raycasting.
- Example project (mandatory part).
- Bonus examples: minimap, floor/ceiling textures, animated sprite.
- Advanced bonus: HUD, health bar, shadow effect, shooting weapons.

***

## VIII. Submission and Peer-Evaluation

- Submit your assignment to your Git repository as usual; only work in your repository is evaluated.
- During the evaluation, a brief project modification may be requested—e.g., small code/update.
- Be prepared for evaluation guidelines requiring quick modifications, demonstrating your understanding.
- The modification can include minor code updates, new display/data structure changes, etc.

***

**Copyright Notice:**  
This document is for educational purposes only. All images are shown under Fair Use.