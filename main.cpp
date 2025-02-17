#include <iostream>
#include <random>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
using namespace std;

int main(int argc, char const *argv[])
{
    int resW = 1280;
    int resH = 720;
    
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
        resW, // width, in pixels
        resH, // height, in pixels
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


    int w, h;
    img = IMG_LoadTexture(renderer, "assets/mouse.png");
    // img = IMG_LoadTexture(renderer, "assets/mouse.jpeg");
	SDL_QueryTexture(img, NULL, NULL, &w, &h);
    SDL_Rect sdlRect; sdlRect.x = resW/4; sdlRect.y = resH/4; sdlRect.w = w/10; sdlRect.h = h/10; 
    int numPixelsToMovePerFrame = sdlRect.w/3;



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

                if (event.key.keysym.scancode == SDL_SCANCODE_UP) {
                upArrowDown = true;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_LEFT) {
                leftArrowDown = true;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_DOWN) {
                downArrowDown = true;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
                rightArrowDown = true;
                }
            }
            else if (event.type == SDL_KEYUP) {
                if (event.key.keysym.scancode == SDL_SCANCODE_UP) {
                upArrowDown = false;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_LEFT) {
                leftArrowDown = false;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_DOWN) {
                downArrowDown = false;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
                rightArrowDown = false;
                }
            }
        }
        //move rectangle
        if (upArrowDown) {
            sdlRect.y -= numPixelsToMovePerFrame;
        }
        if (leftArrowDown) {
            sdlRect.x -= numPixelsToMovePerFrame;
        }
        if (downArrowDown) {
            sdlRect.y += numPixelsToMovePerFrame;
        }
        if (rightArrowDown) {
            sdlRect.x += numPixelsToMovePerFrame;
        }

        // bounds checking and correction
        if (sdlRect.x < 0) {
            sdlRect.x = 0;
        }
        else if (sdlRect.x + sdlRect.w - 1 >= resW) {
            sdlRect.x = resW - sdlRect.w;
        }
        if (sdlRect.y < 0) {
            sdlRect.y = 0;
        }
        else if (sdlRect.y + sdlRect.h - 1 >= resH) {
            sdlRect.y = resH - sdlRect.h;
        }


        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        // SDL_SetRenderDrawColor(renderer, 176, 224, 230, SDL_ALPHA_OPAQUE);
        // SDL_RenderFillRect(renderer, &sdlRect);
        // SDL_RenderPresent(renderer);


		SDL_RenderCopy(renderer, img, NULL, &sdlRect);
		// flip the backbuffer
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