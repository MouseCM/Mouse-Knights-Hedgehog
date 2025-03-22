using namespace std;


class Player {
    


public:
    int playerW = 0;
    int playerH = 0;
    SDL_Rect player = {0, 0, 0, 0}; 
    int playerSpeed = 5;
    int playerHP = 100;
    SDL_Rect playerHPRect = {0, 0, 0, 0};
    SDL_Texture *playerImg = NULL;
    
    

    

    // void CheckBorderCollision() {
        // if (player.x < ) {
        //     player.x = 26;
        // }
        // else if (player.x + player.w + 26 >= STAGE_WIDTH) {
        //     player.x = STAGE_WIDTH - player.w -25;
        // }
        // if (player.y < 25) {
        //     player.y = 26;
        // }
        // else if (player.y + player.h + 26 >= STAGE_HEIGHT) {
        //     player.y = STAGE_HEIGHT - player.h -25;
        // }
    // }

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
        int rectW;
        int rectH;
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
        int existTime = 5000;
        int damage = 10;
        bool isLose = false;
        int preX;
        int preY;


        void SetPlayerBullet(SDL_Renderer *renderer) {
            bulletImg = IMG_LoadTexture(renderer, "assets/bullet.png");
            SDL_QueryTexture(bulletImg, NULL, NULL, &rectW, &rectH);
            bullet.w = rectW * 1.5;
            bullet.h = rectH * 1.5;
        }

        

        // void CheckBorderCollision() {
        //     if(bullet.x <= 25){
        //         // deltaX = 26;
        //         // angle = M_PI - angle;
        //         isFiring = false;
        //     }
        //     else if (bullet.x + bullet.w + 25 >= STAGE_WIDTH) {
        //         // deltaX = STAGE_WIDTH-bullet.w-26;
        //         // angle = M_PI - angle;
        //         isFiring = false;
        //     }
        //     else if(bullet.y <= 25){
        //         // deltaY = 26;
        //         // angle = -angle;
        //         isFiring = false;
        //     }
        //     else if (bullet.y + bullet.h + 25 >= STAGE_HEIGHT) {
        //         // deltaY = STAGE_HEIGHT-bullet.h-26;
        //         // angle = -angle;
        //         isFiring = false;
        //     }
        // }

        void CheckObjectCollision(SDL_Rect object) {
            // if(bullet.x >= object.x && bullet.x <= object.x+object.w && bullet.y >= object.y && bullet.y <= object.y+object.h) {
            //     while(bullet.x >= object.x && bullet.x <= object.x+object.w && bullet.y >= object.y && bullet.y <= object.y+object.h) {
            //         preX = deltaX - cos(angle) * speed;
            //         preY = deltaY - sin(angle) * speed;
            //         deltaX -= cos(angle) * speed;
            //         deltaY -= sin(angle) *speed;
            //         bullet.x = deltaX;
            //         bullet.y = deltaY;
            //     }

            //     if(preX < object.x) {
            //         angle = M_PI - angle;
            //         deltaX = object.x-1;
            //     }
            //     else if(preX > object.x + object.w) {
            //         angle = M_PI - angle;
            //         deltaX = object.x + object.w+1;
            //     }
            //     else if(preY < object.y) {
            //         angle = -angle;
            //         deltaY = object.y-1;
            //     }
            //     else if(preY > object.y + object.h){
            //         angle = -angle;
            //         deltaY = object.y+object.h+1;
            //     }
            // }
         }

        void Move(Event &event) {
            // if(isFiring && SDL_GetTicks64() >= existTime) {
            //     isFiring = false;
            //     isLose = true;
            // }

            if(isFiring) {
                bullet.x = deltaX;
                bullet.y = deltaY;
                deltaX += cos(angle) * speed;
                deltaY += sin(angle) * speed;
            }

            // cout << rotateX << ' ' << rotateY << endl;
            // cout << bullet.x << ' ' << bullet.y << endl;
            // cout << bullet.w << ' ' << bullet.h << endl;
        }
    };

    Bullet bullet;

    // void Fire() {   
        
    //     if(bullet.isFiring == 0 && bullet.isLose == false) {
            // SDL_GetMouseState(&bullet.aimX, &bullet.aimY);
            // bullet.deltaX = bullet.aimX - (player.x + player.w/2);
            // bullet.deltaY = bullet.aimY - (player.y + player.h/2);
            // bullet.angle = atan2(bullet.deltaY, bullet.deltaX);
            // bullet.deltaX = player.x + player.w/2 - bullet.bullet.w/2;
            // bullet.deltaY = player.y + player.h/2 - bullet.bullet.h/2;
            // // bullet.existTime = SDL_GetTicks64() + 1000;
            // bullet.isFiring = true;
    //     }

    //     // cout << SDL_GetTicks64() << ' ' << bullet.existTime << endl;
        
    // }

    void Setplayer(SDL_Renderer *renderer) {
        playerImg = IMG_LoadTexture(renderer, "assets/mouse.png");
	    SDL_QueryTexture(playerImg, NULL, NULL, &playerW, &playerH);
        player.w = playerW*1.5; 
        player.h = playerH*1.5;
        player.x = SCREEN_WIDTH/2-player.w/2; 
        player.y = SCREEN_HEIGHT/2-player.h/2; 
        // playerHPRect.h = 40;

        // for(int i = 0; i < bullet.maxBullet; i++){
        //     Bullet temp;
        //     temp.SetPlayerBullet(renderer);
        //     bullets.push_back(temp);
        // }
    }

};


