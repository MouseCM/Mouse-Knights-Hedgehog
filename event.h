using namespace std;

class Event {



public:
    bool appIsRunning = true;   
    bool wDown = false;
    bool aDown = false;
    bool sDown = false;
    bool dDown = false;
    bool mouseButtonDown = false;
    bool mouseButtonLeftDown = false;
    bool isNewGame = false;
    bool isContinue = false;
    bool exitDown = false;
    int mouseX = 0;
    int mouseY = 0;
    int curStage = 0;
    bool isRetry = 0;
    bool isLose = false;
    // bool isPaused = false;


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
            }
            if (event.type == SDL_MOUSEBUTTONUP) {
                mouseButtonLeftDown = false;
            }

            // cout << mouseX << ' ' << mouseY << endl;
            
            if(mouseX >= 373 && mouseX <= 906 && mouseY >= 245 && mouseY <= 398) {
                isNewGame = true;
            } 
            if(mouseX >= 425 && mouseX <= 855 && mouseY >= 424 && mouseY <= 549) {
                isContinue = true;
            }
            if(mouseX >= 425 && mouseX <= 855 && mouseY >= 575 && mouseY <= 659) {
                appIsRunning = false;
            }

        }

    }

    void CheckEvent() {
        while (SDL_PollEvent(&event)) {
            // Handle each specific event
            if (event.type == SDL_QUIT) {
                appIsRunning = false;
            }

            if(isLose) {
                wDown = false;
                aDown = false;
                sDown = false;
                dDown = false;
                mouseButtonDown = false;
                mouseButtonLeftDown = false;
                if (event.button.button == SDL_BUTTON_LEFT) {
                    mouseButtonLeftDown = true;
                }
        
                if (event.type == SDL_MOUSEBUTTONUP) {
                    mouseButtonLeftDown = false;
                }
        
                // cout << "SDfsdfsafda" << mouseButtonLeftDown << endl;
                if(mouseButtonLeftDown) {
                    int x;
                    int y;
                    SDL_GetMouseState(&x, &y);
                    // cout << x << ' ' << y << endl;
                    if(x >= 540 && x <= 735 && y >= 511 && y <= 605) {
                        isRetry = true;
                    }
                }
            }
            else {
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
    }


    void CheckEnd() {
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
            }
            if (event.type == SDL_MOUSEBUTTONUP) {
                mouseButtonLeftDown = false;
            }

            // cout << mouseX << ' ' << mouseY << endl;
            
            if(mouseX >= 417 && mouseX <= 862 && mouseY >= 507 && mouseY <= 618) {
                isNewGame = true;
            } 

            if(mouseX >= 492 && mouseX <= 788 && mouseY >= 629 && mouseY <= 714) {
                appIsRunning = false;
            }

        }
    }

};