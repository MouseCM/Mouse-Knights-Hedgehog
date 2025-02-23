

class Mouse {
public:
    int mouseW = 0;
    int mouseH = 0;
    SDL_Rect mouse = {0, 0, 0, 0}; 
    int mouseSpeed = 10;
    int mouseHP = 100;
    SDL_Rect mouseHPRect = {0, 0, 0, 0};
    SDL_Texture *img = NULL;
};


