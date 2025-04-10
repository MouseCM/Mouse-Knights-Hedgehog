# Mouse Knights: Hedgehog

> Nguyen Chi Minh, 24020232 

# Game story
- This is Mouse Knghits: Hedgehog, an action roguelike and top-down shooter game.
- The game tells the story of a journey to defeat a witch who is a hedgehog and who killed Mouse's family when he was a child.
- You will take on the role of Mouse to defeat the witch.

# Game preview
**Home**
![Home](https://github.com/MouseCM/Mouse-Knights-Hedgehog/blob/main/assets/home.png)
**Stage**
Using W, A, S, D to move, left mouse click to fire bullet each 0.5s.
![Stage](https://github.com/MouseCM/Mouse-Knights-Hedgehog/blob/main/preview/stage.png)

**Boss**
![boss](https://github.com/MouseCM/Mouse-Knights-Hedgehog/blob/main/preview/boss.png) 


**Screen when win game**
![end](https://github.com/MouseCM/Mouse-Knights-Hedgehog/blob/main/assets/end.png)
# Config
- Due to linking issues with macOS, I coded everything in a single file to avoid missing library references between files.
- config sdl2 for macOS:

**Install sdl2, sdl2_image, sdl2_mixer using homebrew**     

      brew install sdl2   
      brew install sdl2_image
      brew install sdl2_mixer
        
**Create a file name makefile which include this:**

      SRC_DIR = .
      BUILD_DIR = build/debug
      CC = g++
      SRC_FILES = $(wildcard $(SRC_DIR)/main.cpp)
      INCLUDE_PATHS = -I/opt/homebrew/opt/sdl2/include/SDL2 -I/opt/homebrew/Cellar/sdl2_image/2.8.5/include -I/opt/homebrew/Cellar/sdl2_mixer/2.8.1_1/include 
      LIBRARY_PATHS = -L/opt/homebrew/opt/sdl2/lib -L/opt/homebrew/Cellar/sdl2_image/2.8.5/lib -L/opt/homebrew/Cellar/sdl2_mixer/2.8.1_1/lib
      COMPILER_FLAGS = -std=c++11 -Wall -O0 -g
      LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer
      
      all:
          $(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(SRC_FILES) -o main





# Reference:

    https://fb.watch/xOY2rD-J4Y/
    https://gist.github.com/armornick/3434362
    https://www.youtube.com/watch?v=XOk0aGwZYn8
    claude.ai
    chatgpt.com
