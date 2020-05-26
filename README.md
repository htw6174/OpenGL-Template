# Asteroids
A tribute to the game _Asteroids (1979)_ in our Game Engine. Written in C++ using GLFW, GLM, and GLEW.

[![Generic badge](https://img.shields.io/badge/Status-WIP-Yellow.svg)](https://shields.io/)

![ProjectGif](/images/shootingAsteroids.gif)


## Build
To build this project in Visual Studio 2019:
  1. Open the Property Manager window under `View -> Other Windows`
  2. Expand the root item and right-click on `Debug|Win32 -> Add Existing Property Sheet`
  3. Select the `OpenGL-PropertySheet.props` file in the project directory
  4. Repeat this process for `Release|Win32`
  
### Build Warnings
  
If you get the following warning:

  `warning LNK4098: defaultlib \<library\> conflicts with use of other libs; use /NODEFAULTLIB:library`
  
1. Open the project properties window, 
2. Go to `Linker -> Input -> Ignore Specific Default Libraries`
3. Add the conflicting library to the field

## Authors
Hardy Whitney — Lucas Rumney — Cody Stough

## Attribution

### Template
Used the development template established in our [OpenGL Development Template](https://github.com/htw6174/OpenGL-Template) for Microsoft Visual Studio.

### Entity Component System Structure
ECS Structure based heavily on Austin Morlan's [amazing article](https://code.austinmorlan.com/austin/ecs).



