# Terraingen - Interactive Procedural Terrain Generator
OpenGL C++ Application to generate terrain using noise.
The application:
* Visualize the generated terrain.
* Updates the terrain when changing parameters in the application graphic interface
* Stores the terrain in a .obj file when closing the program

---
## Execution instructions
Run the executable.

#### Camera key controls
```
    Arrows -> Rotates the camera
    
    WASD -> Move the camera position in the XY plane
    
    Space -> Move the camera up in the Z axis
    
    L-Shift -> Move the camera down in the Z axis
```

#### Terrain parameter controls
In the window, a widget with a list of alterable parameters will allow you to change the terrain.
```
    seed -> seed used for the random generation
    scale -> scales the frequency of the noise
    octaves -> number of noise octaves to add 
    persistance -> amplitude factor of each octave respect to the previous one
    lacunarity -> frequency factor of each octave respect to the previous one
    amplitude -> height-amplitude of the terrain in the z-axis 
    water level -> height altitude range (0 to 1) to color as water 
    width -> width of the terrain grid in the x-axis
    height -> height of the terrain grid in the y-axis
```

####

---
## Compile instructions

This application is compiled with CMake

### Generate makefile with CMakeLists
On a terminal in the folder with the CMakeLists, run
```
    cmake -S . -B build
````
to create the makefile project inside the `build` folder. For windows MinGW, add the flag `-G "MinGW Makefiles` to create the makefile with MinGW.
You can choose your cmake generator with the flag `-G`, check what generators you have by running ````cmake --help````.

### Compile with the makefile

If you're using linux, then run
```
    make
```
and the `terraingen` executable will be created.

If you generated the makefile with MinGW in windows, you can use
```
    mingw32-make
```
to create the executable.

---
---
## Project structure
The folder `Dependencies` contains the compiled libraries, with the headers files to use.
The folder `resources` contains the shaders that can be compiled, and texture resources.
Inside `src/vendor`, there are source libraries that are included for the project.
The `src` folder stores the project headers and cpp files.

