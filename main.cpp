#include <iostream>
#include <SDL.h>
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
#include "dino.h"
#include "helper_functions.h"
#include "stage.h"
#include "rendering_functions.h"


using namespace std;

 

int run() {
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    Event event;
    srand(1);
    SetUp(window, renderer);

    Stage stage;
    int curStage = 0;

    vector<bool> isSet(2);

    Player player;
    player.Setplayer(renderer);
    player.bullet.SetPlayerBullet(renderer);
    

    stage.SetStage1(renderer);

    int num = 4;
    vector<Dino> dino;
    for(int i = 0; i < num; i++){
        Dino temp;
        temp.SetDino(renderer, (i+1)*200);
        // temp.Fire();
        dino.push_back(temp);
    
    }

    SDL_RenderPresent(renderer);

    while(event.appIsRunning) {
        if(curStage == 0) {
            event.checkHome();

            if(!isSet[curStage]) {
                stage.SetHome(renderer);
                isSet[curStage] = true;
            }

            if(event.mouseButtonLeftDown && event.playDown) {
                curStage++;
                event.mouseButtonLeftDown = false;
            }

            

            

            RenderHome(event, renderer, stage);
        }
        else if(curStage == 1) {
            event.CheckEvent();
            RenderStage1(event, renderer, stage, player, dino);
        }

        
    }
    



    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}











int main(int argc, char const *argv[]) {
    run();
    return 0;
}



