

void RenderHitboxes(SDL_Renderer *renderer, SDL_Rect rect) {
    SDL_SetRenderDrawColor(renderer, 255, 105, 180, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &rect);
}

void RenderBackground(SDL_Renderer *renderer, Stage &stage) {
    SDL_RenderCopy(renderer, stage.backgroundImg, NULL, &stage.background);
}

void RenderCustomDotCursor(SDL_Renderer* renderer, Player &player) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    
    SDL_Rect dotRect = {mouseX - 20, mouseY - 20, 40, 40};

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

void RenderHedgehog(SDL_Renderer *renderer, Hedgehog &hedgehog, vector<Hedgehog::Gun> &guns) {
    if (hedgehog.hp <= 0) {
        return;
    }


    if(SDL_GetTicks64() <= hedgehog.hurtTime+200) {
        SDL_RenderCopy(renderer, hedgehog.rectImgHurt, NULL, &hedgehog.rect);
    }
    else {
        SDL_RenderCopy(renderer, hedgehog.rectImg, NULL, &hedgehog.rect);
    }

    for(int i = 0 ;i < guns.size(); i++) {
        if(SDL_GetTicks64() <= guns[i].hurtTime+200) {
            SDL_RenderCopy(renderer, guns[i].rectImgHurt, NULL, &guns[i].rect);
        }
        else {
            SDL_RenderCopy(renderer, guns[i].rectImg, NULL, &guns[i].rect);
        }

        if(guns[i].bullet.isFiring) {
            SDL_RenderCopy(renderer, guns[i].bullet.rectImg, NULL, &guns[i].bullet.rect);
        }
    }

    hedgehog.hpRect.w = float(hedgehog.hp)/1000 * 600;

    SDL_Rect temp = {SCREEN_WIDTH/2-300, 30, 600, 20};
    SDL_SetRenderDrawColor(renderer, 150, 150, 150, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &temp);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &hedgehog.hpRect);

}

void RenderDeadPlayer(SDL_Renderer *renderer, Player &player) {
    SDL_RenderCopy(renderer, player.playerImg, &player.imgRect, &player.player);
}

