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

    class Bullet {
        SDL_Texture *dinoBulletImg = NULL;
        SDL_Rect dinoBullet = {0, 0, 0, 0};
        int dinoBulletW = 0;
        int dinoBulletH = 0;
        int dinoSpeed = 5;
        int dinoBulletSpeed = 10;
        int dinoBulletNum = 0;
        bool isFiring = false;

        void SetDinoBullet(SDL_Renderer *renderer) {
            dinoBulletImg = IMG_LoadTexture(renderer, "assets/dinoBullet.png");
            SDL_QueryTexture(dinoBulletImg, NULL, NULL, &dinoBulletW, &dinoBulletH);
            dinoBullet.h = dinoBulletH*2;
            dinoBullet.w = dinoBulletW*2;
            // if (dinoBulletNum == 0) {
            //     dinoBullet.x = dino.x + dino.w/2;
            //     dinoBullet.y = dino.y + dino.h/2;
            // }
            // dinoBulletNum++;
            // isFiring = true;
        }
    };

    Bullet bullet;

};