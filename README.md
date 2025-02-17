# Mouse Knights: Hedgehog

> Nguyen Chi Minh, 24020232 

# Game story
- This is Mouse Knghits: Hedgehog, an action roguelike and top-down shooter game.
- The game tells the story of a journey to defeat a witch who is a hedgehog and who killed Mouse's family when he was a child.
- You will take on the role of Mouse to defeat the witch.

# Game preview

# Config
- ***Due to linking issues with macOS, I coded everything in a single file to avoid missing library references between files.
- config sdl2 for macOS:
make a file name makefile which include this:

    all:
	    g++ -F/Library/Frameworks \
        -framework SDL2 \
        -framework SDL2_image \
        -rpath /Library/Frameworks \
        main.cpp -o main




# Reference:

    https://fb.watch/xOY2rD-J4Y/
    https://gist.github.com/armornick/3434362
    claude.ai
