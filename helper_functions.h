// #include "drawing_functions.h"


using namespace std;
int SetUp() {
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
    
    // initialize renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
    SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        cout << "Renderer is NULL";
        return 1;
    }

    return 0;
}

void Fire(Player &player) {
    if (event.mouseButtonLeftDown) {
        if (player.bullet.numBullet == 0) {
            SDL_GetMouseState(&player.bullet.aimX, &player.bullet.aimY);

            player.bullet.deltaX = (player.bullet.aimX - player.bullet.bullet.w/2) - (player.player.x + player.player.w/2 - player.bullet.bullet.w/2);
            player.bullet.deltaY = (player.bullet.aimY - player.bullet.bullet.h/2) - (player.player.y + player.player.h/2 - player.bullet.bullet.h/2);
            player.bullet.angle = atan2(player.bullet.deltaY, player.bullet.deltaX);
            player.bullet.deltaX = player.player.x + player.player.w/2 - player.bullet.bullet.w/2;
            player.bullet.deltaY = player.player.y + player.player.h/2 - player.bullet.bullet.h/2;
        }
        player.bullet.numBullet++;
        player.bullet.isFiring = true;
    }
}


void IsCollision(Player &player, Dino &dino) {
    if (dino.dinoHP <= 0) {
        return;
    }
    
    if (player.bullet.isFiring && player.bullet.numBullet >= 1) {
        if (player.bullet.bullet.x + player.bullet.bullet.w >= dino.dino.x && player.bullet.bullet.x <= dino.dino.x + dino.dino.w &&
            player.bullet.bullet.y + player.bullet.bullet.h >= dino.dino.y && player.bullet.bullet.y <= dino.dino.y + dino.dino.h) {
            player.bullet.isFiring = false;
            player.bullet.numBullet = 0;
            dino.dinoHP -= 20;
        }
    }
}