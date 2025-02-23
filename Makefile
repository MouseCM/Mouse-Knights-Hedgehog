all:
	g++ -F/Library/Frameworks -framework SDL2 -framework SDL2_image -rpath /Library/Frameworks main.cpp -o main