class Hedgehog {
public:
    int rectW = 0;
    int rectH = 0;
    int hp = 5000;
    int hurtTime = 0;
    float deltaX;
    float deltaY;
    SDL_Texture *rectImg = NULL;
    SDL_Texture *rectImgHurt = NULL;
    SDL_Rect rect = {0, 0, 0, 0};
    SDL_Rect hpRect = {0, 0, 0, 0};


    void SetRect(SDL_Renderer *renderer, int x, int y) {
        rectImg = IMG_LoadTexture(renderer, "assets/hedgehog.png");
        rectImgHurt = IMG_LoadTexture(renderer, "assets/hedgehogHurt.png");
        SDL_QueryTexture(rectImg, NULL, NULL, &rectW, &rectH);
        rect = {x, y, rectW*5, rectH*5};
        deltaX = x;
        deltaY = y;
        hurtTime = SDL_GetTicks64()-501;
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
        int reloadTime = SDL_GetTicks64()+500;
        int damage = 10;

        void SetRect(SDL_Renderer *renderer) {
            rectImg = IMG_LoadTexture(renderer, "assets/dinoBullet.png");
            SDL_QueryTexture(rectImg, NULL, NULL, &W, &H);
            rect = {0, 0, W*2, H*2};
        }



        
        
    };

    
    
    };