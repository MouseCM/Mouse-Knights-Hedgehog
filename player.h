using namespace std;


class Player {
public:
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
	    SDL_QueryTexture(playerImg, NULL, NULL, &player.w, &player.h);
        imgRect = {17, 17, 14, 15};
        player = {0, 0, player.w/35*10, player.h/35*10};
        player = {SCREEN_WIDTH/2-player.w/2, SCREEN_HEIGHT/2-player.h/2, player.w, player.h};
    }


    class Bullet {
    public:
        SDL_Texture *bulletImg = NULL;
        SDL_Rect bullet = {0, 0, 0, 0};
        int speed = 40;
        int aimX = 0;
        int aimY = 0;
        float deltaX = 0;
        float deltaY = 0;
        bool isFiring = false;
        float angle = 0;
        int reloadTime = SDL_GetTicks64()-500;
        int damage = 10;


        void SetPlayerBullet(SDL_Renderer *renderer) {
            bulletImg = IMG_LoadTexture(renderer, "assets/bullet.png");
            SDL_QueryTexture(bulletImg, NULL, NULL, &bullet.w, &bullet.h);
            bullet = {0, 0, bullet.w*15/10, bullet.h*15/10};
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


