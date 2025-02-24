class Event {



public:
    bool appIsRunning = true;   
    bool wDown = false;
    bool aDown = false;
    bool sDown = false;
    bool dDown = false;
    bool upArrowDown = false;
    bool downArrowDown = false;
    bool leftArrowDown = false;
    bool rightArrowDown = false;
    bool mouseButtonDown = false;
    bool mouseButtonLeftDown = false;
    SDL_Event event;

    void CheckEvent() {
        while (SDL_PollEvent(&event)) {
            // Handle each specific event
            if (event.type == SDL_QUIT) {
                appIsRunning = false;
            }


            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                    appIsRunning = false;
                }
                if (event.key.keysym.scancode == SDL_SCANCODE_W) {
                    wDown = true;
                }
                if (event.key.keysym.scancode == SDL_SCANCODE_A) {
                    aDown = true;
                }
                if (event.key.keysym.scancode == SDL_SCANCODE_S) {
                    sDown = true;
                }
                if (event.key.keysym.scancode == SDL_SCANCODE_D) {
                    dDown = true;
                }
            
            }
            else if (event.type == SDL_KEYUP) {
                if (event.key.keysym.scancode == SDL_SCANCODE_W) {
                    wDown = false;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_A) {
                    aDown = false;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_S) {
                    sDown = false;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_D) {
                    dDown = false;
                }

            }

            
            if (event.button.button == SDL_BUTTON_LEFT) {
                mouseButtonLeftDown = true;
            }
            if (event.type == SDL_MOUSEBUTTONUP) {
                mouseButtonLeftDown = false;
            }
            
            
            
        }
    }

};