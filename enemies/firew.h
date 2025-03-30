class Firew {
public:
    int rectW = 0;
    int rectH = 0;
    int hp = 100;
    int damage = 60;
    int boomTime = SDL_GetTicks64()-2000;
    int hurtTime = SDL_GetTicks64()-200;
    float deltaX;
    float deltaY;
    SDL_Texture *rectImg = NULL;
    SDL_Texture *rectImgHurt = NULL;
    SDL_Rect rect = {0, 0, 0, 0};
    SDL_Rect hpRect = {0, 0, 0, 0};

    SDL_Rect boomRect = {0, 0, 0, 0};
    SDL_Texture *boomImg = NULL;


    void SetRect(SDL_Renderer *renderer, int x, int y) {
        rectImg = IMG_LoadTexture(renderer, "assets/firew.png");
        rectImgHurt = IMG_LoadTexture(renderer, "assets/firewHurt.png");
        boomImg = IMG_LoadTexture(renderer, "assets/boom.png");
        SDL_QueryTexture(rectImg, NULL, NULL, &rectW, &rectH);
        rect = {x, y, rectW*15/10, rectH*15/10}; 
        boomRect = rect;        
        deltaX = x;
        deltaY = y;
        hpRect.h = 10;
    }

    

};