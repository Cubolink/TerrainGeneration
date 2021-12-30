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

This application is compiled with CMake.

### Linking Errors
Depending on the make generator and compiler you use,
**YOU MAY HAVE TO USE DEPENDENCIES FOR YOUR PLATFORM**, so feel free to modify the CMakeLists.txt and Dependencies. For example,
you may have to use precompiled binaries for 32 bits instead of 64 bits, or even precompile your own Dependencies.

### Generate makefile with CMakeLists
On a terminal in the folder with the CMakeLists, run
```
    cmake -S . -B build
````
to create the makefile project inside the `build` folder. For windows MinGW, add the flag `-G "MinGW Makefiles` to create the makefile with MinGW.
You can choose your cmake generator with the flag `-G`, check what generators you have by running ````cmake --help````.

### Compile with the makefile
First, go to your `build` folder.

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
The `src` folder stores the project source files.

### Source files
The main is in `Application.cpp`.

#### OpenGL
`vertexbuffer.h, indexbuffer.h, vertexarray.h, vertexbufferlayout.h` allows to handle the openGL buffers.
`texture.h` can read an image and load it as texture to GL.

`renderer.h` use the previous information to render (draw) them with GL. But as drawing handling different buffers can be complicated,
this renderer can handle shapes. With `shape.h`, you can create some shapes, that handles those GL buffers.

For drawing, we also need GLSL shaders, so `shader.h` can load them from files, compile them, and then
the renderer can use them to draw. Some shaders use many uniforms, so `light.h` and `material.h` handle
the lighting uniforms of those lighting shaders.

`glerrorhandler.h` allows us to print the GL errors that can happen, so we can debug. Use the GLCall() MACRO to
run GL functions with this ability.

#### Camera
We draw using the Model View Projection, and with the previous described section
we can handle the model section, and the projection is simply defined in the main Application loop. For the view we need `camera.h`.

We can get the view matrix from Camera in `camera.h`, that camera handles its position and angles to calculate its 
"eye", "center" and "up" and use them with GL look_at to get the view matrix. It handles the speed of the position and angles too,
and calling a method we can use that information to update its position and angles after a delta time. 
It's easy to change those parameters when in need, but it can be hard to control them with inputs, so a controller class is made.

`controler.h` has a CameraController to handle movement directions caused by inputs, and then use that information to update the Camera properties.

#### Noise
`noise.h` can write values using noise over a 2D vector. It uses perlin noise with the different octaves.
The generated matrix can be used with `shape.h` to generate a shape, with colored vertices with normals, the indices, buffers, all that
a shape needs. That shape then can be drawn with the renderer.

`obj_files.h` can store these kinds of shapes
(actually only the shapes where each vertex has 3 position coordinates, 3 coordinates for rgb color, and 3 coords for normals).
IT DOES NOT SUPPORT OTHER KIND OF SHAPES.
Also, be aware that `.obj` files doesn't officially support colored vertices, so this information isn't actually written, it's skipped.

So the application use it to store the noise map in a `.obj` file when it's closing.

#### Application
It starts setting up all the GL stuff, with inputs and everything. In the main loop, the
terrain is updated only when a change in a noise variable is made from the GUI. When closing the window,
the program stores the terrain shape in a `.obj` file. After that, the program ends.

There's a bug I haven't been able to fix that makes the program freeze at the end instead of returing, but
you can close the command line after the `.obj` is saved.
