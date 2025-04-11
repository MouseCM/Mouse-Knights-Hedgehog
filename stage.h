class Stage {
public:
    SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

    SDL_Rect home = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_Texture *homeImg = NULL;

    SDL_Rect background = {0, 0, 2560, 1440};
    SDL_Texture *backgroundImg = NULL;

    int animated = 0;
    int animationPortalTime = SDL_GetTicks64()-200;
    SDL_Rect animationPortal = {0, 0, 242, 484};
    SDL_Rect portal = {STAGE_WIDTH/2 -20, STAGE_HEIGHT/2 - 40, 40, 80};
    SDL_Texture *portalIMG = NULL;

    SDL_Rect end = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_Texture *endImg = NULL;

    SDL_Rect retry = {0, 0, 0, 0};
    SDL_Texture *retryImg = NULL;

    SDL_Rect lose = {0, 0, 0, 0};
    SDL_Texture *loseImg = NULL;


    

    void SetHome(SDL_Renderer *renderer) {
        homeImg = IMG_LoadTexture(renderer, "assets/home.png");
    }

    void SetPortal(SDL_Renderer *renderer) {
        animationPortal = {15, 1, 242, 490};
        portal = {STAGE_WIDTH/2 -30 - INIT_X, STAGE_HEIGHT/2 - 60 - INIT_Y, 60, 120};
        portalIMG = IMG_LoadTexture(renderer, "assets/portal.png");
        animationPortalTime = SDL_GetTicks64()-200;
    }

    void SetStage(SDL_Renderer *renderer, string curStage) {
        camera = {INIT_X, INIT_Y, SCREEN_WIDTH, SCREEN_HEIGHT};
        background = {-camera.x, -camera.y, STAGE_WIDTH, STAGE_HEIGHT};

        string temp = "assets/stage" + curStage + ".png";
        const char* stage = temp.c_str();
        backgroundImg = IMG_LoadTexture(renderer, stage);


        retry = {SCREEN_WIDTH/2-100, SCREEN_HEIGHT/2-50+200, 200, 100};
        retryImg = IMG_LoadTexture(renderer, "assets/retry.png");

        lose = {SCREEN_WIDTH/2-138, SCREEN_HEIGHT/2-54-200, 276, 108};
        loseImg = IMG_LoadTexture(renderer, "assets/lose.png");
    }

    void SetEnd(SDL_Renderer *renderer) {
        end = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        endImg = IMG_LoadTexture(renderer, "assets/end.png");
    }
  
};