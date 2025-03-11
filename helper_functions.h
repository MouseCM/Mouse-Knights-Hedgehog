// #include "drawing_functions.h"


using namespace std;


void SetUp(SDL_Window* &window, SDL_Renderer* &renderer) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL could not be initialized: " << SDL_GetError();
    }
    else {
        cout << "SDL video system is ready to go\n";
    }


    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        "Mouse Knights: Hedgehog", // window title
        SDL_WINDOWPOS_UNDEFINED, // initial x position
        SDL_WINDOWPOS_UNDEFINED, // initial y position
        SCREEN_WIDTH, // SCREEN_WIDTH, in pixels
        SCREEN_HEIGHT, // SCREEN_HEIGHT, in pixels
        SDL_WINDOW_SHOWN // flags - see below
    );

    // Check that the window was successfully created
    if (window == NULL) {
        cout << "Window is NULL";
        return;
    }
    
    // initialize renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
    SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        cout << "Renderer is NULL";
        return;
    }

    cout << "pass";
}

void Fire(Event &event, Player &player) {
    if (event.mouseButtonLeftDown) {
        player.Fire();
    }
}
bool Collision(SDL_Rect &rect1, SDL_Rect &rect2) {
    if (rect1.x + rect1.w >= rect2.x && rect1.x <= rect2.x + rect2.w) {
        if (rect1.y + rect1.h >= rect2.y && rect1.y <= rect2.y + rect2.h) {
            return true;
        }
    }

    return false;
}

void IsCollision(Player &player, Dino &dino) {
    if (dino.dinoHP <= 0) {
        return;
    }

    if (player.bullet.isFiring) {
        if(Collision(player.bullet.bullet, dino.dino)) {
            dino.dinoHP -= player.bullet.damage;
            // player.bullet.isFiring = false;
        }

        // if(Collision(player.player, player.bullet.bullet)) {
        //     player.playerHP -= player.bullet.damage;
        // }
    }

    
}