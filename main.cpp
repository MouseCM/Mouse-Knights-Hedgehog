#include <iostream>
#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <random>
#include <vector>
#include <fstream>


#include "constants.h"
#include "audio.h"
#include "event.h"
#include "player.h"
#include "enemies/dino.h"
#include "enemies/firew.h"
#include "enemies/hedgehog.h"
#include "stage.h"
#include "helper_functions.h"
#include "rendering_functions.h"


using namespace std;

 

int run() {
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    Event event;
    srand(1);
    SetUp(window, renderer);

    
    Stage stage;


    Audio audio;
    audio.LoadAudio();
    audio.Theme();


    // game loop
    while(event.appIsRunning) {
        if(event.curStage == 0) {
            RenderHome(event, renderer, stage);
        }
        else if(event.curStage == 1) {
            RenderStage(event, renderer, stage, audio, "1");
        }
        else if(event.curStage == 2) {
            RenderStage(event, renderer, stage, audio, "2");
        }
        else if(event.curStage == 3) {
            RenderStage(event, renderer, stage, audio, "3");
        }
        else if(event.curStage == 4) {
            RenderStage(event, renderer, stage, audio, "4");
        }
        else if(event.curStage == 5) {
            RenderStage(event, renderer, stage, audio, "5");
        }
        else if(event.curStage == 6) {
            RenderStage(event, renderer, stage, audio, "6");
        }
        else if(event.curStage == END) {
            RenderEnd(event, renderer, stage);
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



