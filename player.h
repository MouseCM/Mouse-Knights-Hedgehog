using namespace std;


class Player {
public:
    int playerW = 0;
    int playerH = 0;
    SDL_Rect player = {0, 0, 0, 0}; 
    SDL_Rect imgRect = {0, 0, 30, 40};
    int playerSpeed = 5;
    int playerHP = 100;
    SDL_Rect playerHPRect = {0, 0, 0, 0};
    SDL_Texture *playerImg = NULL;
    SDL_Texture *playerImgHurt = NULL;
    SDL_Texture *dot = NULL;
    SDL_Texture *hp = NULL;
    SDL_Texture *name = NULL;
    int hurtTime = SDL_GetTicks64()-200;
    
    
    void Setplayer(SDL_Renderer *renderer) {
        playerImg = IMG_LoadTexture(renderer, "assets/mouse.png");
        playerImgHurt = IMG_LoadTexture(renderer, "assets/mouseHurt.png");
        dot = IMG_LoadTexture(renderer, "assets/dot.png");
        hp = IMG_LoadTexture(renderer, "assets/hp.png");
        name = IMG_LoadTexture(renderer, "assets/name.png");
	    SDL_QueryTexture(playerImg, NULL, NULL, &playerW, &playerH);
        imgRect = {17, 17, 14, 15};
        player.w = 50;
        player.h = 60;
        // player.w = playerW*1.5;
        // player.h = playerH*1.5;
        player = {SCREEN_WIDTH/2-player.w/2, SCREEN_HEIGHT/2-player.h/2, player.w, player.h};
    }


    class Bullet {
    public:
        int rectW = 0;
        int rectH = 0;
        SDL_Texture *bulletImg = NULL;
        SDL_Rect bullet = {26, 26, 26, 26};
        int speed = 40;
        int aimX = 0;
        int aimY = 0;
        float deltaX = 0;
        float deltaY = 0;
        bool isFiring = false;
        float angle = 0;
        int reloadTime = SDL_GetTicks64();
        int damage = 10;


        void SetPlayerBullet(SDL_Renderer *renderer) {
            bulletImg = IMG_LoadTexture(renderer, "assets/bullet.png");
            SDL_QueryTexture(bulletImg, NULL, NULL, &rectW, &rectH);
            bullet.w = rectW * 1.5;
            bullet.h = rectH * 1.5;
        }


        void Move(Event &event) {

            if(isFiring) {
                deltaX += cos(angle) * speed;
                deltaY += sin(angle) * speed;
                bullet.x = deltaX;
                bullet.y = deltaY;
            }
        }
    };

    Bullet bullet;
};


