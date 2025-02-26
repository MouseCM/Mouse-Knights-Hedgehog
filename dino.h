

class Dino {

public:
    int dinoW = 0;
    int dinoH = 0;
    int dinoHP = 100;
    SDL_Texture *dinoImg = NULL;
    SDL_Rect dino = {0, 0, 0, 0};
    SDL_Rect dinoHPRect = {0, 0, 0, 0};

    void SetDino(SDL_Renderer *renderer, int pos) {
        dinoImg = IMG_LoadTexture(renderer, "assets/dino.png");
        SDL_QueryTexture(dinoImg, NULL, NULL, &dinoW, &dinoH);
        dino.w = dinoW*2;
        dino.h = dinoH*2;
        dino.x = rand()%500 + pos;
        dino.y = rand()%500;
        dinoHPRect.h = 10;
    }

    // void Fire() {

    // }

};