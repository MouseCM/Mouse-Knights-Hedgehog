class Fire {

    public:
        int rectW = 0;
        int rectH = 0;
        int hp = 100;
        SDL_Texture *rectImg = NULL;
        SDL_Rect rect = {0, 0, 0, 0};
        SDL_Rect hpRect = {0, 0, 0, 0};
    
    
        void SetRect(SDL_Renderer *renderer, int x, int y) {
            rectImg = IMG_LoadTexture(renderer, "assets/dino.png");
            SDL_QueryTexture(rectImg, NULL, NULL, &rectW, &rectH);
            rect.w = rectW*2;
            rect.h = rectH*2;
            rect.x = x;
            rect.y = y;
            hpRect.h = 10;
        }
    

};