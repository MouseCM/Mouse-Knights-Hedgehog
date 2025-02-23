#include <iostream>
#include <random>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <math.h>



#include "bullet.h"
#include "constants.h"
#include "mouse.h"

using namespace std;




int main(int argc, char const *argv[])
{
    bool wDown = false;
    bool aDown = false;
    bool sDown = false;
    bool dDown = false;
    bool upArrowDown = false;
    bool downArrowDown = false;
    bool leftArrowDown = false;
    bool rightArrowDown = false;
    bool isFiring = false;
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    bool appIsRunning = true;
    int numMillisToThrottle = 6;
    Uint64 lastDrawTime = SDL_GetTicks64();
    SDL_Texture *img = NULL;
    int lastRotation = 0;
    int fireRotation = 0;
    int numBullet = 0;



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
        SCREEN_WIDTH, // SCREEN_WIDTH, in pixels
        SCREEN_HEIGHT, // SCREEN_HEIGHT, in pixels
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




    Mouse mouse;
    
    // int mouseW, mouseH;
    img = IMG_LoadTexture(renderer, "assets/mouse.png");
    // // img = IMG_LoadTexture(renderer, "assets/mouse.jpeg");
	SDL_QueryTexture(img, NULL, NULL, &mouse.mouseW, &mouse.mouseH);
    // int mouseHP = 100;
    // SDL_Rect mouseHPRect;
    // mouseHPRect.w = mouseW*1.5;
    // mouseHPRect.h = 10;


    mouse.mouse.w = mouse.mouseW*1.5; 
    mouse.mouse.h = mouse.mouseH*1.5; 
    mouse.mouse.x = SCREEN_WIDTH/2-mouse.mouse.w/2; 
    mouse.mouse.y = SCREEN_HEIGHT/1.2-mouse.mouse.h/2; 



    bulletImg = IMG_LoadTexture(renderer, "assets/bullet.png");
    SDL_QueryTexture(bulletImg, NULL, NULL, &bulletW, &bulletH);
    bullet.w = bulletW*1.5;
    bullet.h = bulletH*1.5;
    

    int aimX = 0;
    int aimY = 0;
    // float angle = 0;
    float deltaX = 0;
    float deltaY = 0;



    srand(1);
    int dinoW, dinoH;
    SDL_Texture *dinoImg = NULL;
    dinoImg = IMG_LoadTexture(renderer, "assets/dino.png");
    SDL_QueryTexture(dinoImg, NULL, NULL, &dinoW, &dinoH);
    SDL_Rect dino;
    dino.x = rand()%100 + 200;
    dino.y = rand()%100 + 200;
    dino.w = dinoW*3;
    dino.h = dinoH*3;
    // int bulletSpeed = 20;






    // border
    SDL_Texture *borderTextureTop = IMG_LoadTexture(renderer, "assets/border/top.jpg");
    SDL_Texture *borderTextureLeft = IMG_LoadTexture(renderer, "assets/border/left.jpg");
    SDL_Texture *borderTextureRight = IMG_LoadTexture(renderer, "assets/border/right.jpg");
    SDL_Texture *borderTextureBottom = IMG_LoadTexture(renderer, "assets/border/bottom.jpg");
    


    // game loop
    while (appIsRunning) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            // Handle each specific event
            if (event.type == SDL_QUIT) {
                appIsRunning = false;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                    appIsRunning = false;
                }
                if (event.key.keysym.scancode == SDL_SCANCODE_W) {
                    wDown = true;
                    // lastRotation = 0;
                }
                if (event.key.keysym.scancode == SDL_SCANCODE_A) {
                    aDown = true;
                    // lastRotation = 6;
                }
                if (event.key.keysym.scancode == SDL_SCANCODE_S) {
                    sDown = true;
                    // lastRotation = 4;
                }
                if (event.key.keysym.scancode == SDL_SCANCODE_D) {
                    dDown = true;
                    // lastRotation = 2;
                }
            
            }
            else if (event.type == SDL_KEYUP) {
                if (event.key.keysym.scancode == SDL_SCANCODE_W) {
                    wDown = false;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_A) {
                    aDown = false;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_S) {
                    sDown = false;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_D) {
                    dDown = false;
                }

            }

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    // Left mouse button was just released
                    
                    if (numBullet == 0) {
                        SDL_GetMouseState(&aimX, &aimY);
                        bullet.x = mouse.mouse.x+mouse.mouse.w/2;    
                        bullet.y = mouse.mouse.y+mouse.mouse.h/2;
                        deltaX = aimX-mouse.mouse.x;
                        deltaY = aimY-mouse.mouse.y;
                        float angle = atan2(deltaY, deltaX);

                        deltaX = cos(angle) * bulletSpeed;
                        deltaY = sin(angle) * bulletSpeed;

                    }
                    numBullet++;
                    isFiring = true;

                }
            }
        }

        

        //move rectangle
        if (wDown) {
            mouse.mouse.y -= mouse.mouseSpeed;
        }
        if (aDown) {
            mouse.mouse.x -= mouse.mouseSpeed;
        }
        if (sDown) {
            mouse.mouse.y += mouse.mouseSpeed;
        }
        if (dDown) {
            mouse.mouse.x += mouse.mouseSpeed;
        }

        // mouse border collision
        if (mouse.mouse.x < 25) {
            mouse.mouse.x = 26;
        }
        else if (mouse.mouse.x + mouse.mouse.w + 26 >= SCREEN_WIDTH) {
            mouse.mouse.x = SCREEN_WIDTH - mouse.mouse.w -25;
        }
        if (mouse.mouse.y < 25) {
            mouse.mouse.y = 26;
        }
        else if (mouse.mouse.y + mouse.mouse.h + 26 >= SCREEN_HEIGHT) {
            mouse.mouse.y = SCREEN_HEIGHT - mouse.mouse.h -25;
        }

        mouse.mouseHPRect.x = mouse.mouse.x;
        mouse.mouseHPRect.y = mouse.mouse.y-25;
        mouse.mouseHP = 50;



        if(isFiring && numBullet >= 1){
            
            bullet.x += deltaX;
            bullet.y += deltaY;
        }


        // check bullet border collision
        if(bullet.x <= 0){
            isFiring = false;
            numBullet = 0;
        }
        else if (bullet.x + bullet.w >= SCREEN_WIDTH) {
            isFiring = false;
            numBullet = 0;
        }
        else if(bullet.y <= 0){
            
            isFiring = false;
            numBullet = 0;
        }
        else if (bullet.y + bullet.h >= SCREEN_HEIGHT) {
            isFiring = false;
            numBullet = 0;
        }


        SDL_Rect background = {25, 25, SCREEN_WIDTH-50, SCREEN_HEIGHT-50};
        SDL_RenderCopy(renderer, backgroundImg, NULL, &background);


        SDL_Rect topBorder = {0, 0, SCREEN_WIDTH, 25};
        SDL_Rect bottomBorder = {0, SCREEN_HEIGHT - 25, SCREEN_WIDTH, 25};
        SDL_Rect leftBorder = {0, 0, 25, SCREEN_HEIGHT};
        SDL_Rect rightBorder = {SCREEN_WIDTH - 25, 0, 25, SCREEN_HEIGHT};
        SDL_RenderCopy(renderer, borderTextureTop, NULL, &topBorder);
        SDL_RenderCopy(renderer, borderTextureBottom, NULL, &bottomBorder);
        SDL_RenderCopy(renderer, borderTextureLeft, NULL, &leftBorder);
        SDL_RenderCopy(renderer, borderTextureRight, NULL, &rightBorder);


        mouse.mouseHPRect.w = float(mouse.mouseHP)/100 * mouse.mouseW*1.5;
        SDL_Rect temp = {mouse.mouse.x, mouse.mouse.y-25, mouse.mouseW*1.5, 10};
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &temp);
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &mouse.mouseHPRect);


        SDL_RenderCopy(renderer, dinoImg, NULL, &dino);

        if(isFiring && numBullet >= 1){
            // bullet hitbox
            // SDL_SetRenderDrawColor(renderer, 255, 105, 180, SDL_ALPHA_OPAQUE);
            // SDL_RenderFillRect(renderer, &bullet);¥¥=-09876543

            SDL_RenderCopy(renderer, bulletImg, NULL, &bullet);
            
        }
        


        // // mouse hitbox
        // SDL_SetRenderDrawColor(renderer, 255, 105, 180, SDL_ALPHA_OPAQUE);
        // SDL_RenderFillRect(renderer, &mouse);

		SDL_RenderCopy(renderer, img, NULL, &mouse.mouse);
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
