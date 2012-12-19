Phynball
========

Physically Based Project - 2D Pinball Game

Instruction to build on Windows:

- Downlaod the zip file
- Extract all files
- Open VisualStudio 2010 and open the solution (actually double clicking on the solution could fail, so open it from VisualStudio)
- Go to Project/Properties/Configuration Properties/Linker/General
- Under Additional Library Directories add "PATH TO YOUR FOLDER"\libs\Simple OpenGL Image Library\lib\
- Under Additional Library Directories add "PATH TO YOUR FOLDER"\PBSproject\GLUT\
- Compile in Release/Win32 mode
- Run the executable
- Note: can it be that it says that the glut32.dll is not found, just copy and paste it to the same folder where the executable is.

Note about the code:

- To tilt left pale: use x key
- To tilt right pale: use n key
- If the animation is to slow or to fast try to increase the timestep in Constants.h file
