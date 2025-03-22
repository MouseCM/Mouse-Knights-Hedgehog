

void RenderHitbox(SDL_Renderer *renderer, SDL_Rect rect) {
    SDL_SetRenderDrawColor(renderer, 255, 105, 180, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &rect);
}

void RenderBackground1(SDL_Renderer *renderer, Stage &stage) {
    // SDL_Rect srcRect = {0, 0, 100, 100};
    SDL_RenderCopy(renderer, stage.backgroundImg, NULL, &stage.background);
    // SDL_DestroyTexture(backgroundImg);



    // SDL_RenderCopy(renderer, stage.borderTextureTop, NULL, &stage.topBorder);
    // SDL_RenderCopy(renderer, stage.borderTextureBottom, NULL, &stage.bottomBorder);
    // SDL_RenderCopy(renderer, stage.borderTextureLeft, NULL, &stage.leftBorder);
    // SDL_RenderCopy(renderer, stage.borderTextureRight, NULL, &stage.rightBorder);
    // SDL_DestroyTexture(borderTextureTop);
    // SDL_DestroyTexture(borderTextureBottom);
    // SDL_DestroyTexture(borderTextureLeft);
    // SDL_DestroyTexture(borderTextureRight);
}

void RenderCustomDotCursor(SDL_Renderer* renderer) {
    // Get current mouse position
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    
    // Draw a dot at the mouse position
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White dot
    
    // For a simple dot (3x3 pixels)
    SDL_Rect dotRect = {mouseX - 1, mouseY - 1, 7, 7};
    SDL_RenderFillRect(renderer, &dotRect);
}

void RenderPlayer(SDL_Renderer *renderer, Player &player) {
    player.playerHPRect.x = 30;
    player.playerHPRect.y = 30;
    player.playerHPRect.w = float(player.playerHP)/100 * player.playerW*5;
    player.playerHPRect.h = 20; 

    SDL_Rect temp = {30, 30, player.playerW*5, 20};
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &temp);
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &player.playerHPRect);
    SDL_RenderCopy(renderer, player.playerImg, NULL, &player.player);
}

void RenderDino(SDL_Renderer *renderer, Dino &dino) {
    if (dino.dinoHP <= 0) {
        return;
    }

    // dino.dinoBullet.x += 1;
    // dino.dinoBullet.y += 1;
    // if (dino.isFiring && dino.dinoBulletNum >= 1) {
    //     SDL_RenderCopy(renderer, dino.dinoBulletImg, NULL, &dino.dinoBullet);
    //     // cout << dino.dinoBullet.x << " " << dino.dinoBullet.y << endl;
    // }

    dino.dinoHPRect.x = dino.dino.x;
    dino.dinoHPRect.y = dino.dino.y-25;
    dino.dinoHPRect.w = float(dino.dinoHP)/100 * dino.dinoW*2;
    
    SDL_Rect temp = {dino.dino.x, dino.dino.y-25, dino.dinoW*2, 10};
    SDL_SetRenderDrawColor(renderer, 150, 150, 150, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &temp);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &dino.dinoHPRect);

    SDL_RenderCopy(renderer, dino.dinoImg, NULL, &dino.dino);
}




