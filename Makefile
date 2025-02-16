all:
	g++ -I/Library/Frameworks/SDL2.framework/Headers -F/Library/Frameworks -framework SDL2 -Wl,-rpath,/Library/Frameworks main.cpp -o main