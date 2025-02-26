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
#include "dino.h"
#include "helper_functions.h"
#include "stage.h"
#include "rendering_functions.h"


using namespace std;



 

int run() {
    srand(1);
    SetUp();

    Player player;
    player.Setplayer(renderer);
    player.bullet.SetPlayerBullet(renderer);
    


    Stage stage;
    stage.SetStage();

    int num = 4;
    vector<Dino> dino;
    for(int i = 0; i < num; i++){
        Dino temp;
        temp.SetDino(renderer, (i+1)*200);
        dino.push_back(temp);
    }

    SDL_ShowCursor(SDL_DISABLE);


    while (event.appIsRunning) {
        event.CheckEvent();

        Fire(player);

        player.Move(event);

        player.CheckBorderCollision();

        player.bullet.Move(event);

        player.bullet.CheckBorderCollision();

        for(int i = 0; i < num; i++) {
            IsCollision(player, dino[i]);
        }
        

        RenderStage(renderer, stage);
        RenderPlayer(renderer, player);
        if(player.bullet.isFiring && player.bullet.numBullet >= 1){
            SDL_RenderCopy(renderer, player.bullet.bulletImg, NULL, &player.bullet.bullet);
        }
        for(int i = 0; i < num; i++) {
            RenderDino(renderer, dino[i]);
        }
        

        RenderCustomDotCursor(renderer);
        


		SDL_RenderPresent(renderer);
        SDL_Delay(16);
        lastDrawTime = SDL_GetTicks64();
    }



    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}



int main(int argc, char const *argv[])
{
    run();
    return 0;
}



