class Dino {

public:
    int dinoW = 0;
    int dinoH = 0;
    int dinoHP = 100;
    SDL_Texture *dinoImg = NULL;
    SDL_Rect dino = {0, 0, 0, 0};
    SDL_Rect dinoHPRect = {0, 0, 0, 0};


    void SetDino(SDL_Renderer *renderer, int x, int y) {
        dinoImg = IMG_LoadTexture(renderer, "assets/dino.png");
        SDL_QueryTexture(dinoImg, NULL, NULL, &dinoW, &dinoH);
        dino.w = dinoW*2;
        dino.h = dinoH*2;
        dino.x = x;
        dino.y = y;
        dinoHPRect.h = 10;

        
    }

    class Bullet {
    public:
        SDL_Texture *rectImg = NULL;
        SDL_Rect rect = {0, 0, 0, 0};
        int W = 0;
        int H = 0;
        int dinoSpeed = 5;
        int rectSpeed = 10;
        int rectNum = 0;
        bool isFiring = false;

        void SetRect(SDL_Renderer *renderer, Dino dino) {
            rectImg = IMG_LoadTexture(renderer, "assets/rect.png");
            SDL_QueryTexture(rectImg, NULL, NULL, &W, &H);
            rect.h = H*2;
            rect.w = W*2;
            if (rectNum == 0) {
                rect.x = dino.dino.x + dino.dino.w/2;
                rect.y = dino.dino.y + dino.dino.h/2;
            }
            SDL_RenderCopy(renderer, rectImg, NULL, &rect);
            rectNum++;
            isFiring = true;
        }

        
    };

    Bullet bullet;

};