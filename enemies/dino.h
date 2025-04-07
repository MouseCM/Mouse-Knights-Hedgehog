class Dino {

public:
    int hp = 100;
    int hurtTime = 0;
    float deltaX;
    float deltaY;
    SDL_Texture *rectImg = NULL;
    SDL_Texture *rectImgHurt = NULL;
    SDL_Rect rect = {0, 0, 0, 0};
    SDL_Rect hpRect = {0, 0, 0, 0};


    void SetRect(SDL_Renderer *renderer, int x, int y) {
        rectImg = IMG_LoadTexture(renderer, "assets/dino.png");
        rectImgHurt = IMG_LoadTexture(renderer, "assets/dinoHurt.png");
        SDL_QueryTexture(rectImg, NULL, NULL, &rect.w, &rect.h);
        rect = {x, y, rect.w*2, rect.h*2};
        deltaX = x;
        deltaY = y;
        hurtTime = SDL_GetTicks64()-501;
        hpRect.h = 10;
    }

    class Bullet {
    public:
        SDL_Texture *rectImg = NULL;
        SDL_Rect rect = {0, 0, 0, 0};
        int rectSpeed = 10;
        bool isFiring = false;
        float angle = 0;
        float deltaX = 0;
        float deltaY = 0;
        int reloadTime = SDL_GetTicks64()+500;
        int damage = 10;

        void SetRect(SDL_Renderer *renderer) {
            rectImg = IMG_LoadTexture(renderer, "assets/dinoBullet.png");
            SDL_QueryTexture(rectImg, NULL, NULL, &rect.w, &rect.h);
            rect = {0, 0, rect.w*2, rect.h*2};
        }

        void Move(Event &event) {
            if(isFiring) {
                deltaX += cos(angle) * rectSpeed;
                deltaY += sin(angle) * rectSpeed;
                rect.x = deltaX;
                rect.y = deltaY;
            }
        }

        
        
    };

    Bullet bullet;


};