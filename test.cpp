#include <SDL.h>
#include <iostream>

const int WINDOW_WIDTH = 100;   // Now the window is 100x100
const int WINDOW_HEIGHT = 100;
const int IMAGE_WIDTH = 1000;   // Full image size is 1000x400
const int IMAGE_HEIGHT = 400;

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Create window - now just 100x100
    SDL_Window* window = SDL_CreateWindow(
        "SDL2 Viewport Example",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    // Create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Create a large surface for the full image (1000x400)
    SDL_Surface* imageSurface = SDL_CreateRGBSurface(0, IMAGE_WIDTH, IMAGE_HEIGHT, 32, 0, 0, 0, 0);
    if (!imageSurface) {
        std::cerr << "Failed to create surface! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Fill the image with a gradient for demonstration purposes
    SDL_LockSurface(imageSurface);
    Uint32* pixels = static_cast<Uint32*>(imageSurface->pixels);
    for (int y = 0; y < IMAGE_HEIGHT; y++) {
        for (int x = 0; x < IMAGE_WIDTH; x++) {
            Uint8 r = static_cast<Uint8>((x * 255) / IMAGE_WIDTH);
            Uint8 g = static_cast<Uint8>((y * 255) / IMAGE_HEIGHT);
            Uint8 b = 128;
            pixels[y * (imageSurface->pitch / 4) + x] = SDL_MapRGB(imageSurface->format, r, g, b);
        }
    }
    SDL_UnlockSurface(imageSurface);

    // Create texture from surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    SDL_FreeSurface(imageSurface);
    if (!texture) {
        std::cerr << "Failed to create texture! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Variables for viewport position (position within the large 1000x400 image)
    int viewportX = 0;
    int viewportY = 0;
    bool quit = false;
    SDL_Event e;

    // Main loop
    while (!quit) {
        // Handle events
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    // Move viewport with arrow keys
                    case SDLK_LEFT:
                        viewportX = std::max(0, viewportX - 10);
                        break;
                    case SDLK_RIGHT:
                        viewportX = std::min(IMAGE_WIDTH - WINDOW_WIDTH, viewportX + 10);
                        break;
                    case SDLK_UP:
                        viewportY = std::max(0, viewportY - 10);
                        break;
                    case SDLK_DOWN:
                        viewportY = std::min(IMAGE_HEIGHT - WINDOW_HEIGHT, viewportY + 10);
                        break;
                }
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Render only the viewport portion of the image
        SDL_Rect sourceRect = {viewportX, viewportY, WINDOW_WIDTH, WINDOW_HEIGHT};
        SDL_Rect destRect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
        SDL_RenderCopy(renderer, texture, &sourceRect, &destRect);

        // Display current viewport position
        std::cout << "Viewport Position: (" << viewportX << ", " << viewportY << ")" << std::endl;

        // Present rendered content
        SDL_RenderPresent(renderer);

        // Cap to 60 FPS
        SDL_Delay(16);
    }

    // Cleanup and exit
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}