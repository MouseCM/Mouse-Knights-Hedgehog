

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




void RenderStage(Event &event, SDL_Renderer *renderer, Stage &stage, string level) {
    Player player;
    player.Setplayer(renderer);
    player.bullet.SetPlayerBullet(renderer);
    
    vector<vector<bool>> canMove(RIGHT-LEFT+1, vector<bool>(DOWN-UP+1, 1));

    
 
    

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

    vector<SDL_Rect> box;
    file >> num;
    // cout << num << endl;
    for(int i = 0; i < num; i++) {
        SDL_Rect temp;
        file >> temp.x >> temp.y >> temp.w >> temp.h;
        box.push_back(temp);
    }

    for(int t = 0; t < box.size(); t++) {
        for(int i = box[t].x; i <= box[t].x+box[t].w; i++) {
            for(int j = box[t].y; j <= box[t].y+box[t].h; j++) {
                canMove[i-LEFT][j-UP] = false;
            }
        }
    }


    file.close();



    stage.SetPortal(renderer);
    // cout << player.player.w << ' ' << player.player.h << endl;

    while(event.appIsRunning) {

        event.CheckEvent();
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

        SDL_ShowCursor(SDL_DISABLE);

        
        // player.Move(event);
        
        
        
        MoveCamera(event, player, stage, dino, bullets, canMove);
        // cout << stage.camera.x+SCREEN_WIDTH/2-LEFT << ' ' << stage.camera.y+SCREEN_HEIGHT/2-UP << endl;

        // player.CheckBorderCollision();

        

        
        // player.bullet.Move(event);

        // cout << player.bullet.isFiring << endl;
        

        
        


        

        

        // player.bullet.CheckBorderCollision();
        
        // IsCollision(player, dino);

        // render after this

        RenderBackground1(renderer, stage);


        Fire(renderer, event, player, bullets);
        for(int i = 0; i < bullets.size(); i++) {
            if(bullets[i].isFiring) {
                bullets[i].Move(event);
                CheckBorderCollision(bullets[i], stage, box);
                if(bullets[i].isFiring) {
                    SDL_RenderCopy(renderer, player.bullet.bulletImg, NULL, &bullets[i].bullet);
                }
            }
        }

        for(int i = 0; i < dino.size(); i++) {
            for(int j = 0; j < bullets.size(); j++) {
                IsCollision(bullets[j], dino[i]);
            }
        }

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

        
        
        
        


        // render bullet
        // if(player.bullet.isFiring) {
        //     SDL_RenderCopy(renderer, player.bullet.bulletImg, NULL, &player.bullet.bullet);
        // }

        for(int i = 0; i < num; i++) {
            RenderDino(renderer, dino[i]);
        }

        
        RenderPlayer(renderer, player);

        RenderCustomDotCursor(renderer);
        

        
        SDL_RenderPresent(renderer);
        SDL_Delay(16);   
    } 

    bullets.clear();
    canMove.clear();
    box.clear();
}



