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
        0, // initial x position
        0, // initial y position
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

    cout << "Setup successfully";
}

void Fire(SDL_Renderer *renderer, Event &event, Player &player, vector<Player::Bullet> &bullets) {
    if (event.mouseButtonLeftDown) {
        if(SDL_GetTicks64() >= player.bullet.reloadTime) {
            Player::Bullet bullet;
            bullet.SetPlayerBullet(renderer);
            SDL_GetMouseState(&bullet.aimX, &bullet.aimY);
            bullet.deltaX = bullet.aimX - (player.player.x + player.player.w/2);
            bullet.deltaY = bullet.aimY - (player.player.y + player.player.h/2);
            bullet.angle = atan2(bullet.deltaY, bullet.deltaX);
            bullet.deltaX = player.player.x + player.player.w/2 - bullet.bullet.w/2;
            bullet.deltaY = player.player.y + player.player.h/2 - bullet.bullet.h/2;
            // bullet.existTime = SDL_GetTicks64() + 1000;
            bullet.isFiring = true;
            bullets.push_back(bullet);
            player.bullet.reloadTime = SDL_GetTicks64() + 500;
        }
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

void CheckBorderCollision(Player::Bullet &bullet, Stage &stage) {
    if(bullet.bullet.x < stage.background.x+668+bullet.speed) {
        bullet.isFiring = false;
    }
    else if (bullet.bullet.x > stage.background.x + 1892 - bullet.bullet.w-bullet.speed) {
        bullet.isFiring = false;
    }
    if(bullet.bullet.y < stage.background.y+390+bullet.speed) {
        bullet.isFiring = false;
    }
    else if(bullet.bullet.y > stage.background.y + 1050 - bullet.bullet.h-bullet.speed) {
        bullet.isFiring = false;
    }
}

void IsCollision(Player::Bullet &bullet, Dino &dino) {
    if (dino.dinoHP <= 0) {
        return;
    }

    if (bullet.isFiring) {
        if(Collision(bullet.bullet, dino.dino)) {
            dino.dinoHP -= bullet.damage;
            bullet.isFiring = false;
            // player.bullet.isFiring = false;
        }

        // if(Collision(player.player, player.bullet.bullet)) {
        //     player.playerHP -= player.bullet.damage;
        // }
    }

    
}



bool CheckBorderCollision(Player &player, Stage &stage) {
    bool val = false;
    if (player.player.x <= stage.background.x + 668) {
        player.player.x = stage.background.x + 668;
        val = true;
    }
    else if (player.player.x + player.player.w >= stage.background.x + 1892) {
        player.player.x = stage.background.x + 1892 - player.player.w;
        val = true;
    }
    if (player.player.y <= stage.background.y + 390) {
        player.player.y = stage.background.y + 390;
        val = true;
    }
    else if (player.player.y + player.player.h >= stage.background.y + 1050) {
        player.player.y = stage.background.y + 1050 - player.player.h;
        val = true;
    }

    return val;
}