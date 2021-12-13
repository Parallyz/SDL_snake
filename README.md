## Snake game made in C++ with the SDL2 libraries


# Description

In this game you need to control the snake, namely
pick apples
then the snake will increase. And do not touch the borders and parts of the snake's body

# Instructions to run

You need to download the SDL2-devel-2.0 and SDL2_image-devel-2.0.5 libraries to run the game. Follow these steps to connect libraries
С/С++> General> Additional Include Directories> %PATH% \ SDL2 \ include;
and
SDL2_image-2.0.5 \ include;

Then, depending on the bit size of your system, we connect

For x86:
Linker> General> Additional Library Directories>% PATH% \ SDL2 \ lib \ x86;
and
%PATH% \ SDL2_image-2.0.5 \ lib \ x86;

For x64:
Linker> General> Additional Library Directories>% PATH% \ SDL2 \ lib \ x64;
and
% PATH% \ SDL2_image-2.0.5 \ lib \ x64;

Next:
Linker> Input>
AdditionalDependencies>
SDL2.lib;
SDL2main.lib;
SDL2_image.lib;

This project is written on the x64 bit system, so if you have another bit you need to replace the files:
SDL2.dll
SDL2_image.dll
zlib1.dll
libpng16-16.dll
to files of the corresponding bit size from folders:
% PATH% \ SDL2 \ lib \ x86;
and
% PATH% \ SDL2_image-2.0.5 \ lib \ x86;

That's all you need

# Інструкції для керування


Arrows change the direction of the snake
