#include <SDL2/SDL.h>
#include <iostream>

const int SCREEN_WIDTH = 340;
const int SCREEN_HEIGHT = 480;
const int INITIAL_RADIUS = 10;
const int CIRCLE_SPEED = 2;
const int RADIUS_INCREMENT = 1;



bool initializeSDL(SDL_Window** window, SDL_Renderer** renderer) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return false;
    }

    *window = SDL_CreateWindow("Circle Drawing", 
                                SDL_WINDOWPOS_CENTERED, 
                                SDL_WINDOWPOS_CENTERED, 
                                SCREEN_WIDTH, 
                                SCREEN_HEIGHT, 
                                SDL_WINDOW_SHOWN);
    if (*window == NULL) {
        printf("Window creation failed: %s\n", SDL_GetError());
        return false;
    }

    *renderer = SDL_CreateRenderer(*window,
                                    -1, 
                                    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (*renderer == NULL) {
        printf("Renderer creation failed: %s\n", SDL_GetError());
        return false;
    }

    return true;
}



void drawCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius) {
    for (int x = -radius; x <= radius; x++) {
        for (int y = -radius; y <= radius; y++) {

                if(x*x + y*y <= radius*radius)
                    SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
        }
    }
}




int main(int argc, char* args[]) {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    if (!initializeSDL(&window, &renderer)) {
        return 1;
    }

    int circleX = SCREEN_WIDTH / 2;
    int circleY = SCREEN_HEIGHT / 2;
    int circleRadius = INITIAL_RADIUS;


    bool running = true;
    SDL_Event e;

    // DETERMINING THE MINIMUM OF MAX_RADIUS
    int MAX_RADIUS;
    if(SCREEN_HEIGHT/2 > SCREEN_WIDTH/2)
        MAX_RADIUS = SCREEN_WIDTH / 2;
    else 
        MAX_RADIUS = SCREEN_HEIGHT / 2;

    while (running) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                running = false;
                break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0,106,78, 255); 
        SDL_RenderClear(renderer);

        // Incrementing the circle's radius
        circleRadius += RADIUS_INCREMENT;
        if (circleRadius > MAX_RADIUS) {
            circleRadius = INITIAL_RADIUS;
        }

        // Draw the circle at the updated position
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); 
        drawCircle(renderer, circleX, circleY, circleRadius);

        // Present the renderer
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
