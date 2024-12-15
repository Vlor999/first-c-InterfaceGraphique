# First Graphical Interface

## Description
This project simulates the movement and collision of multiple spheres (or "bubbles") within a graphical interface. It uses SDL2 for rendering and handles physics-based interactions like collisions, gravity, and boundary effects. The simulation provides visual feedback on how the spheres interact and react to each other based on predefined physical laws.

## Features
- **Graphical Rendering**: The simulation uses SDL2 to render the spheres and their movements.
- **Collision Detection and Response**: Handles sphere-sphere and sphere-boundary collisions with realistic physics.
- **Random Initialization**: Spheres are initialized with random positions, radii, velocities, and colors.
- **Optimized Collision Checking**: Uses a grid-based system to reduce unnecessary collision checks.

## Prerequisites
- SDL2 library installed on your system.
- GCC compiler (or any C compiler that supports SDL2 and math libraries).
- A Unix-like environment is recommended for running the Makefile.

## Installation
1. Clone the repository:
   ```bash
   git clone <repository_url>
   cd <repository_folder>
   ```

2. Install dependencies:
   Ensure SDL2 is installed on your system. For example, on Ubuntu:
   ```bash
   sudo apt-get install libsdl2-dev
   ```

3. Compile the project:
   ```bash
   make compile
   ```

## Usage
Run the simulation with:
```bash
make run
```

Stop the simulation by closing the graphical window.

## Files
- **`main.c`**: Contains the main function and SDL2 loop.
- **`myBubble.h`**: Header file defining the `Sphere` struct and associated constants.
- **`Makefile`**: Automates compilation, running, and cleaning tasks.

## Constants
| Constant           | Description                                    |
|--------------------|------------------------------------------------|
| `LARGEUR`          | Width of the simulation window (800 px).       |
| `HAUTEUR`          | Height of the simulation window (800 px).      |
| `COULEUR_FOND`     | Background color (black: `0x0000000`).         |
| `PESANTEUR`        | Gravity acceleration (`9.81 m/s^2`).          |
| `TIMESTEP`         | Time step for each simulation update.          |
| `AMORTISSEMENT`    | Damping factor for collisions (`0.97`).        |
| `NOMBRE_BALLE`     | Total number of spheres (1000).               |


## Project Structure
- **Physics Engine**: Includes functions like `gereCollision` and `deplaceBalle` to handle sphere physics.
- **Rendering**: Functions like `dessineSphere` render spheres on the SDL2 surface.
- **Optimization**: Grid-based collision checks to avoid unnecessary computations.

## License
This project is licensed under the GPLv3 License. You are free to use, modify, and distribute this software under the following conditions:

## Troubleshooting
- **Compilation Errors**: Ensure that SDL2 is properly installed and that the include paths are correctly configured.
- **Performance Issues**: For simulations with a high number of spheres, consider reducing `NOMBRE_BALLE` or optimizing the grid-based collision detection further.

## Future Improvements
- Add user controls for interaction (e.g., adding/removing spheres in real-time).
- Enhance visual effects with smoother rendering or additional animations.
- Support for customizable parameters (e.g., gravity, damping factor) via a configuration file.



