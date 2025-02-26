
class Player {
    


public:
    int playerW = 0;
    int playerH = 0;
    SDL_Rect player = {0, 0, 0, 0}; 
    int playerSpeed = 10;
    int playerHP = 100;
    SDL_Rect playerHPRect = {0, 0, 0, 0};
    SDL_Texture *playerImg = NULL;
    
    

    
    void Setplayer(SDL_Renderer *renderer) { 
        playerImg = IMG_LoadTexture(renderer, "assets/mouse.png");
	    SDL_QueryTexture(playerImg, NULL, NULL, &playerW, &playerH);  
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

    void Move(Event &event) {
        if (event.wDown) {
            player.y -= playerSpeed;
        }
        if (event.aDown) {
            player.x -= playerSpeed;
        }
        if (event.sDown) {
            player.y += playerSpeed;
        }
        if (event.dDown) {
            player.x += playerSpeed;
        }
    }



    class Bullet {
    public:
        int bulletW;
        int bulletH;
        SDL_Texture *bulletImg = NULL;
        SDL_Rect bullet = {0, 0, 0, 0};
        int bulletSpeed = 20;
        int aimX = 0;
        int aimY = 0;
        float deltaX = 0;
        float deltaY = 0;
        bool isFiring = false;
        int numBullet = 0;
        float angle = 0;


        void SetPlayerBullet(SDL_Renderer *renderer) {
            bulletImg = IMG_LoadTexture(renderer, "assets/bullet.png");
            SDL_QueryTexture(bulletImg, NULL, NULL, &bulletW, &bulletH);
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

        void Move(Event &event) {
            if(isFiring && numBullet >= 1){
                bullet.x = deltaX + cos(angle) * bulletSpeed;
                bullet.y = deltaY + sin(angle) * bulletSpeed;
                deltaX += cos(angle) * bulletSpeed;
                deltaY += sin(angle) * bulletSpeed;
            }
        }

    };

    Bullet bullet;
};


