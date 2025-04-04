

void RenderHitboxes(SDL_Renderer *renderer, SDL_Rect rect) {
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

void RenderCustomDotCursor(SDL_Renderer* renderer, Player &player) {
    // Get current mouse position
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    
    // Draw a dot at the mouse position
    // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White dot
    
    // For a simple dot (3x3 pixels)
    SDL_Rect dotRect = {mouseX - 20, mouseY - 20, 40, 40};
    // SDL_RenderFillRect(renderer, &dotRect);
    SDL_RenderCopy(renderer, player.dot, NULL, &dotRect);
}

void RenderPlayer(SDL_Renderer *renderer, Player &player) {
    if(player.playerHP <= 0) return; 
    player.playerHPRect.x = 50;
    player.playerHPRect.y = 30;
    player.playerHPRect.w = float(player.playerHP)/100 * 200;
    player.playerHPRect.h = 20; 

    SDL_Rect temp = {50, 30, 200, 20};
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &temp);
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &player.playerHPRect);

    temp = {50, 10, 60, 15};
    SDL_RenderCopy(renderer, player.name, NULL, &temp);
    temp = {5, 20, 40, 40};
    SDL_RenderCopy(renderer, player.hp, NULL, &temp);
    if(SDL_GetTicks64() <= player.hurtTime+200) {
        SDL_RenderCopy(renderer, player.playerImgHurt, &player.imgRect, &player.player);
    }
    else {
        SDL_RenderCopy(renderer, player.playerImg, &player.imgRect, &player.player);
    }
    

}

void RenderDeadPlayer(SDL_Renderer *renderer, Player &player) {
    SDL_RenderCopy(renderer, player.playerImg, &player.imgRect, &player.player);
}

void RenderDino(SDL_Renderer *renderer, Dino &dino) {
    if (dino.hp <= 0) {
        return;
    }

    // dino.dinoBullet.x += 1;
    // dino.dinoBullet.y += 1;
    // if (dino.isFiring && dino.dinoBulletNum >= 1) {
    //     SDL_RenderCopy(renderer, dino.dinoBulletImg, NULL, &dino.dinoBullet);
    //     // cout << dino.dinoBullet.x << " " << dino.dinoBullet.y << endl;
    // }

    dino.hpRect.x = dino.rect.x;
    dino.hpRect.y = dino.rect.y-25;
    dino.hpRect.w = float(dino.hp)/100 * dino.rect.w;
    
    SDL_Rect temp = {dino.rect.x, dino.rect.y-25, dino.rect.h, 10};
    SDL_SetRenderDrawColor(renderer, 150, 150, 150, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &temp);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &dino.hpRect);

    if(SDL_GetTicks64() <= dino.hurtTime+200) {
        SDL_RenderCopy(renderer, dino.rectImgHurt, NULL, &dino.rect);
    }
    else {
        SDL_RenderCopy(renderer, dino.rectImg, NULL, &dino.rect);
    }
    
}

void RenderFirew(SDL_Renderer *renderer, Firew &firew) {
    if (firew.hp <= 0) {
        if(SDL_GetTicks64() <= firew.boomTime+1000) {
            firew.boomRect.x = firew.rect.x;
            firew.boomRect.y = firew.rect.y;
            SDL_RenderCopy(renderer, firew.boomImg, NULL, &firew.boomRect);
        }
        return;
    }

    // dino.dinoBullet.x += 1;
    // dino.dinoBullet.y += 1;
    // if (dino.isFiring && dino.dinoBulletNum >= 1) {
    //     SDL_RenderCopy(renderer, dino.dinoBulletImg, NULL, &dino.dinoBullet);
    //     // cout << dino.dinoBullet.x << " " << dino.dinoBullet.y << endl;
    // }

    firew.hpRect.x = firew.rect.x;
    firew.hpRect.y = firew.rect.y-25;
    firew.hpRect.w = float(firew.hp)/100 * firew.rect.w;
    
    SDL_Rect temp = {firew.rect.x, firew.rect.y-25, firew.rect.h, 10};
    SDL_SetRenderDrawColor(renderer, 150, 150, 150, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &temp);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &firew.hpRect);

    if(SDL_GetTicks64() <= firew.hurtTime+200) {
        SDL_RenderCopy(renderer, firew.rectImgHurt, NULL, &firew.rect);
    }
    else {
        SDL_RenderCopy(renderer, firew.rectImg, NULL, &firew.rect);
    }
    
}


