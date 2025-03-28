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
    if(event.isLose) return;
    if (event.mouseButtonLeftDown) {
        if(SDL_GetTicks64() >= player.bullet.reloadTime && player.playerHP > 0) {
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

void DinoFire(Event event, SDL_Renderer *renderer, Dino &dino, Player &player) {
    if(event.isLose) return;
    if(SDL_GetTicks64() >= dino.bullet.reloadTime && dino.hp > 0) {
        // cout << '1' << endl;
        // dino.bullet.SetRect(renderer);
        // SDL_GetMouseState(&bullet.aimX, &bullet.aimY);

        dino.bullet.deltaX = player.player.x+player.player.w/2 - (dino.rect.x + dino.rect.w/2);
        dino.bullet.deltaY = player.player.y+player.player.h/2 - (dino.rect.y + dino.rect.h/2);
        dino.bullet.angle = atan2(dino.bullet.deltaY, dino.bullet.deltaX);
        dino.bullet.deltaX = dino.rect.x + dino.rect.w/2 - dino.bullet.rect.w/2;
        dino.bullet.deltaY = dino.rect.y + dino.rect.h/2 - dino.bullet.rect.h/2;
        // bullet.existTime = SDL_GetTicks64() + 1000;
        dino.bullet.isFiring = true;
        dino.bullet.reloadTime = SDL_GetTicks64() + 3000;
    }
}

bool Collision(SDL_Rect &rect1, SDL_Rect &rect2) {
    // if(event.isLose) return false;
    if (rect1.x + rect1.w >= rect2.x && rect1.x <= rect2.x + rect2.w) {
        if (rect1.y + rect1.h >= rect2.y && rect1.y <= rect2.y + rect2.h) {
            return true;
        }
    }

    return false;
}

void CheckBorderCollision(Event event, Player::Bullet &bullet, Stage &stage, vector<SDL_Rect> boxes) {
    if(event.isLose) return;
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

    for(int i = 0; i < boxes.size(); i++) {
        if(bullet.bullet.x+bullet.bullet.w >= stage.background.x+boxes[i].x && bullet.bullet.x <= stage.background.x+boxes[i].x+boxes[i].w && bullet.bullet.y+bullet.bullet.h >= stage.background.y+boxes[i].y && bullet.bullet.y <= stage.background.y+boxes[i].y+boxes[i].h) {
            bullet.isFiring = false;
        }
    }

}

void CheckBorderCollision(Event event, Dino::Bullet &bullet, Stage &stage, vector<SDL_Rect> boxes) {
    if(event.isLose) return;
    if(bullet.rect.x < stage.background.x+LEFT) {
        bullet.isFiring = false;
    }
    else if (bullet.rect.x > stage.background.x + RIGHT - bullet.rect.w) {
        bullet.isFiring = false;
    }
    if(bullet.rect.y < stage.background.y+UP) {
        bullet.isFiring = false;
    }
    else if(bullet.rect.y > stage.background.y + DOWN - bullet.rect.h) {
        bullet.isFiring = false;
    }

    for(int i = 0; i < boxes.size(); i++) {
        if(bullet.rect.x+bullet.rect.w >= stage.background.x+boxes[i].x && bullet.rect.x <= stage.background.x+boxes[i].x+boxes[i].w && bullet.rect.y+bullet.rect.h >= stage.background.y+boxes[i].y && bullet.rect.y <= stage.background.y+boxes[i].y+boxes[i].h) {
            bullet.isFiring = false;
        }
    }

}


// check player fire to dino
void IsCollision(Event event, Player::Bullet &bullet, Dino &dino) {
    if(event.isLose) return;
    if (dino.hp <= 0) {
        return;
    }

    if (bullet.isFiring) {
        if(Collision(bullet.bullet, dino.rect)) {
            dino.hp -= bullet.damage;
            bullet.isFiring = false;
        }
    } 
}

// check player fire to firew
void IsCollision(Event event, Player::Bullet &bullet, Firew &firew) {
    if(event.isLose) return;
    if (firew.hp <= 0) {
        return;
    }

    if (bullet.isFiring) {
        if(Collision(bullet.bullet, firew.rect)) {
            firew.hp -= bullet.damage;
            bullet.isFiring = false;
        }
    } 
}


// check dino fire player
void IsCollision(Event event, Dino::Bullet &bullet, Player &player) {
    if(event.isLose) return;
    if(player.playerHP <= 0) {
        return;
    }

    if(bullet.isFiring) {
        if(Collision(bullet.rect, player.player)) {
            player.playerHP -= bullet.damage;
            bullet.isFiring = false;
        }
    }
}


// check firew boom
void IsCollision(Event event, Firew &firew, Player &player) {
    if(event.isLose) return;
    if(player.playerHP <= 0) {
        return;
    }
    if(firew.hp <= 0) return;

    if(Collision(firew.rect, player.player)) {
        player.playerHP = max(0, player.playerHP-firew.damage);
        firew.hp = 0;
        firew.boomTime = SDL_GetTicks64();
    }
}

bool CheckEnemiesDead(vector<Dino> dinos, vector<Firew> firews) {
    // if(event.isLose) return;
    for(int i = 0; i < dinos.size(); i++) {
        if(dinos[i].hp > 0) return false;
    }

    for(int i = 0; i < firews.size(); i++) {
        if(firews[i].hp > 0) return false;
    }

    return true;
}


void DinoMove(Event event, vector<Dino> &dinos, Stage stage, Player player, vector<SDL_Rect> boxes) {
    if(event.isLose) return;
    float angle = 0;
    float tempX = 0;
    float tempY = 0;
    bool isPass = true;

    for(int i = 0; i < dinos.size(); i++) {
        if(dinos[i].hp <= 0) continue;
        isPass = true;
        angle = atan2(player.player.y+- dinos[i].rect.y, player.player.x - dinos[i].rect.x);
        tempX = dinos[i].deltaX - cos(angle);
        tempY = dinos[i].deltaY - sin(angle);
        if(tempX < stage.background.x+LEFT) {
            tempX = stage.background.x+LEFT;
        }
        else if (tempX > stage.background.x + RIGHT - dinos[i].rect.w) {
            tempX = stage.background.x + RIGHT - dinos[i].rect.w;
        }
        if(tempY < stage.background.y+UP) {
            tempY = stage.background.y+UP;
        }
        else if(tempY > stage.background.y + DOWN - dinos[i].rect.h) {
            tempY = stage.background.y + DOWN - dinos[i].rect.h;
        }
    
        for(int j = 0; j < boxes.size(); j++) {
            if(tempX+dinos[i].rect.w >= stage.background.x+boxes[j].x && tempX <= stage.background.x+boxes[j].x+boxes[j].w && tempY+dinos[i].rect.h >= stage.background.y+boxes[j].y && tempY <= stage.background.y+boxes[j].y+boxes[j].h) {
                isPass = false;
                break;
            }
        }

        if(isPass) {
            dinos[i].deltaX = tempX;
            dinos[i].deltaY = tempY;
            dinos[i].rect.x = tempX;
            dinos[i].rect.y = tempY;
        }
    }


}

void FirewMove(Event event, vector<Firew> &firews, Stage stage, Player player, vector<SDL_Rect> boxes) {
    if(event.isLose) return;
    float angle = 0;
    float tempX = 0;
    float tempY = 0;
    bool isPass = true;

    for(int i = 0; i < firews.size(); i++) {
        if(firews[i].hp <= 0) continue;
        isPass = true;
        angle = atan2(player.player.y - firews[i].rect.y, player.player.x - firews[i].rect.x);
        tempX = firews[i].deltaX + cos(angle);
        tempY = firews[i].deltaY + sin(angle);
        if(tempX < stage.background.x+LEFT) {
            tempX = stage.background.x+LEFT;
        }
        else if (tempX > stage.background.x + RIGHT - firews[i].rect.w) {
            tempX = stage.background.x + RIGHT - firews[i].rect.w;
        }
        if(tempY < stage.background.y+UP) {
            tempY = stage.background.y+UP;
        }
        else if(tempY > stage.background.y + DOWN - firews[i].rect.h) {
            tempY = stage.background.y + DOWN - firews[i].rect.h;
        }
        
        for(int j = 0; j < boxes.size(); j++) {
            if(tempX+firews[i].rect.w >= stage.background.x+boxes[j].x && tempX <= stage.background.x+boxes[j].x+boxes[j].w && tempY+firews[i].rect.h >= stage.background.y+boxes[j].y && tempY <= stage.background.y+boxes[j].y+boxes[j].h) {
                isPass = false;
                break;
            }
        }

        if(isPass) {
            firews[i].deltaX = tempX;
            firews[i].deltaY = tempY;
            firews[i].rect.x = tempX;
            firews[i].rect.y = tempY;
        }
    }
}





void MoveCamera(SDL_Renderer *renderer, Event &event, Player &player, Stage &stage, vector<Dino> &dinos, vector<Player::Bullet> &bullets, vector<vector<bool>> &canMove, vector<SDL_Rect> &boxes, vector<Firew> &firews) {
    if(event.isLose) return;

    if (event.wDown) {
        int add = 5;
        player.imgRect.x = 18;
        player.imgRect.y = 65;

        while(stage.camera.y+SCREEN_HEIGHT/2-player.player.h/2-add < UP) add--;
        while(!canMove[stage.camera.x+SCREEN_WIDTH/2+player.player.w/2-LEFT][stage.camera.y+SCREEN_HEIGHT/2-player.player.h/2-add-UP]) add--;
        while(!canMove[stage.camera.x+SCREEN_WIDTH/2-player.player.w/2-LEFT][stage.camera.y+SCREEN_HEIGHT/2-player.player.h/2-add-UP]) add--;

        stage.camera.y -= add;
        stage.background.y = -stage.camera.y;
        stage.portal.y += add;
        for(int i = 0; i < dinos.size(); i++){
            dinos[i].deltaY += add;
            dinos[i].rect.y += add;
            dinos[i].bullet.deltaY += add;
        }
        for(int i = 0; i < bullets.size(); i++) {
            bullets[i].bullet.y += add;
        }
        for(int i = 0; i < firews.size(); i++) {
            firews[i].deltaY += add;
            firews[i].rect.y += add;
        }
        
    }
    if (event.aDown) {
        int add = 5;
        player.imgRect.x = 114;
        player.imgRect.y = 17;

        while(stage.camera.x+SCREEN_WIDTH/2-player.player.w/2-add < LEFT) add--;
        while(!canMove[stage.camera.x+SCREEN_WIDTH/2-player.player.w/2-add-LEFT][stage.camera.y+SCREEN_HEIGHT/2+player.player.h/2-UP])add--;
        while(!canMove[stage.camera.x+SCREEN_WIDTH/2-player.player.w/2-add-LEFT][stage.camera.y+SCREEN_HEIGHT/2-player.player.h/2-UP])add--;
        stage.camera.x -= add;
        stage.background.x = -stage.camera.x;
        stage.portal.x += add;
        for(int i = 0; i < dinos.size(); i++){
            dinos[i].rect.x += add;
            dinos[i].deltaX += add;
            dinos[i].bullet.deltaX += add;
        }
        for(int i = 0; i < bullets.size(); i++) {
            bullets[i].bullet.x += add;
        }
        for(int i = 0; i < firews.size(); i++) {
            firews[i].deltaX += add;
            firews[i].rect.x += add;
        }
    }
    if (event.sDown) {
        int add = 5;
        player.imgRect.x = 18;
        player.imgRect.y = 17;

        while(stage.camera.y+SCREEN_HEIGHT/2+player.player.h/2+add > DOWN) add--;
        while(!canMove[stage.camera.x+SCREEN_WIDTH/2+player.player.w/2-LEFT][stage.camera.y+SCREEN_HEIGHT/2+player.player.h/2+add-UP]) add--;
        while(!canMove[stage.camera.x+SCREEN_WIDTH/2-player.player.w/2-LEFT][stage.camera.y+SCREEN_HEIGHT/2+player.player.h/2+add-UP]) add--;

        stage.camera.y += add;
        stage.background.y = -stage.camera.y;
        stage.portal.y -= add;
        for(int i = 0; i < dinos.size(); i++){
            dinos[i].rect.y -= add;
            dinos[i].deltaY -= add;
            dinos[i].bullet.deltaY -= add;
        }
        for(int i = 0; i < bullets.size(); i++) {
            bullets[i].bullet.y -= add;
        }
        for(int i = 0; i < firews.size(); i++) {
            firews[i].deltaY -= add;
            firews[i].rect.y -= add;
        }
        
    }
    if (event.dDown) {
        int add = 5;
        player.imgRect.x = 162;
        player.imgRect.y = 17;

        while(stage.camera.x+SCREEN_WIDTH/2+player.player.w/2+add > RIGHT) add--;
        while(!canMove[stage.camera.x+SCREEN_WIDTH/2+player.player.w/2+add-LEFT][stage.camera.y+SCREEN_HEIGHT/2-UP]) add--;
        stage.camera.x += add;
        stage.background.x = -stage.camera.x;
        stage.portal.x -= add;
    
        for(int i = 0; i < dinos.size(); i++){
            dinos[i].rect.x -= add;
            dinos[i].deltaX -= add;
            dinos[i].bullet.deltaX -= add;
        }

        for(int i = 0; i < bullets.size(); i++) {
            bullets[i].bullet.x -= add;
        }
        for(int i = 0; i < firews.size(); i++) {
            firews[i].deltaX -= add;
            firews[i].rect.x -= add;
        }
    }

}