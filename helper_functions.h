using namespace std;

// setup window
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

void InitStage(string &input, SDL_Renderer *renderer, Stage &stage, vector<Dino> &dinos, vector<Firew> &firews, vector<Hedgehog::Gun> &guns, Hedgehog &hedgehog, vector<SDL_Rect> &boxes, vector<vector<bool>> &canMove, vector<Hedgehog::Bullet> &hedgehogBullets, int &num) {
    ifstream file(input);
    file >> num;

    
    int x = 0;
    int y = 0;

    // init dinos
    for(int i = 0; i < num; i++){
        Dino temp;
        file >> x >> y;
        
        temp.SetRect(renderer, x-INIT_X, y-INIT_Y);
        // temp.Fire();
        temp.bullet.SetRect(renderer);
        dinos.push_back(temp);
    }

    
    // init boxes
    file >> num;
    for(int i = 0; i < num; i++) {
        SDL_Rect temp;
        file >> temp.x >> temp.y >> temp.w >> temp.h;
        boxes.push_back(temp);
    }

    // init map for player moving
    for(int t = 0; t < boxes.size(); t++) {
        for(int i = boxes[t].x; i <= boxes[t].x+boxes[t].w; i++) {
            for(int j = boxes[t].y; j <= boxes[t].y+boxes[t].h; j++) {
                canMove[i-LEFT][j-UP] = false;
            }
        }
    }

    // init firew
    file >> num;
    for(int i = 0; i < num; i++) {
        file >> x >> y;
        Firew temp;
        temp.SetRect(renderer, x-INIT_X, y-INIT_Y);
        firews.push_back(temp);
    }


    // boss stage
    file >> num;
    if(num == 1) {
        hedgehog.SetRect(renderer ,SCREEN_WIDTH/2, SCREEN_HEIGHT/2-300);
        for(int i = 0; i < firews.size(); i++) {
            firews[i].hp = -1;
        }
        hedgehog.bullet.SetRect(renderer);
    }
    else {
        hedgehog.hp = 0;
    }

    
    for(int i = 0; i < hedgehogBullets.size(); i++) {
        hedgehogBullets[i].SetRect(renderer);
    }

    
    
    for(int i = 0; i < guns.size(); i++) {
        guns[i].SetRect(renderer, 0, 0);
        guns[i].bullet.SetRect(renderer);
    }
    guns[0].SetRect(renderer, LEFT-INIT_X, UP-INIT_Y);
    guns[1].SetRect(renderer, LEFT-INIT_X, DOWN-INIT_Y-guns[1].rect.h);
    guns[2].SetRect(renderer, RIGHT-INIT_X-guns[2].rect.w, UP-INIT_Y);
    guns[3].SetRect(renderer, RIGHT-INIT_X-guns[3].rect.w, DOWN-INIT_Y-guns[2].rect.h);

    file.close();
}

