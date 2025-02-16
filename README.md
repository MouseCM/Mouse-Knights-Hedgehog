


config sdl2:

make a file name makefile and paste this to file:

    all:

        g++ -I/Library/Frameworks/SDL2.framework/Headers -F/Library/Frameworks -framework SDL2 -Wl,-rpath,/Library/Frameworks main.cpp -o main