void RenderPortal(SDL_Renderer *renderer, Stage &stage) {
    if(SDL_GetTicks64() >= stage.animationPortalTime + 200) {
        if(stage.animated == 0) {
            stage.animationPortal.x = 15;
            stage.animationPortal.y = 1;
        }
        else if(stage.animated == 1) {
            stage.animationPortal.x = 264;
            stage.animationPortal.y = 1;
        }
        else if(stage.animated == 2) {
            stage.animationPortal.x = 510;
            stage.animationPortal.y = 1;
        }
        else {
            stage.animationPortal.x = 758;
            stage.animationPortal.y = 1;
        }
        stage.animationPortalTime = SDL_GetTicks64();
        stage.animated += 1;
        stage.animated %= 4;
    }

    SDL_RenderCopy(renderer, stage.portalIMG, &stage.animationPortal, &stage.portal);
    
}




void RenderHome(Event &event, SDL_Renderer *renderer, Stage &stage) {
    // event.CheckEvent();
    stage.SetHome(renderer);
    
    while(event.appIsRunning) {
        if(event.curStage != 0) break;
        event.checkHome();


        if(event.mouseButtonLeftDown && event.isNewGame) {
            event.isNewGame = false;
            event.mouseButtonLeftDown = false;
            event.curStage = 1;
        }

        if(event.mouseButtonLeftDown && event.isContinue) { 
            event.mouseButtonDown = false;
            event.isContinue = false;
            ifstream input("levels/current.txt");
            input >> event.curStage;
            input.close();
        }


        SDL_RenderCopy(renderer, stage.homeImg, NULL, &stage.home);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
}








void RenderStage(Event &event, SDL_Renderer *renderer, Stage &stage, string level) {
    Player player;
    Hedgehog hedgehog;
    vector<vector<bool>> canMove(RIGHT-LEFT+1, vector<bool>(DOWN-UP+1, 1));
    vector<Dino> dinos;
    vector<Player::Bullet> bullets;
    vector<Firew> firews;



    stage.SetStage(renderer, level);

    player.Setplayer(renderer);
    player.bullet.SetPlayerBullet(renderer);
    
    ofstream output("levels/current.txt");
    output << event.curStage;
    output.close();
    
    string input = "levels/" + level + ".txt";
    ifstream file(input);
    

    int num = 0;
    file >> num;

    
    int x = 0;
    int y = 0;

    for(int i = 0; i < num; i++){
        Dino temp;
        file >> x >> y;
        
        temp.SetRect(renderer, x-INIT_X, y-INIT_Y);
        // temp.Fire();
        temp.bullet.SetRect(renderer);
        dinos.push_back(temp);
    }

    vector<SDL_Rect> boxes;
    file >> num;
    // cout << num << endl;
    for(int i = 0; i < num; i++) {
        SDL_Rect temp;
        file >> temp.x >> temp.y >> temp.w >> temp.h;
        boxes.push_back(temp);
    }

    for(int t = 0; t < boxes.size(); t++) {
        for(int i = boxes[t].x; i <= boxes[t].x+boxes[t].w; i++) {
            for(int j = boxes[t].y; j <= boxes[t].y+boxes[t].h; j++) {
                canMove[i-LEFT][j-UP] = false;
            }
        }
    }

    file >> num;

    for(int i = 0; i < num; i++) {
        file >> x >> y;
        Firew temp;
        temp.SetRect(renderer, x-INIT_X, y-INIT_Y);
        firews.push_back(temp);
    }

    file >> num;

    if(num == 1) {
        hedgehog.SetRect(renderer ,SCREEN_WIDTH/2, SCREEN_HEIGHT/2-300);
    }

    file.close();



    stage.SetPortal(renderer);
    // cout << player.player.w << ' ' << player.player.h << endl;
    // player.playerHP = 20;

    SDL_ShowCursor(SDL_DISABLE);

    // cerr << firews.size() << endl << dinos.size() << endl << boxes.size() << endl;

    while(event.appIsRunning) {
        event.CheckEvent();
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        
        MoveCamera(renderer, event, player, stage, dinos, bullets, canMove, boxes, firews, hedgehog);

        RenderBackground1(renderer, stage);
        

        Fire(renderer, event, player, bullets);
        for(int i = 0; i < bullets.size(); i++) {
            if(bullets[i].isFiring) {
                bullets[i].Move(event);
                CheckBorderCollision(event, bullets[i], stage, boxes);
                if(bullets[i].isFiring) {
                    SDL_RenderCopy(renderer, player.bullet.bulletImg, NULL, &bullets[i].bullet);
                }
            }
        }

        for(int i = 0; i < dinos.size(); i++) {
            DinoFire(event, renderer, dinos[i], player);
            if(dinos[i].bullet.isFiring) {
                dinos[i].bullet.Move(event);
                CheckBorderCollision(event, dinos[i].bullet, stage, boxes);
            }
        }

        DinoMove(event, dinos, stage, player, boxes);
        FirewMove(event, firews, stage, player, boxes);
        

        for(int i = 0; i < dinos.size(); i++) {
            for(int j = 0; j < bullets.size(); j++) {
                IsCollision(event, bullets[j], dinos[i]);
            }

            if(dinos[i].bullet.isFiring) {
                SDL_RenderCopy(renderer, dinos[i].bullet.rectImg, NULL, &dinos[i].bullet.rect);
            }

            IsCollision(event, dinos[i].bullet, player);
        }

        for(int i = 0; i < firews.size(); i++) {
            for(int j = 0; j < bullets.size(); j++) {
                IsCollision(event, bullets[j], firews[i]);
            }

            IsCollision(event, firews[i], player);
        }

        

        
        
        
        


        for(int i = 0; i < dinos.size(); i++) {
            RenderDino(renderer, dinos[i]);
        }

        for(int i = 0; i < firews.size(); i++) {
            RenderFirew(renderer, firews[i]);
        }

        if(num == 1) {
            SDL_RenderCopy(renderer, hedgehog.rectImg, NULL, &hedgehog.rect);
        }
        
        
        if(player.playerHP <= 0) {
            player.imgRect.x = 41;
            player.imgRect.y = 43;
            player.imgRect.w = 14;
            player.imgRect.h = 13;
            player.player.w = 60;
            player.player.h = 50;
            event.isLose = true;
            SDL_ShowCursor(SDL_ENABLE);
            SDL_RenderCopy(renderer, stage.retryImg, NULL, &stage.retry);
            SDL_RenderCopy(renderer, stage.loseImg, NULL, &stage.lose);
            RenderDeadPlayer(renderer, player);
            if(event.isRetry) {
                event.isRetry = false;
                event.isLose = false;
                event.mouseButtonLeftDown = false;
                break;
            }
        }
        else {
            if(CheckEnemiesDead(dinos, firews, num)) {
                RenderPortal(renderer, stage);
                if(Collision(player.player, stage.portal) && event.returnDown) {
                    event.curStage++;
                    break;
                }
            }
            RenderCustomDotCursor(renderer, player);
        }

        RenderPlayer(renderer, player);

        
        SDL_RenderPresent(renderer);
        SDL_Delay(16);   
    } 

    bullets.clear();
    canMove.clear();
    boxes.clear();
    dinos.clear();
}




void RenderEnd(Event &event, SDL_Renderer *renderer, Stage &stage) {
    stage.SetEnd(renderer);
    SDL_ShowCursor(SDL_ENABLE);

    while(event.appIsRunning) {
        if(event.curStage != END) break;
        event.CheckEnd();


        if(event.mouseButtonLeftDown && event.isNewGame) {
            event.isNewGame = false;
            event.mouseButtonLeftDown = false;
            event.curStage = 1;
        }


        SDL_RenderCopy(renderer, stage.endImg, NULL, &stage.end);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
}
