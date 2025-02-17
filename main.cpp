#include <iostream>
#include <random>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
using namespace std;

int main(int argc, char const *argv[])
{
    int WIDTH = 1280;
    int HEIGHT = 720;
    
    bool upArrowDown = false;
    bool leftArrowDown = false;
    bool downArrowDown = false;
    bool rightArrowDown = false;
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    bool appIsRunning = true;
    int numMillisToThrottle = 6;
    Uint64 lastDrawTime = SDL_GetTicks64();
    SDL_Texture *img = NULL;



    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL could not be initialized: " << SDL_GetError();
    }
    else {
        cout << "SDL video system is ready to go\n";
    }

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        "An SDL2 window", // window title
        SDL_WINDOWPOS_UNDEFINED, // initial x position
        SDL_WINDOWPOS_UNDEFINED, // initial y position
        WIDTH, // width, in pixels
        HEIGHT, // height, in pixels
        SDL_WINDOW_SHOWN // flags - see below
    );

    // Check that the window was successfully created
    if (window == NULL) {
        // In the case that the window could not be made...
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }
    

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
    SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        // In the case that the renderer could not be made...
        printf("Could not create renderer: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Texture *backgroundImg = IMG_LoadTexture(renderer, "assets/background.jpg");

    int w, h;
    img = IMG_LoadTexture(renderer, "assets/mouse.png");
    // img = IMG_LoadTexture(renderer, "assets/mouse.jpeg");
	SDL_QueryTexture(img, NULL, NULL, &w, &h);
    SDL_Rect mouse; 
    mouse.w = w/10; 
    mouse.h = h/10; 
    mouse.x = WIDTH/2-mouse.w/2; 
    mouse.y = HEIGHT/1.2-mouse.h/2; 
    
    int numPixelsToMovePerFrame = mouse.w/3;

    SDL_Texture *borderTextureTop = IMG_LoadTexture(renderer, "assets/border/top.jpg");
    SDL_Texture *borderTextureLeft = IMG_LoadTexture(renderer, "assets/border/left.jpg");
    SDL_Texture *borderTextureRight = IMG_LoadTexture(renderer, "assets/border/right.jpg");
    SDL_Texture *borderTextureBottom = IMG_LoadTexture(renderer, "assets/border/bottom.jpg");
    


    //main game/app loop
    while (appIsRunning) {
        //slowing things down a little, you can delete this if you like
        // while (SDL_GetTicks64() - lastDrawTime < numMillisToThrottle){}
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            // Handle each specific event
            if (event.type == SDL_QUIT) {
                appIsRunning = false;
            }
            else if (event.type == SDL_KEYDOWN) {

                if (event.key.keysym.scancode == SDL_SCANCODE_W) {
                    upArrowDown = true;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_A) {
                    leftArrowDown = true;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_S) {
                    downArrowDown = true;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_D) {
                    rightArrowDown = true;
                }
            }
            else if (event.type == SDL_KEYUP) {
                if (event.key.keysym.scancode == SDL_SCANCODE_W) {
                    upArrowDown = false;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_A) {
                    leftArrowDown = false;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_S) {
                    downArrowDown = false;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_D) {
                    rightArrowDown = false;
                }
            }
        }
        //move rectangle
        if (upArrowDown) {
            mouse.y -= numPixelsToMovePerFrame;
        }
        if (leftArrowDown) {
            mouse.x -= numPixelsToMovePerFrame;
        }
        if (downArrowDown) {
            mouse.y += numPixelsToMovePerFrame;
        }
        if (rightArrowDown) {
            mouse.x += numPixelsToMovePerFrame;
        }

        // bounds checking and correction
        if (mouse.x < 25) {
            mouse.x = 25;
        }
        else if (mouse.x + mouse.w + 26 >= WIDTH) {
            mouse.x = WIDTH - mouse.w-25;
        }
        if (mouse.y < 25) {
            mouse.y = 25;
        }
        else if (mouse.y + mouse.h + 26 >= HEIGHT) {
            mouse.y = HEIGHT - mouse.h-25;
        }


        SDL_Rect background = {0, 0, 0, 0};
        SDL_RenderCopy(renderer, backgroundImg, NULL, NULL);
        // SDL_SetRenderDrawColor(renderer, 176, 224, 230, SDL_ALPHA_OPAQUE);
        // SDL_RenderFillRect(renderer, &mouse);
        // SDL_RenderPresent(renderer);

        // SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE); // Red color for the border
        SDL_Rect topBorder = {0, 0, WIDTH, 25};
        SDL_Rect bottomBorder = {0, HEIGHT - 25, WIDTH, 25};
        SDL_Rect leftBorder = {0, 0, 25, HEIGHT};
        SDL_Rect rightBorder = {WIDTH - 25, 0, 25, HEIGHT};
        SDL_RenderCopy(renderer, borderTextureTop, NULL, &topBorder);
        SDL_RenderCopy(renderer, borderTextureBottom, NULL, &bottomBorder);
        SDL_RenderCopy(renderer, borderTextureLeft, NULL, &leftBorder);
        SDL_RenderCopy(renderer, borderTextureRight, NULL, &rightBorder);


		SDL_RenderCopy(renderer, img, NULL, &mouse);
		// flip the backbufferasdaw
		// this means that everything that we prepared behind the screens is actually shown
		SDL_RenderPresent(renderer);
        SDL_Delay(16);
        lastDrawTime = SDL_GetTicks64();

    }





    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    cout << "exiting..." << endl;
    SDL_Quit();

    return 0;
}