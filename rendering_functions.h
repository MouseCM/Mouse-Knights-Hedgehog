
// render hitboxes use for debugging
void RenderHitboxes(SDL_Renderer *renderer, SDL_Rect rect) {
    SDL_SetRenderDrawColor(renderer, 255, 105, 180, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &rect);
}


// render background which is stage 1 2 3 .... 
void RenderBackground(SDL_Renderer *renderer, Stage &stage) {
    SDL_RenderCopy(renderer, stage.backgroundImg, NULL, &stage.background);
}


// render custom scope aka red dot
void RenderCustomDotCursor(SDL_Renderer* renderer, Player &player) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    
    SDL_Rect dotRect = {mouseX - 20, mouseY - 20, 40, 40};

    SDL_RenderCopy(renderer, player.dot, NULL, &dotRect);
}


// render player mouse
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


// render boss hedgehog
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


// render when player dead
void RenderDeadPlayer(SDL_Renderer *renderer, Player &player) {
    SDL_RenderCopy(renderer, player.playerImg, &player.imgRect, &player.player);
}


// render single dino
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

// render dinos
void RenderDinos(SDL_Renderer *renderer, vector<Dino> &dinos) {
    for(int i = 0; i < dinos.size(); i++) {
        RenderDino(renderer, dinos[i]);
    }
}


// render single firew
void RenderFirew(SDL_Renderer *renderer, Audio &audio, Firew &firew) {
    if(firew.hp < 0) return;
    if (firew.hp == 0) {
        if(SDL_GetTicks64() <= firew.boomTime+1) {
            audio.FirewExplosion();
            // firew.hp -= 1;
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

// render firews
void RenderFirews(SDL_Renderer *renderer, Audio &audio, vector<Firew> &firews) {
    for(int i = 0; i < firews.size(); i++) {
        RenderFirew(renderer, audio, firews[i]);
    }
}



// render portal when player win
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



void RenderHedgehogStage(Event &event, SDL_Renderer *renderer, Audio &audio, Stage &stage, Hedgehog &hedgehog, Player &player, vector<Player::Bullet> bullets, vector<Hedgehog::Bullet> &hedgehogBullets, vector<Hedgehog::Gun> &guns, vector<Firew> &firews){
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


    SpawnFirew(hedgehog, firews, stage, renderer);


    // skill 1
    if(hedgehog.curBullet < hedgehogBullets.size()-1) {
        if(SDL_GetTicks64() >= hedgehog.bullet.skill1ReloadTime) {
            HedgehogFire(event, renderer, audio, hedgehog, hedgehogBullets[hedgehog.curBullet], player);
            hedgehog.bullet.skill1ReloadTime = SDL_GetTicks64()+200;
            hedgehog.curBullet++;
        }
    }
    else {
        if(SDL_GetTicks64() >= hedgehog.bullet.skill1ReloadTime) {
            HedgehogFire(event, renderer, audio, hedgehog, hedgehogBullets[hedgehog.curBullet], player);
            hedgehog.bullet.skill1ReloadTime = SDL_GetTicks64()+6800;
            hedgehog.curBullet = 0;
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

bool RenderLossScreen(Event &event, SDL_Renderer *renderer, Player &player, Stage &stage) {
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
        return 0;
    }

    return 1;
}

// render home screen (first screen)
void RenderHome(Event &event, SDL_Renderer *renderer, Stage &stage) {
    // event.CheckEvent();
    stage.SetHome(renderer);
    
    while(event.appIsRunning) {
        if(event.curStage != 0) break;
        event.checkHome();


        // check newgame button is clicked
        if(event.mouseButtonLeftDown && event.isNewGame) {
            event.isNewGame = false;
            event.mouseButtonLeftDown = false;
            event.curStage = 1;
        }

        // check continue button is clicked
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







// render stage 
void RenderStage(Event &event, SDL_Renderer *renderer, Stage &stage, Audio &audio, string level) {
    Player player;
    Hedgehog hedgehog;
    vector<vector<bool>> canMove(RIGHT-LEFT+1, vector<bool>(DOWN-UP+1, 1));
    vector<Dino> dinos;
    vector<Player::Bullet> bullets;
    vector<Firew> firews;
    vector<SDL_Rect> boxes;
    vector<Hedgehog::Bullet> hedgehogBullets(8);
    vector<Hedgehog::Gun> guns(4);
    int num = 0;


    stage.SetStage(renderer, level);

    player.Setplayer(renderer);
    player.bullet.SetPlayerBullet(renderer);
    
    ofstream output("levels/current.txt");
    output << event.curStage;
    output.close();
    
    string input = "levels/" + level + ".txt";
    
    InitStage(input, renderer, stage, dinos, firews, guns, hedgehog, boxes, canMove, hedgehogBullets, num);


    stage.SetPortal(renderer);

    SDL_ShowCursor(SDL_DISABLE);

    while(event.appIsRunning) {
        event.CheckEvent();
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        

        MoveCamera(renderer, event, audio, player, stage, dinos, bullets, canMove, boxes, firews, hedgehog, hedgehogBullets, guns, num);


        RenderBackground(renderer, stage);
        

        // player firing bullet
        PlayerBullet(event, renderer, audio, stage, bullets, player, boxes, dinos, firews);

        // make dino fire a bullet and moving and border checking
        DinosBullet(event, renderer, audio, stage, dinos, player, boxes);


        // move dino
        DinosMove(event, dinos, stage, player, boxes);

        // move firew
        FirewsMove(event, firews, stage, player, boxes);



        // check firews close to player to boom
        FirewsBoom(event, firews, player);


        RenderDinos(renderer, dinos);
        

        RenderFirews(renderer, audio, firews);
        


        // BOSS stage
        if(num == 1 && hedgehog.hp > 0) {
            RenderHedgehogStage(event, renderer, audio, stage, hedgehog, player, bullets, hedgehogBullets, guns, firews);
        }
        
        

        // check if player is dead
        if(player.playerHP <= 0) {
            if(!RenderLossScreen(event, renderer, player, stage)) break;
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

    // reset
    bullets.clear();
    canMove.clear();
    boxes.clear();
    dinos.clear();
    hedgehogBullets.clear();
    firews.clear();
    guns.clear();
}



// render end screen when player finish the game
void RenderEnd(Event &event, SDL_Renderer *renderer, Stage &stage) {
    stage.SetEnd(renderer);
    SDL_ShowCursor(SDL_ENABLE);

    while(event.appIsRunning) {
        if(event.curStage != END) break;
        event.CheckEnd();

        // check newgame button is clicked
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
