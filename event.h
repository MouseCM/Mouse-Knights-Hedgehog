using namespace std;

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
    bool playDown = false;
    bool exitDown = false;
    int mouseX = 0;
    int mouseY = 0;
    int curStage = 1;
    int isRetry = 0;

    SDL_Event event;

    void checkHome() {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                appIsRunning = false;
            }

            if (event.key.keysym.scancode == SDL_SCANCODE_D) {
                dDown = true;
            }

            if (event.button.button == SDL_BUTTON_LEFT) {
                mouseButtonLeftDown = true;
                SDL_GetMouseState(&mouseX, &mouseY);
                cout << mouseX << ' ' << mouseY << endl;
            }
            if (event.type == SDL_MOUSEBUTTONUP) {
                mouseButtonLeftDown = false;
            }

            // cout << mouseX << ' ' << mouseY << endl;
            
            if(mouseX >= 229 && mouseX <= 1046 && mouseY >= 185 && mouseY <= 419) {
                playDown = true;
            } 
            if(mouseX >= 496 && mouseX <= 779 && mouseY >= 468 && mouseY <= 540) {
                if(mouseButtonLeftDown) {
                    appIsRunning = false;
                    // cout << '1';
                }
            }

        }

    }

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
                if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                    appIsRunning = false;
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

    void CheckRetry() {
        if (event.button.button == SDL_BUTTON_LEFT) {
            mouseButtonLeftDown = true;
        }

        if (event.type == SDL_MOUSEBUTTONUP) {
            mouseButtonLeftDown = false;
        }

        if(mouseButtonLeftDown) {
            int x;
            int y;
            SDL_GetMouseState(&x, &y);
            // cout << x << ' ' << y << endl;
            if(x >= 540 && x <= 735 && y >= 311 && y <= 405) {
                isRetry = true;
            }
        }
    }

};