# A simple game engine using the ECS pattern and OpenGL

ECS method based on https://code.austinmorlan.com/austin/ecs

To build this project in Visual Studio 2019:

  1: Open the Property Manager window under View -> Other Windows
  
  2: Expand the root item and right-click on Debug|Win32 -> Add Existing Property Sheet
  
  3: Select the OpenGL-PropertySheet.props file in the project directory
  
  4: Do the same thing for Release|Win32
  
  
If you get the warning:

  warning LNK4098: defaultlib \<library\> conflicts with use of other libs; use /NODEFAULTLIB:library
  
Open the project properties window, go to Linker -> Input -> Ignore Specific Default Libraries and add the conflicting library
