class Dino {

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
        rect = {x, y, rectW*2, rectH*2};
        hpRect.h = 10;
    }

    class Bullet {
    public:
        SDL_Texture *rectImg = NULL;
        SDL_Rect rect = {0, 0, 0, 0};
        int W = 0;
        int H = 0;
        // int rectSpeed = 10;
        int rectSpeed = 10;
        bool isFiring = false;
        int aimX = 0;
        int aimY = 0;
        float angle = 0;
        float deltaX = 0;
        float deltaY = 0;
        int reloadTime = SDL_GetTicks64();
        int damage = 10;

        void SetRect(SDL_Renderer *renderer) {
            rectImg = IMG_LoadTexture(renderer, "assets/dinoBullet.png");
            SDL_QueryTexture(rectImg, NULL, NULL, &W, &H);
            rect = {0, 0, W*2, H*2};
            // if (rectNum == 0) {
            //     rect.x = rect.rect.x + rect.rect.w/2;
            //     rect.y = rect.rect.y + rect.rect.h/2;
            // }
            // SDL_RenderCopy(renderer, rectImg, NULL, &rect);
            // rectNum++;
            // isFiring = true;
        }

        void Move(Event &event) {
            // if(isFiring && SDL_GetTicks64() >= existTime) {
            //     isFiring = false;
            //     isLose = true;
            // }

            if(isFiring) {
                // cout << angle << endl;
                deltaX += cos(angle) * rectSpeed;
                deltaY += sin(angle) * rectSpeed;
                rect.x = deltaX;
                rect.y = deltaY;
            }

            // cout << rotateX << ' ' << rotateY << endl;
            // cout << bullet.x << ' ' << bullet.y << endl;
            // cout << bullet.w << ' ' << bullet.h << endl;
        }

        
        
    };

    Bullet bullet;


};