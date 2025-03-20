void RenderHitbox(SDL_Renderer *renderer, SDL_Rect rect) {
    SDL_SetRenderDrawColor(renderer, 255, 105, 180, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &rect);
}

void RenderBackground1(SDL_Renderer *renderer, Stage &stage) {
    SDL_RenderCopy(renderer, stage.backgroundImg, NULL, &stage.background);
    // SDL_DestroyTexture(backgroundImg);

    SDL_RenderCopy(renderer, stage.borderTextureTop, NULL, &stage.topBorder);
    SDL_RenderCopy(renderer, stage.borderTextureBottom, NULL, &stage.bottomBorder);
    SDL_RenderCopy(renderer, stage.borderTextureLeft, NULL, &stage.leftBorder);
    SDL_RenderCopy(renderer, stage.borderTextureRight, NULL, &stage.rightBorder);
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
    // player.playerHPRect.x = player.player.x;
    // player.playerHPRect.y = player.player.y-25;
    // player.playerHPRect.w = float(player.playerHP)/100 * player.playerW*1.5;

    // SDL_Rect temp = {player.player.x, player.player.y-25, player.playerW*15/10, 10};
    // SDL_SetRenderDrawColor(renderer, 200, 200, 200, SDL_ALPHA_OPAQUE);
    // SDL_RenderFillRect(renderer, &temp);
    // SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
    // SDL_RenderFillRect(renderer, &player.playerHPRect);
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

    // dino.dinoHPRect.x = dino.dino.x;
    // dino.dinoHPRect.y = dino.dino.y-25;
    // dino.dinoHPRect.w = float(dino.dinoHP)/100 * dino.dinoW*2;
    
    // SDL_Rect temp = {dino.dino.x, dino.dino.y-25, dino.dinoW*2, 10};
    // SDL_SetRenderDrawColor(renderer, 150, 150, 150, SDL_ALPHA_OPAQUE);
    // SDL_RenderFillRect(renderer, &temp);
    // SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    // SDL_RenderFillRect(renderer, &dino.dinoHPRect);

    SDL_RenderCopy(renderer, dino.dinoImg, NULL, &dino.dino);
}




void RenderHome(Event &event, SDL_Renderer *renderer, Stage &stage) {
    // event.CheckEvent();
    stage.SetHome(renderer);
    
    while(event.appIsRunning) {
        if(event.curStage != 0) break;
        event.checkHome();

        if(event.mouseButtonLeftDown && event.playDown) {
            event.mouseButtonLeftDown = false;
            event.curStage++;
        }

        SDL_RenderCopy(renderer, stage.homeImg, NULL, NULL);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
}



bool checkDinoDead(vector<Dino> dino) {
    for(int i = 0; i < dino.size(); i++){
        if(dino[i].dinoHP > 0) return false;
    }

    return true;
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
    
    int x = 0;
    int y = 0;

    for(int i = 0; i < num; i++){
        Dino temp;
        file >> x >> y;
        
        temp.SetDino(renderer, x, y);
        // temp.Fire();
        temp.bullet.SetRect(renderer, temp);
        dino.push_back(temp);
    
    }

    


    file.close();



    stage.SetPortal(renderer);


    while(event.appIsRunning) {
        event.CheckEvent();

        SDL_ShowCursor(SDL_DISABLE);

        

        player.Move(event);

        player.CheckBorderCollision();

        Fire(event, player);
        player.bullet.Move(event);

        // cout << player.bullet.isFiring << endl;
        

        
        


        for(int i = 0; i < num; i++) {
            IsCollision(player, dino[i]);
        }

        

        player.bullet.CheckBorderCollision();
        
        // IsCollision(player, dino);

        

        RenderBackground1(renderer, stage);

        if(checkDinoDead(dino)) {
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
                    break;
                }
            }
        }

        
        
        RenderPlayer(renderer, player);

        // render bullet
        if(player.bullet.isFiring) {
            SDL_RenderCopy(renderer, player.bullet.bulletImg, NULL, &player.bullet.bullet);
        }

        for(int i = 0; i < num; i++) {
            RenderDino(renderer, dino[i]);
        }

        

        RenderCustomDotCursor(renderer);
        


        SDL_RenderPresent(renderer);
        SDL_Delay(16);   
    } 
}




void RenderStage3(Event &event, SDL_Renderer *renderer, Stage &stage, string level) {
    Player player;
    player.Setplayer(renderer);
    player.bullet.SetPlayerBullet(renderer);
    

    stage.SetStage3(renderer);

    string input = "levels/" + level + ".txt";
    ifstream file(input);
    
    int num = 0;
    file >> num;

    int x;
    int y;

    vector<Dino> dino;

    for(int i = 0; i < num; i++){
        Dino temp;
        file >> x >> y;
        // cout << x << ' ' << y << endl;
        
        temp.SetDino(renderer, x, y);
        // temp.Fire();
        temp.bullet.SetRect(renderer, temp);
        dino.push_back(temp);
    }

    int boxSize = 0;
    file >> boxSize;
    vector<SDL_Rect> rectBox(boxSize);
    for(int i = 0; i < boxSize; i++) {
        file >> rectBox[i].x >> rectBox[i].y >> rectBox[i].w >> rectBox[i].h;
    }

    // cout << dino.size();
    file.close();

    stage.SetPortal(renderer);


    while(event.appIsRunning) {
        event.CheckEvent();

        SDL_ShowCursor(SDL_DISABLE);

        

        player.Move(event);

        player.CheckBorderCollision();

        Fire(event, player);
        player.bullet.Move(event);

        // cout << player.bullet.isFiring << endl;
        

        
        


        for(int i = 0; i < num; i++) {
            IsCollision(player, dino[i]);
        }

        

        player.bullet.CheckBorderCollision();

        for(int i = 0; i < boxSize; i++) {
            player.bullet.CheckObjectCollision(rectBox[i]);
        }
        
        // IsCollision(player, dino);

        

        RenderBackground1(renderer, stage);

        if(checkDinoDead(dino)) {
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
                    break;
                }
            }
        }

        
        
        RenderPlayer(renderer, player);

        // render bullet
        if(player.bullet.isFiring) {
            SDL_RenderCopy(renderer, player.bullet.bulletImg, NULL, &player.bullet.bullet);
        }

        for(int i = 0; i < num; i++) {
            RenderDino(renderer, dino[i]);
        }

        for(int i = 0; i < boxSize; i++) {
            // cout << rectBox[i].y;
            SDL_RenderCopy(renderer, stage.box, NULL, &rectBox[i]);
        }

        

        RenderCustomDotCursor(renderer);
        


        SDL_RenderPresent(renderer);
        SDL_Delay(16);   
    } 
}