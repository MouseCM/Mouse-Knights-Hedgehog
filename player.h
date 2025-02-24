class Player {
    


public:
    int playerW = 0;
    int playerH = 0;
    SDL_Rect player = {0, 0, 0, 0}; 
    int playerSpeed = 10;
    int playerHP = 100;
    SDL_Rect playerHPRect = {0, 0, 0, 0};
    SDL_Texture *playerImg = NULL;
    
    

    
    void Setplayer() { 
        player.w = playerW*1.5; 
        player.h = playerH*1.5; 
        player.x = SCREEN_WIDTH/2-player.w/2; 
        player.y = SCREEN_HEIGHT/1.2-player.h/2; 
        playerHPRect.h = 10;
    }

    void CheckBorderCollision() {
        if (player.x < 25) {
            player.x = 26;
        }
        else if (player.x + player.w + 26 >= SCREEN_WIDTH) {
            player.x = SCREEN_WIDTH - player.w -25;
        }
        if (player.y < 25) {
            player.y = 26;
        }
        else if (player.y + player.h + 26 >= SCREEN_HEIGHT) {
            player.y = SCREEN_HEIGHT - player.h -25;
        }
    }

    class Bullet {
    public:
        int bulletW, bulletH;
        SDL_Texture *bulletImg = NULL;
        SDL_Rect bullet = {0, 0, 0, 0};
        int bulletSpeed = 20;
        int aimX = 0;
        int aimY = 0;
        float deltaX = 0;
        float deltaY = 0;
        bool isFiring = false;
        int fireRotation = 0;
        int numBullet = 0;

        void SetPlayerBullet() {
            bullet.w = bulletW*1.5;
            bullet.h = bulletH*1.5;
        }

        void CheckBorderCollision() {
            if(bullet.x <= 0){
                isFiring = false;
                numBullet = 0;
            }
            else if (bullet.x + bullet.w >= SCREEN_WIDTH) {
                isFiring = false;
                numBullet = 0;
            }
            else if(bullet.y <= 0){
                isFiring = false;
                numBullet = 0;
            }
            else if (bullet.y + bullet.h >= SCREEN_HEIGHT) {
                isFiring = false;
                numBullet = 0;
            }
        }
    };

    Bullet bullet;
};