void RenderDino(SDL_Renderer *renderer, Dino &dino) {
    if (dino.hp <= 0) {
        return;
    }

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

void RenderFirew(SDL_Renderer *renderer, Audio &audio, Firew &firew) {
    if (firew.hp <= 0) {
        if(SDL_GetTicks64() <= firew.boomTime+100) {
            audio.FirewExplosion();
        }
        if(SDL_GetTicks64() <= firew.boomTime+1000) {
            firew.boomRect.x = firew.rect.x;
            firew.boomRect.y = firew.rect.y;
            SDL_RenderCopy(renderer, firew.boomImg, NULL, &firew.boomRect);
            
        }
        return;
    }

    firew.hpRect.x = firew.rect.x;
    firew.hpRect.y = firew.rect.y-25;
    firew.hpRect.w = float(firew.hp)/100 * firew.rect.w;
    
    SDL_Rect temp = {firew.rect.x, firew.rect.y-25, firew.rect.w, 10};
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








void RenderStage(Event &event, SDL_Renderer *renderer, Stage &stage, Audio &audio, string level) {
    Player player;
    Hedgehog hedgehog;
    vector<vector<bool>> canMove(RIGHT-LEFT+1, vector<bool>(DOWN-UP+1, 1));
    vector<Dino> dinos;
    vector<Player::Bullet> bullets;
    vector<Firew> firews;
    int curBullet = 0;


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
        for(int i = 0; i < 4; i++) {
            firews[i].hp = 0;
            dinos[i].hp = 0;
        }
        hedgehog.bullet.SetRect(renderer);
    }
    else {
        hedgehog.hp = 0;
    }

    vector<Hedgehog::Bullet> hedgehogBullets(8);
    for(int i = 0; i < hedgehogBullets.size(); i++) {
        hedgehogBullets[i].SetRect(renderer);
    }

    vector<Hedgehog::Gun> guns(4);
    
    for(int i = 0; i < guns.size(); i++) {
        guns[i].SetRect(renderer, 0, 0);
        guns[i].bullet.SetRect(renderer);
    }
    guns[0].SetRect(renderer, LEFT-INIT_X, UP-INIT_Y);
    guns[1].SetRect(renderer, LEFT-INIT_X, DOWN-INIT_Y-guns[1].rect.h);
    guns[2].SetRect(renderer, RIGHT-INIT_X-guns[2].rect.w, UP-INIT_Y);
    guns[3].SetRect(renderer, RIGHT-INIT_X-guns[3].rect.w, DOWN-INIT_Y-guns[2].rect.h);

    file.close();


    stage.SetPortal(renderer);

    SDL_ShowCursor(SDL_DISABLE);

    while(event.appIsRunning) {
        event.CheckEvent();
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        
        MoveCamera(renderer, event, audio, player, stage, dinos, bullets, canMove, boxes, firews, hedgehog, hedgehogBullets, guns, num);

        RenderBackground(renderer, stage);
        

        Fire(renderer, event, audio, player, bullets);
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
            DinoFire(event, renderer, audio, dinos[i], player);
            if(dinos[i].bullet.isFiring) {
                dinos[i].bullet.Move(event);
                CheckBorderCollision(event, dinos[i].bullet, stage, boxes);
            }
        }


        DinoMove(event, dinos, stage, player, boxes);

        FirewMove(event, firews, stage, player, boxes);
        

        for(int i = 0; i < dinos.size(); i++) {
            for(int j = 0; j < bullets.size(); j++) {
                CheckCollision(event, bullets[j], dinos[i]);
            }

            if(dinos[i].bullet.isFiring) {
                SDL_RenderCopy(renderer, dinos[i].bullet.rectImg, NULL, &dinos[i].bullet.rect);
            }

            CheckCollision(event, dinos[i].bullet, player);
        }

        for(int i = 0; i < firews.size(); i++) {
            for(int j = 0; j < bullets.size(); j++) {
                CheckCollision(event, bullets[j], firews[i]);
            }

            CheckCollision(event, firews[i], player);
        }


        for(int i = 0; i < dinos.size(); i++) {
            RenderDino(renderer, dinos[i]);
        }

        for(int i = 0; i < firews.size(); i++) {
            RenderFirew(renderer, audio, firews[i]);
        }


        // BOSS
        if(num == 1 && hedgehog.hp > 0) {
            for(int i = 0; i < bullets.size(); i++) {
                CheckCollision(event, bullets[i], hedgehog, guns);
            }

            for(int i = 0; i < guns.size(); i++) {
                for(int j = 0; j < bullets.size(); j++) {
                    CheckCollision(event, bullets[j], guns[i], guns, hedgehog);
                }
                
                GunFire(event, renderer, audio, guns[i], player);
                if(guns[i].bullet.isFiring) {
                    guns[i].bullet.Move();
                    CheckBorderCollision(event, guns[i].bullet, stage);
                    CheckCollision(event, guns[i].bullet, player);
                }
            }


            SpawnFirew(hedgehog, firews, stage);


            // skill 1
            if(curBullet < hedgehogBullets.size()-1) {
                if(SDL_GetTicks64() >= hedgehog.bullet.skill1ReloadTime) {
                    HedgehogFire(event, renderer, audio, hedgehog, hedgehogBullets[curBullet], player);
                    hedgehog.bullet.skill1ReloadTime = SDL_GetTicks64()+200;
                    curBullet++;
                }
            }
            else {
                if(SDL_GetTicks64() >= hedgehog.bullet.skill1ReloadTime) {
                    HedgehogFire(event, renderer, audio, hedgehog, hedgehogBullets[curBullet], player);
                    hedgehog.bullet.skill1ReloadTime = SDL_GetTicks64()+7800;
                    curBullet = 0;
                }
            }


            // skill 2
            if(SDL_GetTicks64() >= hedgehog.bullet.skill2ReloadTime) {
                for(int i = 0; i < hedgehogBullets.size(); i++) {
                    if(!hedgehogBullets[i].isFiring) {
                        HedgehogFire(event, renderer, audio, hedgehog, hedgehogBullets[i], player);
                        hedgehog.bullet.skill2ReloadTime = SDL_GetTicks64()+8000;

                        if(i == 0) {
                            hedgehogBullets[i].angle = 0;
                        }
                        else if(i == 1) {
                            hedgehogBullets[i].angle = M_PI/2;
                        }
                        else if(i == 2) {
                            hedgehogBullets[i].angle = M_PI;
                        }
                        else if(i == 3) {
                            hedgehogBullets[i].angle = -M_PI/2;
                        }
                        else if(i == 4) {
                            hedgehogBullets[i].angle = M_PI/4;
                        }
                        else if(i == 5) {
                            hedgehogBullets[i].angle = -M_PI/4;
                        }
                        else if(i == 6) {
                            hedgehogBullets[i].angle = 3*M_PI/4;
                        }
                        else if(i == 7) {
                            hedgehogBullets[i].angle = -3*M_PI/4;
                        }
                    }
                    else {
                        hedgehogBullets[i].Move();
                        CheckBorderCollision(event, hedgehogBullets[i], stage);
                    }
                }
            }

            
            for(int i = 0; i < hedgehogBullets.size(); i++) {
                if(hedgehogBullets[i].isFiring) {
                    hedgehogBullets[i].Move();
                    CheckBorderCollision(event, hedgehogBullets[i], stage);
                    CheckCollision(event, hedgehogBullets[i], player);
                    SDL_RenderCopy(renderer, hedgehog.bullet.rectImg, NULL, &hedgehogBullets[i].rect);
                }
            }
            RenderHedgehog(renderer, hedgehog, guns);
            
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
            if(CheckEnemiesDead(dinos, firews, hedgehog)) {
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
