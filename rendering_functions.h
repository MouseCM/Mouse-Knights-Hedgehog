void RenderHitbox(SDL_Renderer *renderer, SDL_Rect rect) {
    SDL_SetRenderDrawColor(renderer, 255, 105, 180, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &rect);
}

void RenderStage(SDL_Renderer *renderer, Stage &stage) {
    
    SDL_RenderCopy(renderer, stage.backgroundImg, NULL, &stage.background);
    // SDL_DestroyTexture(backgroundImg);



    // render border
    

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
    player.playerHPRect.x = player.player.x;
    player.playerHPRect.y = player.player.y-25;
    player.playerHPRect.w = player.playerW*1.5;

    SDL_Rect temp = {player.player.x, player.player.y-25, player.playerW*1.5, 10};
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

    dino.dinoBullet.x += 1;
    dino.dinoBullet.y += 1;
    if (dino.isFiring && dino.dinoBulletNum >= 1) {
        SDL_RenderCopy(renderer, dino.dinoBulletImg, NULL, &dino.dinoBullet);
        // cout << dino.dinoBullet.x << " " << dino.dinoBullet.y << endl;
    }

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