// player fire bullet function
void Fire(SDL_Renderer *renderer, Event &event, Audio &audio, Player &player, vector<Player::Bullet> &bullets) {
    if(event.isLose) return;
    if (event.mouseButtonLeftDown) {
        if(SDL_GetTicks64() >= player.bullet.reloadTime && player.playerHP > 0) {
            audio.PlayerFire();
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


// dino fire bullet function
void DinoFire(Event event, SDL_Renderer *renderer, Audio &audio, Dino &dino, Player &player) {
    if(event.isLose) return;
    if(SDL_GetTicks64() >= dino.bullet.reloadTime && dino.hp > 0) {
        audio.DinoFire();

        dino.bullet.deltaX = player.player.x+player.player.w/2 - (dino.rect.x + dino.rect.w/2);
        dino.bullet.deltaY = player.player.y+player.player.h/2 - (dino.rect.y + dino.rect.h/2);
        dino.bullet.angle = atan2(dino.bullet.deltaY, dino.bullet.deltaX);
        dino.bullet.deltaX = dino.rect.x + dino.rect.w/2 - dino.bullet.rect.w/2;
        dino.bullet.deltaY = dino.rect.y + dino.rect.h/2 - dino.bullet.rect.h/2;
        dino.bullet.isFiring = true;
        dino.bullet.reloadTime = SDL_GetTicks64() + 3000;
    }
}



// setup bullet for hedgehog
void HedgehogFire(Event event, SDL_Renderer *renderer, Audio &audio, Hedgehog &hedgehog, Hedgehog::Bullet &bullet, Player &player) {
    if(event.isLose) return;

    audio.HedgehogFire();

    bullet.deltaX = player.player.x+player.player.w/2 - (hedgehog.rect.x + hedgehog.rect.w/2);
    bullet.deltaY = player.player.y+player.player.h/2 - (hedgehog.rect.y + hedgehog.rect.h/2);
    bullet.angle = atan2(bullet.deltaY, bullet.deltaX);
    bullet.deltaX = hedgehog.rect.x + hedgehog.rect.w/2 - hedgehog.bullet.rect.w/2;
    bullet.deltaY = hedgehog.rect.y + hedgehog.rect.h/2 - hedgehog.bullet.rect.h/2;
    bullet.rect.x = hedgehog.rect.x + hedgehog.rect.w/2 - hedgehog.bullet.rect.w/2;
    bullet.rect.y = hedgehog.rect.y + hedgehog.rect.h/2 - hedgehog.bullet.rect.h/2;
    bullet.isFiring = true;
}


// gun of hedgehog fire each 5 second
void GunFire(Event event, SDL_Renderer *renderer, Audio &audio, Hedgehog::Gun &gun, Player &player) {
    if(event.isLose) return;
    if(SDL_GetTicks64() >= gun.bullet.reloadTime) {
        audio.DinoFire();

        gun.bullet.deltaX = player.player.x+player.player.w/2 - (gun.rect.x + gun.rect.w/2);
        gun.bullet.deltaY = player.player.y+player.player.h/2 - (gun.rect.y + gun.rect.h/2);
        gun.bullet.angle = atan2(gun.bullet.deltaY, gun.bullet.deltaX);
        gun.bullet.deltaX = gun.rect.x + gun.rect.w/2 - gun.bullet.rect.w/2;
        gun.bullet.deltaY = gun.rect.y + gun.rect.h/2 - gun.bullet.rect.h/2;
        gun.bullet.isFiring = true;
        gun.bullet.reloadTime = SDL_GetTicks64() + 5000;
    }
}


// check collision of 2 rect
bool Collision(SDL_Rect &rect1, SDL_Rect &rect2) {
    // if(event.isLose) return false;
    if (rect1.x + rect1.w >= rect2.x && rect1.x <= rect2.x + rect2.w) {
        if (rect1.y + rect1.h >= rect2.y && rect1.y <= rect2.y + rect2.h) {
            return true;
        }
    }

    return false;
}


// check if player bullet is collison with border or boxes
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



// check if dino bullet is collision with border or boxes
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



// check if hedgehog bullet is collision with border
void CheckBorderCollision(Event event, Hedgehog::Bullet &bullet, Stage &stage) {
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
}



// check if hedgehog gun bullet is collision with border
void CheckBorderCollision(Event event, Hedgehog::Gun::Bullet &bullet, Stage &stage) {
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
}



// check player bullet hit dino to reduce dino hp
void CheckCollision(Event event, Player::Bullet &bullet, Dino &dino) {
    if(event.isLose) return;
    if (dino.hp <= 0) {
        return;
    }

    if (bullet.isFiring) {
        if(Collision(bullet.bullet, dino.rect)) {
            dino.hp -= bullet.damage;
            bullet.isFiring = false;
            dino.hurtTime = SDL_GetTicks64();
        }
    } 
}



// check player bullet hit firew to reduce firew hp
void CheckCollision(Event event, Player::Bullet &bullet, Firew &firew) {
    if(event.isLose) return;
    if (firew.hp <= 0) {
        return;
    }

    if (bullet.isFiring) {
        if(Collision(bullet.bullet, firew.rect)) {
            firew.hp -= bullet.damage;
            bullet.isFiring = false;
            firew.hurtTime = SDL_GetTicks64();
            if(firew.hp == 0) {
                firew.hp -= 1;
                // firew.boomTime = SDL_GetTicks64();
            }
        }
    } 
}



// check if firew to collise with player to boom reduce player hp
void CheckCollision(Event event, Firew &firew, Player &player) {
    if(event.isLose) return;
    if(player.playerHP <= 0) {
        return;
    }
    if(firew.hp <= 0) return;

    if(Collision(firew.rect, player.player)) {
        player.playerHP = max(0, player.playerHP-firew.damage);
        player.hurtTime = SDL_GetTicks64();
        firew.hp = 0;
        firew.boomTime = SDL_GetTicks64();
    }
}


// check if player bullet hit hedgehog to reduce hedgehog hp
void CheckCollision(Event event, Player::Bullet &bullet, Hedgehog &hedgehog, vector<Hedgehog::Gun> &guns) {
    if(event.isLose) return;
    if (hedgehog.hp <= 0) {
        return;
    }

    if (bullet.isFiring) {
        if(Collision(bullet.bullet, hedgehog.rect)) {
            hedgehog.hp -= bullet.damage;
            bullet.isFiring = false;
            hedgehog.hurtTime = SDL_GetTicks64();
            for(int i = 0; i < guns.size(); i++) {
                guns[i].hurtTime = SDL_GetTicks64();
            }
        }
    } 
}


// check dino bullet hit player to reduce player hp
void CheckCollision(Event event, Dino::Bullet &bullet, Player &player) {
    if(event.isLose) return;
    if(player.playerHP <= 0) {
        return;
    }

    if(bullet.isFiring) {
        if(Collision(bullet.rect, player.player)) {
            player.playerHP -= bullet.damage;
            player.hurtTime = SDL_GetTicks64();
            bullet.isFiring = false;
        }
    }
}


// check hedgehog bullet hit player to reduce player hp
void CheckCollision(Event event, Hedgehog::Bullet &bullet, Player &player) {
    if(event.isLose) return;
    if(player.playerHP <= 0) {
        return;
    }

    if(bullet.isFiring) {
        if(Collision(bullet.rect, player.player)) {
            player.playerHP -= bullet.damage;
            player.hurtTime = SDL_GetTicks64();
            bullet.isFiring = false;
        }
    }
}


// check gun bullet hit player to reduce player hp
void CheckCollision(Event event, Hedgehog::Gun::Bullet &bullet, Player &player) {
    if(event.isLose) return;
    if(player.playerHP <= 0) {
        return;
    }

    if(bullet.isFiring) {
        if(Collision(bullet.rect, player.player)) {
            player.playerHP -= bullet.damage;
            player.hurtTime = SDL_GetTicks64();
            bullet.isFiring = false;
        }
    }
}


// check player bullet hit gun of hedgehog to reduce hedgehog hp
void CheckCollision(Event event, Player::Bullet &bullet, Hedgehog::Gun &gun, vector<Hedgehog::Gun> &guns, Hedgehog &hedgehog) {
    if(event.isLose) return;
    if (hedgehog.hp <= 0) {
        return;
    }

    if (bullet.isFiring) {
        if(Collision(bullet.bullet, gun.rect)) {
            hedgehog.hp -= bullet.damage;
            bullet.isFiring = false;
            hedgehog.hurtTime = SDL_GetTicks64();
            for(int i = 0; i < guns.size(); i++) {
                guns[i].hurtTime = SDL_GetTicks64();
            }
        }
    } 
}


// hedgehog spawn firew
void SpawnFirew(Hedgehog &hedgehog, vector<Firew> &firews, Stage &stage, SDL_Renderer *renderer) {
    for(int i = 0; i < firews.size(); i++) {
        if(firews[i].hp > 0) return;
    }

    if(SDL_GetTicks64() >= hedgehog.spawnTime-1000) {
        if(hedgehog.isSpawned == false) {
            for(int i = 0; i < firews.size(); i++) {
                firews[i].rect.x = (rand() % (RIGHT-LEFT-firews[i].rect.w)) + stage.background.x + LEFT;
                firews[i].rect.y = (rand() % (DOWN-UP-firews[i].rect.h)) + stage.background.y + UP;
                firews[i].deltaX = firews[i].rect.x;
                firews[i].deltaY = firews[i].rect.y;
            }
            hedgehog.isSpawned = true;
        }
        
        for(int i = 0; i < firews.size(); i++) {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 128); // Semi-transparent red
            SDL_RenderFillRect(renderer, &firews[i].rect);
        }
    }
    if(SDL_GetTicks64() >= hedgehog.spawnTime) {
        for(int i = 0; i < firews.size(); i++) {
            firews[i].hp = 100;
        }

        hedgehog.isSpawned = false;
        hedgehog.spawnTime = SDL_GetTicks64()+40000;
    }
}


// make dino fire a bullet and moving and border checking dino bullet and hit player check
void DinosBullet(Event event, SDL_Renderer *renderer, Audio &audio, Stage &stage, vector<Dino> &dinos, Player &player, vector<SDL_Rect> &boxes) {
    for(int i = 0; i < dinos.size(); i++) {
        DinoFire(event, renderer, audio, dinos[i], player);
        if(dinos[i].bullet.isFiring) {
            dinos[i].bullet.Move(event);
            CheckBorderCollision(event, dinos[i].bullet, stage, boxes);
            if(dinos[i].bullet.isFiring) {
                SDL_RenderCopy(renderer, dinos[i].bullet.rectImg, NULL, &dinos[i].bullet.rect);
            }

            CheckCollision(event, dinos[i].bullet, player);
        }
    }
}

// player firing bullet
void PlayerBullet(Event event, SDL_Renderer *renderer, Audio &audio, Stage &stage, vector<Player::Bullet> &bullets, Player &player, vector<SDL_Rect> &boxes, vector<Dino> &dinos, vector<Firew> &firews) {
    Fire(renderer, event, audio, player, bullets);
    for(int i = 0; i < bullets.size(); i++) {
        if(bullets[i].isFiring) {
            bullets[i].Move(event);
            CheckBorderCollision(event, bullets[i], stage, boxes);
            if(bullets[i].isFiring) {
                SDL_RenderCopy(renderer, player.bullet.bulletImg, NULL, &bullets[i].bullet);
            }

            // check hit dinos
            for(int j = 0; j < dinos.size(); j++) {
                CheckCollision(event, bullets[i], dinos[j]);
            }

            // check hit firews
            for(int j = 0; j < firews.size(); j++) {
                CheckCollision(event, bullets[i], firews[j]);
            }
        }
    }
}

// check firews close to player to boom
void FirewsBoom(Event &event, vector<Firew> &firews, Player &player) {
    for(int i = 0; i < firews.size(); i++) {
        CheckCollision(event, firews[i], player);
    }
}

// dino moving, also check border and boxes collision
void DinosMove(Event event, vector<Dino> &dinos, Stage stage, Player player, vector<SDL_Rect> boxes) {
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


// firew moving, also check border and boxed collision
void FirewsMove(Event event, vector<Firew> &firews, Stage stage, Player player, vector<SDL_Rect> boxes) {
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




// check is all bot is dead to end stage
bool CheckEnemiesDead(vector<Dino> dinos, vector<Firew> firews, Hedgehog hedgehog) {
    // if(event.isLose) return;
    for(int i = 0; i < dinos.size(); i++) {
        if(dinos[i].hp > 0) return false;
    }

    for(int i = 0; i < firews.size(); i++) {
        if(firews[i].hp > 0) return false;
    }

    if(hedgehog.hp > 0) return false;

    return true;
}



// move everything with player
void MoveCamera(SDL_Renderer *renderer, Event &event, Audio &audio, Player &player, Stage &stage, vector<Dino> &dinos, vector<Player::Bullet> &bullets, vector<vector<bool>> &canMove, vector<SDL_Rect> &boxes, vector<Firew> &firews, Hedgehog &hedgehog, vector<Hedgehog::Bullet> &hedgehogBullets, vector<Hedgehog::Gun> &guns, int &num) {
    if(event.isLose) {
        audio.EndRun();
        return;
    }
    bool isMoved = false;

    if (event.wDown) {
        isMoved = true;

        int add = 5;
        player.imgRect.x = 17;
        player.imgRect.y = 65;

        while(stage.camera.y+SCREEN_HEIGHT/2-player.player.h/2-add < UP) add--;
        while(!canMove[stage.camera.x+SCREEN_WIDTH/2+player.player.w/2-LEFT][stage.camera.y+SCREEN_HEIGHT/2-player.player.h/2-add-UP]) add--;
        while(!canMove[stage.camera.x+SCREEN_WIDTH/2-player.player.w/2-LEFT][stage.camera.y+SCREEN_HEIGHT/2-player.player.h/2-add-UP]) add--;
        
        if(add > 0) {
            if(!audio.CheckPlayingChannel1()) {
                audio.Run();
            }
        }
        stage.camera.y -= add;
        stage.background.y = -stage.camera.y;
        stage.portal.y += add;
        for(int i = 0; i < dinos.size(); i++){
            dinos[i].deltaY += add;
            dinos[i].rect.y += add;
            dinos[i].bullet.deltaY += add;
        }
        for(int i = 0; i < bullets.size(); i++) {
            bullets[i].deltaY += add;
            bullets[i].bullet.y += add;
        }
        for(int i = 0; i < firews.size(); i++) {
            firews[i].deltaY += add;
            firews[i].rect.y += add;
        }

        if(num) {
            hedgehog.rect.y += add;
            for(int i = 0; i < hedgehogBullets.size(); i++) {
                hedgehogBullets[i].deltaY += add;
                hedgehogBullets[i].rect.y += add;
            }

            for(int i = 0; i < guns.size(); i++) {
                guns[i].rect.y += add;
                guns[i].bullet.deltaY += add;
                guns[i].bullet.rect.y += add;
            }
        }
        
    }

    if (event.aDown) {
        isMoved = true;

        int add = 5;
        player.imgRect.x = 113;
        player.imgRect.y = 17;

        while(stage.camera.x+SCREEN_WIDTH/2-player.player.w/2-add < LEFT) add--;
        while(!canMove[stage.camera.x+SCREEN_WIDTH/2-player.player.w/2-add-LEFT][stage.camera.y+SCREEN_HEIGHT/2+player.player.h/2-UP])add--;
        while(!canMove[stage.camera.x+SCREEN_WIDTH/2-player.player.w/2-add-LEFT][stage.camera.y+SCREEN_HEIGHT/2-player.player.h/2-UP])add--;

        if(add > 0) {
            if(!audio.CheckPlayingChannel1()) {
                audio.Run();
            }
        } 
        stage.camera.x -= add;
        stage.background.x = -stage.camera.x;
        stage.portal.x += add;
        for(int i = 0; i < dinos.size(); i++){
            dinos[i].rect.x += add;
            dinos[i].deltaX += add;
            dinos[i].bullet.deltaX += add;
        }
        for(int i = 0; i < bullets.size(); i++) {
            bullets[i].deltaX += add;
            bullets[i].bullet.x += add;
        }
        for(int i = 0; i < firews.size(); i++) {
            firews[i].deltaX += add;
            firews[i].rect.x += add;
        }

        if(num) {
            hedgehog.rect.x += add;
            for(int i = 0; i < hedgehogBullets.size(); i++) {
                hedgehogBullets[i].deltaX += add;
                hedgehogBullets[i].rect.x += add;
            }
            for(int i = 0; i < guns.size(); i++) {
                guns[i].rect.x += add;
                guns[i].bullet.deltaX += add;
                guns[i].bullet.rect.x += add;
            }
        }
    }
    if (event.sDown) {
        isMoved = true;

        int add = 5;
        player.imgRect.x = 17;
        player.imgRect.y = 17;

        while(stage.camera.y+SCREEN_HEIGHT/2+player.player.h/2+add > DOWN) add--;
        while(!canMove[stage.camera.x+SCREEN_WIDTH/2+player.player.w/2-LEFT][stage.camera.y+SCREEN_HEIGHT/2+player.player.h/2+add-UP]) add--;
        while(!canMove[stage.camera.x+SCREEN_WIDTH/2-player.player.w/2-LEFT][stage.camera.y+SCREEN_HEIGHT/2+player.player.h/2+add-UP]) add--;

        if(add > 0) {
            if(!audio.CheckPlayingChannel1()) {
                audio.Run();
            }
        }
        stage.camera.y += add;
        stage.background.y = -stage.camera.y;
        stage.portal.y -= add;
        for(int i = 0; i < dinos.size(); i++){
            dinos[i].rect.y -= add;
            dinos[i].deltaY -= add;
            dinos[i].bullet.deltaY -= add;
        }
        for(int i = 0; i < bullets.size(); i++) {
            bullets[i].deltaY -= add;
            bullets[i].bullet.x -= add;
        }
        for(int i = 0; i < firews.size(); i++) {
            firews[i].deltaY -= add;
            firews[i].rect.y -= add;
        }

        if(num) {
            hedgehog.rect.y -= add;
            for(int i = 0; i < hedgehogBullets.size(); i++) {
                hedgehogBullets[i].deltaY -= add;
                hedgehogBullets[i].rect.y -= add;
            }
            for(int i = 0; i < guns.size(); i++) {
                guns[i].rect.y -= add;
                guns[i].bullet.deltaY -= add;
                guns[i].bullet.rect.y -= add;
            }
        }
        
    }
    if (event.dDown) {
        isMoved = true;

        int add = 5;
        player.imgRect.x = 161;
        player.imgRect.y = 17;

        while(stage.camera.x+SCREEN_WIDTH/2+player.player.w/2+add > RIGHT) add--;
        while(!canMove[stage.camera.x+SCREEN_WIDTH/2+player.player.w/2+add-LEFT][stage.camera.y+player.player.h/2+SCREEN_HEIGHT/2-UP]) add--;
        while(!canMove[stage.camera.x+SCREEN_WIDTH/2+player.player.w/2+add-LEFT][stage.camera.y-player.player.h/2+SCREEN_HEIGHT/2-UP]) add--;
        
        if(add > 0) {
            if(!audio.CheckPlayingChannel1()) {
                audio.Run();
            }
        }
        stage.camera.x += add;
        stage.background.x = -stage.camera.x;
        stage.portal.x -= add;
    
        for(int i = 0; i < dinos.size(); i++){
            dinos[i].rect.x -= add;
            dinos[i].deltaX -= add;
            dinos[i].bullet.deltaX -= add;
        }

        for(int i = 0; i < bullets.size(); i++) {
            bullets[i].deltaX -= add;
            bullets[i].bullet.x -= add;
        }
        for(int i = 0; i < firews.size(); i++) {
            firews[i].deltaX -= add;
            firews[i].rect.x -= add;
        }

        if(num) {
            hedgehog.rect.x -= add;
            for(int i = 0; i < hedgehogBullets.size(); i++) {
                hedgehogBullets[i].deltaX -= add;
                hedgehogBullets[i].rect.x -= add;
            }
            for(int i = 0; i < guns.size(); i++) {
                guns[i].rect.x -= add;
                guns[i].bullet.deltaX -= add;
                guns[i].bullet.rect.x -= add;
            }
        }
    }

    if(!isMoved) {
        audio.EndRun();
    }
}