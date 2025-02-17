#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define SCALE_FACTOR 4  // To make the pixel art bigger

int main(int argc, char* argv[]) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Texture* texture = NULL;
    bool running = true;
    SDL_Event event;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return 1;
    }

    // Initialize SDL_image
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("SDL_image initialization failed: %s\n", IMG_GetError());
        SDL_Quit();
        return 1;
    }

    // Create window
    window = SDL_CreateWindow("Cute Pixel Mouse",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window creation failed: %s\n", SDL_GetError());
        goto cleanup;
    }

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer creation failed: %s\n", SDL_GetError());
        goto cleanup;
    }

    // Load image
    SDL_Surface* surface = IMG_Load("assets/mouseMain.png");
    if (!surface) {
        printf("Image loading failed: %s\n", IMG_GetError());
        goto cleanup;
    }

    // Create texture from surface
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture) {
        printf("Texture creation failed: %s\n", SDL_GetError());
        goto cleanup;
    }

    // Get texture size
    int textureWidth, textureHeight;
    SDL_QueryTexture(texture, NULL, NULL, &textureWidth, &textureHeight);

    // Scale up the image
    SDL_Rect destRect = {
        (WINDOW_WIDTH - textureWidth * SCALE_FACTOR) / 2,  // Center horizontally
        (WINDOW_HEIGHT - textureHeight * SCALE_FACTOR) / 2, // Center vertically
        textureWidth * SCALE_FACTOR,
        textureHeight * SCALE_FACTOR
    };

    // Main loop
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // White background
        SDL_RenderClear(renderer);

        // Render the mouse
        SDL_RenderCopy(renderer, texture, NULL, &destRect);
        
        // Update screen
        SDL_RenderPresent(renderer);
        
        // Small delay to prevent CPU hogging
        SDL_Delay(16);  // Approx. 60 FPS
    }

cleanup:
    if (texture) SDL_DestroyTexture(texture);
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return 0;
}