#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <random>
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <math.h>


#include "constants.h"
#include "event.h"
#include "player.h"
#include "globals.h"



using namespace std;




int main(int argc, char const *argv[])
{
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    Uint64 lastDrawTime = SDL_GetTicks64();
    
    



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
        cout << "Window is NULL";
        return 1;
    }
    

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
    SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        cout << "Renderer is NULL";
        return 1;
    }



    SDL_Texture *backgroundImg = IMG_LoadTexture(renderer, "assets/background.jpg");


    Player player;
    player.playerImg = IMG_LoadTexture(renderer, "assets/mouse.png");
	SDL_QueryTexture(player.playerImg, NULL, NULL, &player.playerW, &player.playerH);   
    player.Setplayer();
    
    
    



    player.bullet.bulletImg = IMG_LoadTexture(renderer, "assets/bullet.png");
    SDL_QueryTexture(player.bullet.bulletImg, NULL, NULL, &player.bullet.bulletW, &player.bullet.bulletH);
    player.bullet.SetPlayerBullet();
    





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
    

    
    Event event;
    // game loop
    while (event.appIsRunning) {
        event.CheckEvent();



        if (event.mouseButtonLeftDown) {
            
            if (player.bullet.numBullet == 0) {
                SDL_GetMouseState(&player.bullet.aimX, &player.bullet.aimY);
                player.bullet.bullet.x = player.player.x + player.player.w/2;    
                player.bullet.bullet.y = player.player.y + player.player.h/2;
                player.bullet.deltaX = player.bullet.aimX - player.player.x;
                player.bullet.deltaY = player.bullet.aimY - player.player.y;
                float angle = atan2(player.bullet.deltaY, player.bullet.deltaX);

                player.bullet.deltaX = cos(angle) * player.bullet.bulletSpeed;
                player.bullet.deltaY = sin(angle) * player.bullet.bulletSpeed;
            }
            player.bullet.numBullet++;
            player.bullet.isFiring = true;

        }
        

        //move rectangle
        if (event.wDown) {
            player.player.y -= player.playerSpeed;
        }
        if (event.aDown) {
            player.player.x -= player.playerSpeed;
        }
        if (event.sDown) {
            player.player.y += player.playerSpeed;
        }
        if (event.dDown) {
            player.player.x += player.playerSpeed;
        }


        
        // player border collision
        player.CheckBorderCollision();

        player.playerHPRect.x = player.player.x;
        player.playerHPRect.y = player.player.y-25;
        // player.playerHP = 50;



        if(player.bullet.isFiring && player.bullet.numBullet >= 1){
            player.bullet.bullet.x += player.bullet.deltaX;
            player.bullet.bullet.y += player.bullet.deltaY;
        }


        // check bullet border collision
        player.bullet.CheckBorderCollision();


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


        player.playerHPRect.w = player.playerW*1.5;
        SDL_Rect temp = {player.player.x, player.player.y-25, player.playerW*1.5, 10};
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &temp);
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &player.playerHPRect);


        SDL_RenderCopy(renderer, dinoImg, NULL, &dino);

        if(player.bullet.isFiring && player.bullet.numBullet >= 1){
            // bullet hitbox
            // SDL_SetRenderDrawColor(renderer, 255, 105, 180, SDL_ALPHA_OPAQUE);
            // SDL_RenderFillRect(renderer, &bullet);¥¥=-09876543

            SDL_RenderCopy(renderer, player.bullet.bulletImg, NULL, &player.bullet.bullet);
        }
        


        // // player hitbox
        // SDL_SetRenderDrawColor(renderer, 255, 105, 180, SDL_ALPHA_OPAQUE);
        // SDL_RenderFillRect(renderer, &player);

		SDL_RenderCopy(renderer, player.playerImg, NULL, &player.player);
		// flip the backbufferasdaw
		// this means that everything that we prepared behind the screens is actually shown
		SDL_RenderPresent(renderer);
        SDL_Delay(16);
        lastDrawTime = SDL_GetTicks64();
    }





    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}
