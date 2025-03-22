class Stage {
public:
    SDL_Rect home = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_Texture *homeImg = NULL;

    SDL_Rect background = {0, 0, 2560, 1440};
    SDL_Texture *backgroundImg = NULL;

    SDL_Rect portal = {STAGE_WIDTH/2 -20, STAGE_HEIGHT/2 - 40, 40, 80};
    SDL_Texture *portalIMG = NULL;

    // SDL_Rect topBorder = {0, 0, STAGE_WIDTH, 25};
    // SDL_Rect bottomBorder = {0, STAGE_HEIGHT - 25, STAGE_WIDTH, 25};
    // SDL_Rect leftBorder = {0, 0, 25, STAGE_HEIGHT};
    // SDL_Rect rightBorder = {STAGE_WIDTH - 25, 0, 25, STAGE_HEIGHT};

    // SDL_Texture *borderTextureTop = NULL;
    // SDL_Texture *borderTextureLeft = NULL;
    // SDL_Texture *borderTextureRight = NULL;
    // SDL_Texture *borderTextureBottom = NULL;


    SDL_Rect retry = {STAGE_WIDTH/2-100, STAGE_HEIGHT/2-50, 200, 100};
    SDL_Texture *retryImg = NULL;

    SDL_Texture *box = NULL;

    

    void SetHome(SDL_Renderer *renderer) {
        homeImg = IMG_LoadTexture(renderer, "assets/home.png");
    }

    void SetPortal(SDL_Renderer *renderer) {
        portalIMG = IMG_LoadTexture(renderer, "assets/portal.png");
    }

    void SetStage(SDL_Renderer *renderer) {
        background = {-INIT_X, -INIT_Y, STAGE_WIDTH, STAGE_HEIGHT};

        backgroundImg = IMG_LoadTexture(renderer, "assets/background.png");

        // borderTextureTop = IMG_LoadTexture(renderer, "assets/border/top.jpg");
        // borderTextureLeft = IMG_LoadTexture(renderer, "assets/border/left.jpg");
        // borderTextureRight = IMG_LoadTexture(renderer, "assets/border/right.jpg");
        // borderTextureBottom = IMG_LoadTexture(renderer, "assets/border/bottom.jpg");

        retry = {STAGE_WIDTH/2-100-INIT_X, STAGE_HEIGHT/2-50-INIT_Y, 200, 100};
        portal = {STAGE_WIDTH/2 -20 - INIT_X, STAGE_HEIGHT/2 - 40 - INIT_Y, 40, 80};

        retryImg = IMG_LoadTexture(renderer, "assets/retry.png");
    }

    void SetStage3(SDL_Renderer *renderer) {
        backgroundImg = IMG_LoadTexture(renderer, "assets/background.png");

        // borderTextureTop = IMG_LoadTexture(renderer, "assets/border/top.jpg");
        // borderTextureLeft = IMG_LoadTexture(renderer, "assets/border/left.jpg");
        // borderTextureRight = IMG_LoadTexture(renderer, "assets/border/right.jpg");
        // borderTextureBottom = IMG_LoadTexture(renderer, "assets/border/bottom.jpg");

        retryImg = IMG_LoadTexture(renderer, "assets/retry.png");
        box = IMG_LoadTexture(renderer, "assets/box.png");
    }
  
};