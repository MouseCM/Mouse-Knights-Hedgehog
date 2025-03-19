class Stage {
public:
    SDL_Rect home = {0, 0, SCREEN_HEIGHT, SCREEN_WIDTH};
    SDL_Texture *homeImg = NULL;

    SDL_Rect background = {25, 25, SCREEN_WIDTH-50, SCREEN_HEIGHT-50};
    SDL_Texture *backgroundImg = NULL;

    SDL_Rect portal = {SCREEN_WIDTH/2 -20, SCREEN_HEIGHT/2 - 40, 40, 80};
    SDL_Texture *portalIMG = NULL;

    SDL_Rect topBorder = {0, 0, SCREEN_WIDTH, 25};
    SDL_Rect bottomBorder = {0, SCREEN_HEIGHT - 25, SCREEN_WIDTH, 25};
    SDL_Rect leftBorder = {0, 0, 25, SCREEN_HEIGHT};
    SDL_Rect rightBorder = {SCREEN_WIDTH - 25, 0, 25, SCREEN_HEIGHT};

    SDL_Texture *borderTextureTop = NULL;
    SDL_Texture *borderTextureLeft = NULL;
    SDL_Texture *borderTextureRight = NULL;
    SDL_Texture *borderTextureBottom = NULL;


    SDL_Rect retry = {SCREEN_WIDTH/2-100, SCREEN_HEIGHT/2-50, 200, 100};
    SDL_Texture *retryImg = NULL;

    

    void SetHome(SDL_Renderer *renderer) {
        homeImg = IMG_LoadTexture(renderer, "assets/home.png");
    }

    void SetPortal(SDL_Renderer *renderer) {
        portalIMG = IMG_LoadTexture(renderer, "assets/portal.png");
    }

    void SetStage(SDL_Renderer *renderer) {
        backgroundImg = IMG_LoadTexture(renderer, "assets/background.jpg");

        borderTextureTop = IMG_LoadTexture(renderer, "assets/border/top.jpg");
        borderTextureLeft = IMG_LoadTexture(renderer, "assets/border/left.jpg");
        borderTextureRight = IMG_LoadTexture(renderer, "assets/border/right.jpg");
        borderTextureBottom = IMG_LoadTexture(renderer, "assets/border/bottom.jpg");

        retryImg = IMG_LoadTexture(renderer, "assets/retry.png");
    }

};