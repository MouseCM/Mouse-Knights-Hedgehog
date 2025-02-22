#include <iostream>
#include <random>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <math.h>
using namespace std;



const int WIDTH = 1280;
const int HEIGHT = 720;


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

    int mouseW, mouseH;
    img = IMG_LoadTexture(renderer, "assets/mouse.png");
    // img = IMG_LoadTexture(renderer, "assets/mouse.jpeg");
	SDL_QueryTexture(img, NULL, NULL, &mouseW, &mouseH);
    int mouseHP = 100;
    SDL_Rect mouseHPRect;
    mouseHPRect.w = mouseW*1.5;
    mouseHPRect.h = 10;
    SDL_Rect mouse; 
    mouse.w = mouseW*1.5; 
    mouse.h = mouseH*1.5; 
    mouse.x = WIDTH/2-mouse.w/2; 
    mouse.y = HEIGHT/1.2-mouse.h/2; 
    int mouseSpeed = 10;



    int bulletW, bulletH;
    SDL_Texture *bulletImg = NULL;
    bulletImg = IMG_LoadTexture(renderer, "assets/bullet.png");
    SDL_QueryTexture(bulletImg, NULL, NULL, &bulletW, &bulletH);
    SDL_Rect bullet;
    bullet.w = bulletW/2;
    bullet.h = bulletH/2;
    int bulletSpeed = 20;
    

    int aimX = 0;
    int aimY = 0;
    // float angle = 0;
    float deltaX = 0;
    float deltaY = 0;



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
                        bullet.x = mouse.x+mouse.w/2;    
                        bullet.y = mouse.y+mouse.h/2;
                        deltaX = aimX-mouse.x;
                        deltaY = aimY-mouse.y;
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
            mouse.y -= mouseSpeed;
        }
        if (aDown) {
            mouse.x -= mouseSpeed;
        }
        if (sDown) {
            mouse.y += mouseSpeed;
        }
        if (dDown) {
            mouse.x += mouseSpeed;
        }

        // mouse border collision
        if (mouse.x < 25) {
            mouse.x = 26;
        }
        else if (mouse.x + mouse.w + 26 >= WIDTH) {
            mouse.x = WIDTH - mouse.w -25;
        }
        if (mouse.y < 25) {
            mouse.y = 26;
        }
        else if (mouse.y + mouse.h + 26 >= HEIGHT) {
            mouse.y = HEIGHT - mouse.h -25;
        }

        mouseHPRect.x = mouse.x;
        mouseHPRect.y = mouse.y-25;



        if(isFiring && numBullet >= 1){
            
            bullet.x += deltaX;
            bullet.y += deltaY;
        }


        // check bullet border collision
        if(bullet.x <= 0){
            isFiring = false;
            numBullet = 0;
        }
        else if (bullet.x + bullet.w >= WIDTH) {
            isFiring = false;
            numBullet = 0;
        }
        else if(bullet.y <= 0){
            
            isFiring = false;
            numBullet = 0;
        }
        else if (bullet.y + bullet.h >= HEIGHT) {
            isFiring = false;
            numBullet = 0;
        }


        SDL_Rect background = {25, 25, WIDTH-50, HEIGHT-50};
        SDL_RenderCopy(renderer, backgroundImg, NULL, &background);


        SDL_Rect topBorder = {0, 0, WIDTH, 25};
        SDL_Rect bottomBorder = {0, HEIGHT - 25, WIDTH, 25};
        SDL_Rect leftBorder = {0, 0, 25, HEIGHT};
        SDL_Rect rightBorder = {WIDTH - 25, 0, 25, HEIGHT};
        SDL_RenderCopy(renderer, borderTextureTop, NULL, &topBorder);
        SDL_RenderCopy(renderer, borderTextureBottom, NULL, &bottomBorder);
        SDL_RenderCopy(renderer, borderTextureLeft, NULL, &leftBorder);
        SDL_RenderCopy(renderer, borderTextureRight, NULL, &rightBorder);


        mouseHPRect.w = mouseHP/100 * mouseW*1.5;
        // srand(1);
        mouseHP = 100;
        SDL_Rect temp = {mouse.x, mouse.y-25, mouseW*1.5, 10};
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &temp);
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &mouseHPRect);

        if(isFiring && numBullet >= 1){
            // bullet hitbox
            // SDL_SetRenderDrawColor(renderer, 255, 105, 180, SDL_ALPHA_OPAQUE);
            // SDL_RenderFillRect(renderer, &bullet);¥¥=-09876543

            SDL_RenderCopy(renderer, bulletImg, NULL, &bullet);
            
        }
        


        // // mouse hitbox
        // SDL_SetRenderDrawColor(renderer, 255, 105, 180, SDL_ALPHA_OPAQUE);
        // SDL_RenderFillRect(renderer, &mouse);

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