void RenderHome(Event &event, SDL_Renderer *renderer, Stage &stage) {
    // event.CheckEvent();
    stage.SetHome(renderer);
    
    while(event.appIsRunning) {
        if(event.curStage != 0) break;
        event.checkHome();

        if(event.dDown) {
            stage.home.x -= 10;
        }

        if(event.mouseButtonLeftDown && event.playDown) {
            event.mouseButtonLeftDown = false;
            event.curStage++;
        }

        SDL_RenderCopy(renderer, stage.homeImg, NULL, &stage.home);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
}



bool CheckDinoDead(vector<Dino> dino) {
    for(int i = 0; i < dino.size(); i++){
        if(dino[i].dinoHP > 0) return false;
    }

    return true;
}

void MoveScreen(Event &event, Player &player, Stage &stage, vector<Dino> &dino, vector<Player::Bullet> &bullets) {
    if (event.wDown) {
        stage.background.y += 5;
        if(stage.background.y > 0-player.player.h) {
            stage.background.y = 0-player.player.h;
        }
        else {
            stage.portal.y += 5;
            // stage.background.y = min(stage.background.y+5, 0-player.player.h);
            // player.player.y = player.player.y+5;
            for(int i = 0; i < dino.size(); i++){
                dino[i].dino.y += 5;
            }
            for(int i = 0; i < bullets.size(); i++) {
                bullets[i].bullet.y += 5;
            }
        }
        // stage.retry.y += 5;
        
    }
    if (event.aDown) {
        stage.background.x += 5;
        if(stage.background.x > -26-player.player.w/2) {
            stage.background.x = -26-player.player.w/2;
        }
        else {
            stage.portal.x += 5;
            // stage.background.x = min(stage.background.x+5, -26-player.player.w/2);
            // player.player.x = player.player.x+5;
            for(int i = 0; i < dino.size(); i++){
                dino[i].dino.x += 5;
            }
            for(int i = 0; i < bullets.size(); i++) {
                bullets[i].bullet.x += 5;
            }
        }
        // stage.retry.x += 5;
        
    }
    if (event.sDown) {
        stage.background.y -= 5;
        if(stage.background.y < -720+player.player.h) {
            stage.background.y = -720+player.player.h;
        }
        else {
            stage.portal.y -= 5;
            // stage.background.y = max(stage.background.y-5, -720+player.player.h);
            // player.player.y = player.player.y-5;
            for(int i = 0; i < dino.size(); i++){
                dino[i].dino.y -= 5;
            }
            for(int i = 0; i < bullets.size(); i++) {
                bullets[i].bullet.y -= 5;
            }
        }
        // stage.retry.y -= 5;
        
    }
    if (event.dDown) {
        // stage.background.x = max(stage.background.x-5, -1252+player.player.w/2);
        stage.background.x -= 5;
        if(stage.background.x < -1252+player.player.w/2) {
            stage.background.x = -1252+player.player.w/2;
        }
        else {
            stage.portal.x -= 5;
        
            for(int i = 0; i < dino.size(); i++){
                dino[i].dino.x -= 5;
            }

            for(int i = 0; i < bullets.size(); i++) {
                bullets[i].bullet.x -= 5;
            }
        }
        // player.player.x = player.player.x - 5;
        // stage.retry.x -= 5;
        
    }
}



void RenderStage(Event &event, SDL_Renderer *renderer, Stage &stage, string level) {
    Player player;
    player.Setplayer(renderer);
    player.bullet.SetPlayerBullet(renderer);
    
    

    stage.SetStage(renderer);

    string input = "levels/" + level + ".txt";
    ifstream file(input);
    
    int num = 0;
    file >> num;

    vector<Dino> dino;
    vector<Player::Bullet> bullets;

    
    int x = 0;
    int y = 0;

    for(int i = 0; i < num; i++){
        Dino temp;
        file >> x >> y;
        
        temp.SetDino(renderer, x-INIT_X, y-INIT_Y);
        // temp.Fire();
        temp.bullet.SetRect(renderer, temp);
        dino.push_back(temp);
    
    }

    


    file.close();



    stage.SetPortal(renderer);


    while(event.appIsRunning) {

        event.CheckEvent();
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

        SDL_ShowCursor(SDL_DISABLE);

        
        // player.Move(event);
        
        
        
        MoveScreen(event, player, stage, dino, bullets);
        

        // player.CheckBorderCollision();

        

        
        // player.bullet.Move(event);

        // cout << player.bullet.isFiring << endl;
        

        
        


        for(int i = 0; i < dino.size(); i++) {
            for(int j = 0; j < bullets.size(); j++) {
                IsCollision(bullets[j], dino[i]);
            }
        }

        

        // player.bullet.CheckBorderCollision();
        
        // IsCollision(player, dino);

        // render after this

        RenderBackground1(renderer, stage);

        if(CheckDinoDead(dino)) {
            // cout << "viectory";
            SDL_RenderCopy(renderer, stage.portalIMG, NULL, &stage.portal);
            if(Collision(player.player, stage.portal)) {
                event.curStage++;
                break;
            }
        }
        else {
            if(player.bullet.isLose) {
                event.CheckRetry();
                SDL_RenderCopy(renderer, stage.retryImg, NULL, &stage.retry);
                if(event.isRetry) {
                    event.isRetry = false;
                    event.mouseButtonLeftDown = false;
                    RenderStage(event, renderer, stage, to_string(event.curStage));
                    break;
                }
            }
        }

        
        Fire(renderer, event, player, bullets);
        for(int i = 0; i < bullets.size(); i++) {
            if(bullets[i].isFiring) {
                bullets[i].Move(event);
                CheckBorderCollision(bullets[i], stage);
                SDL_RenderCopy(renderer, player.bullet.bulletImg, NULL, &bullets[i].bullet);
            }
        }
        
        RenderPlayer(renderer, player);


        // render bullet
        // if(player.bullet.isFiring) {
        //     SDL_RenderCopy(renderer, player.bullet.bulletImg, NULL, &player.bullet.bullet);
        // }

        for(int i = 0; i < num; i++) {
            RenderDino(renderer, dino[i]);
        }

        

        RenderCustomDotCursor(renderer);
        

        
        SDL_RenderPresent(renderer);
        SDL_Delay(16);   
    } 
}



