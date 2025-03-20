#include <iostream>
#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <random>
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <math.h>
#include <fstream>


#include "constants.h"
#include "event.h"
#include "player.h"
#include "enemies/dino.h"
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


    while(event.appIsRunning) {
        if(event.curStage == 0) {
            RenderHome(event, renderer, stage);
        }
        else if(event.curStage == 1) {
            RenderStage(event, renderer, stage, "1");
        }
        else if(event.curStage == 2) {
            RenderStage(event, renderer, stage, "2");
        }
        else if(event.curStage == 3) {
            RenderStage3(event, renderer, stage, "3");
        }
        else {
            event.appIsRunning = false;
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



