# First_2d_Sidescroller
  
Testing 2d sidescrolling with MinGW, SDL, SDL_image
  
Used libraries:
MinGW (as compiler)  
SDL2  
http://libsdl.org/download-2.0.php  
http://libsdl.org/release/SDL2-devel-2.0.5-mingw.tar.gz  
SDL_image  
https://www.libsdl.org/projects/SDL_image/  
https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.1-mingw.tar.gz  
SDL_mixer  
https://www.libsdl.org/projects/SDL_mixer/  
https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-devel-2.0.1-mingw.tar.gz  
  
From time to time, there will be a static compiled version for windows, so you can use it without the MinGW-compiler.
  
How to compile the program by yourself (for eclipse cdt (c/c++)):  
    1.  Download eclipse (because you need it)  
    2.  Download the required libraries (MinGW, SDL2, SDL_image)  
    3.  Install the libraries (start with MinGW -> SDL2, SDL_image, and SDL_mixer at last)  
		3.1. For MinGW, you only need to install 'mingw-base' (or so) and 'mingw-cpp' (or so)  
		3.2. For SDL2, SDL2_image and SDL_mixer, you need to copy the files from '{Your processor type}/include' and '.../lib' into your '{MinGW folder}/{include and|or lib}' folder  
    4.  Download the source code of this project  
    5.  Create a new c++ project in eclipse  
    6.  Import the source files into the project  
    7.  Project properties -> C/C++ Build -> Settings -> MinGW C++ Linker -> Libraries -> Add (in order) 'mingw32', 'SDL2main', 'SDL2', 'SDL2_image', 'SDL_mixer'  
    8.  Dont forget to add '-std=c++11' to C/C++ Build -> Settings -> GCC C++ Compiler -> Miscellaneous  
		8.1. If you want to compile it so, that you can play without console, add '-mwindows' behind the '-std=c++11'  
    9.  Compile  
    10. Copy the .dll files and the 'Audio'/'Img'/'Maps' directories into the 'Debug' folder of the project  
    11. Enjoy!  
If it still doesn't compile, you need to check if MinGW is added to your system enviroment PATH variable.