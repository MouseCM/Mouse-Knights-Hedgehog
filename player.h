using namespace std;


class Player {
    


public:
    int playerW = 0;
    int playerH = 0;
    SDL_Rect player = {0, 0, 0, 0}; 
    int playerSpeed = 6;
    int playerHP = 100;
    SDL_Rect playerHPRect = {0, 0, 0, 0};
    SDL_Texture *playerImg = NULL;
    
    

    

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
        SDL_Rect bullet = {1, 1, 1, 1};
        int bulletSpeed = 20;
        int aimX = 0;
        int aimY = 0;
        float deltaX = 0;
        float deltaY = 0;
        bool isFiring = false;
        float angle = 0;
        int reloadTime = SDL_GetTicks64();
        int existTime = SDL_GetTicks64();
        int damage = 10;
        


        void SetPlayerBullet(SDL_Renderer *renderer) {
            bulletImg = IMG_LoadTexture(renderer, "assets/bullet.png");
            SDL_QueryTexture(bulletImg, NULL, NULL, &bulletW, &bulletH);
            bullet.w = bulletW*1.5;
            bullet.h = bulletH*1.5;
        }

        void CheckBorderCollision() {
            if(bullet.x <= 0){
                isFiring = false;
                reloadTime = SDL_GetTicks64() + 3000;
                bullet.x = 1;
                bullet.y = 1;
            }
            else if (bullet.x + bullet.w >= SCREEN_WIDTH) {
                isFiring = false;
                reloadTime = SDL_GetTicks64() + 3000;
                bullet.x = 1;
                bullet.y = 1;
            }
            else if(bullet.y <= 0){
                isFiring = false;
                reloadTime = SDL_GetTicks64() + 3000;
                bullet.x = 1;
                bullet.y = 1;
            }
            else if (bullet.y + bullet.h >= SCREEN_HEIGHT) {
                isFiring = false;
                reloadTime = SDL_GetTicks64() + 3000;
                bullet.x = 1;
                bullet.y = 1;
            }
        }

        void Move(Event &event) {
            if(isFiring) {
                bullet.x = deltaX + cos(angle) * bulletSpeed;
                bullet.y = deltaY + sin(angle) * bulletSpeed;
                deltaX += cos(angle) * bulletSpeed;
                deltaY += sin(angle) * bulletSpeed;
            }
        }

    };

    Bullet bullet;
    vector<Bullet> bullets;

    void Fire() {   
        
        cout << SDL_GetTicks64() << ' ' << bullet.reloadTime << endl;
        if(bullet.isFiring == 0 && SDL_GetTicks64() >= bullet.reloadTime) {
            // cout << '1';
            SDL_GetMouseState(&bullet.aimX, &bullet.aimY);
            bullet.deltaX = bullet.aimX - (player.x + player.w/2);
            bullet.deltaY = bullet.aimY - (player.y + player.h/2);
            bullet.angle = atan2(bullet.deltaY, bullet.deltaX);
            bullet.deltaX = player.x + player.w/2 - bullet.bullet.w/2;
            bullet.deltaY = player.y + player.h/2 - bullet.bullet.h/2;
            bullet.existTime = SDL_GetTicks64() + 5000;
            bullet.isFiring = true;
        }

        else {
            SDL_GetMouseState(&bullet.aimX, &bullet.aimY);
            bullet.deltaX = (bullet.aimX) - (bullet.bullet.x);
            bullet.deltaY = (bullet.aimY) - (bullet.bullet.y);
            bullet.angle = atan2(bullet.deltaY, bullet.deltaX);
            bullet.deltaX = bullet.bullet.x;
            bullet.deltaY = bullet.bullet.y;
        }

        if(bullet.isFiring && SDL_GetTicks64() >= bullet.existTime) {
            bullet.isFiring = false;
            bullet.reloadTime = SDL_GetTicks64() + 3000;
        }
    }

    void Setplayer(SDL_Renderer *renderer) {
        playerImg = IMG_LoadTexture(renderer, "assets/mouse.png");
	    SDL_QueryTexture(playerImg, NULL, NULL, &playerW, &playerH);
        player.w = playerW*1.5; 
        player.h = playerH*1.5;
        player.x = SCREEN_WIDTH/2-player.w/2; 
        player.y = SCREEN_HEIGHT/1.2-player.h/2; 
        playerHPRect.h = 10;
        // for(int i = 0; i < bullet.maxBullet; i++){
        //     Bullet temp;
        //     temp.SetPlayerBullet(renderer);
        //     bullets.push_back(temp);
        // }
    
    }

};


