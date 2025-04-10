class Hedgehog {
public:
    int hp = 1000;
    int hurtTime = 0;
    float deltaX;
    float deltaY;
    SDL_Texture *rectImg = NULL;
    SDL_Texture *rectImgHurt = NULL;
    SDL_Rect rect = {0, 0, 0, 0};
    SDL_Rect hpRect = {0, 0, 0, 0};

    int spawnTime = SDL_GetTicks64()+2000;
    bool isSpawned = false;


    void SetRect(SDL_Renderer *renderer, int x, int y) {
        rectImg = IMG_LoadTexture(renderer, "assets/hedgehog.png");
        rectImgHurt = IMG_LoadTexture(renderer, "assets/hedgehogHurt.png");
        SDL_QueryTexture(rectImg, NULL, NULL, &rect.w, &rect.h);
        rect = {x, y, rect.w*5, rect.h*5};
        deltaX = x;
        deltaY = y;
        hpRect = {SCREEN_WIDTH/2-300, 30, 600, 20};
        hurtTime = SDL_GetTicks64()-500;
    }

    

    class Bullet {
    public:
        SDL_Texture *rectImg = NULL;
        SDL_Rect rect = {0, 0, 0, 0};

        int rectSpeed = 10;
        bool isFiring = false;
        int aimX = 0;
        int aimY = 0;
        float angle = 0;
        float deltaX = 0;
        float deltaY = 0;
        int skill1ReloadTime = SDL_GetTicks64()+1000;
        int skill2ReloadTime = SDL_GetTicks64()+5000;
        int damage = 10;

        void SetRect(SDL_Renderer *renderer) {
            rectImg = IMG_LoadTexture(renderer, "assets/dinoBullet.png");
            SDL_QueryTexture(rectImg, NULL, NULL, &rect.w, &rect.h);
            rect = {0, 0, rect.w*2, rect.h*2};
        }    

        void Move() {
            if(isFiring) {
                deltaX += cos(angle) * rectSpeed;
                deltaY += sin(angle) * rectSpeed;
                rect.x = deltaX;
                rect.y = deltaY;
            }
        }
    };

    class Gun {
    public:
        SDL_Texture *rectImg = NULL;
        SDL_Texture *rectImgHurt = NULL;
        SDL_Rect rect = {0, 0, 0, 0};
        int hurtTime = SDL_GetTicks64()-200;

        void SetRect(SDL_Renderer *renderer, int x, int y) {
            rectImg = IMG_LoadTexture(renderer, "assets/gun.png");
            rectImgHurt = IMG_LoadTexture(renderer, "assets/gunHurt.png");
            SDL_QueryTexture(rectImg, NULL, NULL, &rect.w, &rect.h);
            rect = {x, y, rect.w*15/10, rect.h*15/10};
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
    
            void Move() {
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

    Bullet bullet;
};