# Snake game made in C++ with the SDL2 libraries


# Compilation

Compile on Windows with g++ *.cpp -IC:\SDL\i686-w64-mingw32\include\SDL2 -LC:\SDL\i686-w64-mingw32\lib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf

# Requirements

In order to successfully compile and run this project, you will need to have the SDL 2 libraries on your system.
Download the latest SDL2-devel-2.x.x-mingw from SDL's official page and uncompress the inner folder's contents on an easy access directory (such as C:\SDL, for example). Download as well the latest SDL2_image from SDL_image page, uncompress, and merge the inner folder's content with the previously created for base SDL (inside C:\SDL)
From the new directory (C:\SDL), there is a folder named with your desired architecture. Copy that folder's bin content onto your MinGW's bin folder, and the include folder's contents onto MinGW's include

# Gameplay

Guide the snake to eat food while avoiding collisions with walls or the body of the snake. Arrow keys change the snake's direction.