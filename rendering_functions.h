

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

    SDL_RenderCopy(renderer, dino.rectImg, NULL, &dino.rect);
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
    player.Setplayer(renderer);
    player.bullet.SetPlayerBullet(renderer);
    
    vector<vector<bool>> canMove(RIGHT-LEFT+1, vector<bool>(DOWN-UP+1, 1));
    // vector<vector<bool>>* canMove = new vector<vector<bool>>(RIGHT-LEFT+1, vector<bool>(DOWN-UP+1, 1));

    
 
    

    stage.SetStage(renderer, level);

    string input = "levels/" + level + ".txt";
    ifstream file(input);
    
    int num = 0;
    file >> num;

    vector<Dino> dinos;
    vector<Player::Bullet> bullets;

    
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


    file.close();



    stage.SetPortal(renderer);
    // cout << player.player.w << ' ' << player.player.h << endl;
    // player.playerHP = 20;

    while(event.appIsRunning) {
        event.CheckEvent();
        SDL_ShowCursor(SDL_DISABLE);

        
        // player.Move(event);
        
        
        
        MoveCamera(renderer, event, player, stage, dinos, bullets, canMove, boxes);

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
                CheckBorderCollision(bullets[i], stage, boxes);
                if(bullets[i].isFiring) {
                    SDL_RenderCopy(renderer, player.bullet.bulletImg, NULL, &bullets[i].bullet);
                }
            }
        }

        for(int i = 0; i < dinos.size(); i++) {
            DinoFire(renderer, dinos[i], player);
            if(dinos[i].bullet.isFiring) {
                dinos[i].bullet.Move(event);
                CheckBorderCollision(dinos[i].bullet, stage, boxes);
            }
        }

        DinoMove(dinos, stage, player, boxes);
        

        for(int i = 0; i < dinos.size(); i++) {
            for(int j = 0; j < bullets.size(); j++) {
                IsCollision(bullets[j], dinos[i]);
            }

            if(dinos[i].bullet.isFiring) {
                SDL_RenderCopy(renderer, dinos[i].bullet.rectImg, NULL, &dinos[i].bullet.rect);
            }

            IsCollision(event, dinos[i].bullet, player);
        }

        

        
        
        
        


        // render bullet
        // if(player.bullet.isFiring) {
        //     SDL_RenderCopy(renderer, player.bullet.bulletImg, NULL, &player.bullet.bullet);
        // }

        for(int i = 0; i < dinos.size(); i++) {
            // cout << dino[i].hp << ' ' << dino[i].rect.x << ' ' << dino[i].rect.y << endl;
            RenderDino(renderer, dinos[i]);
        }

        
        RenderPlayer(renderer, player);

        
        
        if(player.playerHP <= 0) {
            SDL_ShowCursor(SDL_ENABLE);
            event.CheckRetry();
            SDL_RenderCopy(renderer, stage.retryImg, NULL, &stage.retry);
            if(event.isRetry) {
                event.isRetry = false;
                event.mouseButtonLeftDown = false;
                // dino.clear();
                // bullets.clear();
                // canMove.clear();
                // boxes.clear();
                // RenderStage(event, renderer, stage, to_string(event.curStage));
                break;
            }
        }
        else {
            if(CheckDinoDead(dinos)) {
                SDL_RenderCopy(renderer, stage.portalIMG, NULL, &stage.portal);
                if(Collision(player.player, stage.portal)) {
                    event.curStage++;
                    ofstream output("levels/current.txt");
                    output << event.curStage;
                    output.close();
                    break;
                }
            }
            RenderCustomDotCursor(renderer);
        }

        

        
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
