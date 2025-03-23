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

void CheckBorderCollision(Player::Bullet &bullet, Stage &stage, vector<SDL_Rect> box) {
    if(bullet.bullet.x < stage.background.x+LEFT) {
        bullet.isFiring = false;
    }
    else if (bullet.bullet.x > stage.background.x + RIGHT - bullet.bullet.w) {
        bullet.isFiring = false;
    }
    if(bullet.bullet.y < stage.background.y+UP) {
        bullet.isFiring = false;
    }
    else if(bullet.bullet.y > stage.background.y + DOWN - bullet.bullet.h) {
        bullet.isFiring = false;
    }

    for(int i = 0; i < box.size(); i++) {
        // cout << bullet.bullet.x+bullet.bullet.w << ' ' << stage.background.x + box[i].x << endl;
        // cout << bullet.bullet.x+bullet.bullet.w << ' ' << stage.background.x+box[i].x << endl;
        // cout << bullet.bullet.x << ' ' << stage.background.x+box[i].x+box[i].w << endl;
        // cout << bullet.bullet.y+bullet.bullet.h << ' ' << stage.background.y+box[i].y << endl;
        // cout << bullet.bullet.y << ' ' << stage.background.y+box[i].y << endl << endl;
        if(bullet.bullet.x+bullet.bullet.w >= stage.background.x+box[i].x && bullet.bullet.x <= stage.background.x+box[i].x+box[i].w && bullet.bullet.y+bullet.bullet.h >= stage.background.y+box[i].y && bullet.bullet.y <= stage.background.y+box[i].y+box[i].h) {
            bullet.isFiring = false;
        }
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




void MoveCamera(Event &event, Player &player, Stage &stage, vector<Dino> &dino, vector<Player::Bullet> &bullets, vector<vector<bool>> &canMove) {
    
    if (event.wDown) {
        int add = 5;
        // stage.camera.y -= 5;
        while(stage.camera.y+SCREEN_HEIGHT/2-player.player.h/2-add < UP) add--;
        while(!canMove[stage.camera.x+SCREEN_WIDTH/2+player.player.w/2-LEFT][stage.camera.y+SCREEN_HEIGHT/2-player.player.h/2-add-UP]) add--;
        while(!canMove[stage.camera.x+SCREEN_WIDTH/2-player.player.w/2-LEFT][stage.camera.y+SCREEN_HEIGHT/2-player.player.h/2-add-UP]) add--;

        stage.camera.y -= add;
        stage.background.y = -stage.camera.y;
        stage.portal.y += add;
        for(int i = 0; i < dino.size(); i++){
            dino[i].dino.y += add;
        }
        for(int i = 0; i < bullets.size(); i++) {
            bullets[i].bullet.y += add;
        }
        
    }
    if (event.aDown) {
        int add = 5;
        // stage.camera.x -= 5;
        while(stage.camera.x+SCREEN_WIDTH/2-player.player.w/2-add < LEFT) add--;
        while(!canMove[stage.camera.x+SCREEN_WIDTH/2-player.player.w/2-add-LEFT][stage.camera.y+SCREEN_HEIGHT/2+player.player.h/2-UP])add--;
        while(!canMove[stage.camera.x+SCREEN_WIDTH/2-player.player.w/2-add-LEFT][stage.camera.y+SCREEN_HEIGHT/2-player.player.h/2-UP])add--;
        stage.camera.x -= add;
        stage.background.x = -stage.camera.x;
        stage.portal.x += add;
        for(int i = 0; i < dino.size(); i++){
            dino[i].dino.x += add;
        }
        for(int i = 0; i < bullets.size(); i++) {
            bullets[i].bullet.x += add;
        }
    }
    if (event.sDown) {
        int add = 5;
        // stage.camera.y += 5;
        while(stage.camera.y+SCREEN_HEIGHT/2+player.player.h/2+add > DOWN) add--;
        while(!canMove[stage.camera.x+SCREEN_WIDTH/2+player.player.w/2-LEFT][stage.camera.y+SCREEN_HEIGHT/2+player.player.h/2+add-UP]) add--;
        while(!canMove[stage.camera.x+SCREEN_WIDTH/2-player.player.w/2-LEFT][stage.camera.y+SCREEN_HEIGHT/2+player.player.h/2+add-UP]) add--;

        stage.camera.y += add;
        stage.background.y = -stage.camera.y;
        stage.portal.y -= add;
        for(int i = 0; i < dino.size(); i++){
            dino[i].dino.y -= add;
        }
        for(int i = 0; i < bullets.size(); i++) {
            bullets[i].bullet.y -= add;
        }
        
    }
    if (event.dDown) {
        int add = 5;
        // stage.camera.x += 5;
        while(stage.camera.x+SCREEN_WIDTH/2+player.player.w/2+add > RIGHT) add--;
        while(!canMove[stage.camera.x+SCREEN_WIDTH/2+player.player.w/2+add-LEFT][stage.camera.y+SCREEN_HEIGHT/2-UP]) add--;
        stage.camera.x += add;
        stage.background.x = -stage.camera.x;
        stage.portal.x -= add;
    
        for(int i = 0; i < dino.size(); i++){
            dino[i].dino.x -= add;
        }

        for(int i = 0; i < bullets.size(); i++) {
            bullets[i].bullet.x -= add;
        }
    }
}