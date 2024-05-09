#include <SDL2/SDL.h>
#include <stdio.h>
#include<math.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int INITIAL_RADIUS = 10;
const int CIRCLE_SPEED = 2;
const int INCREMENT = 1;



bool initializeSDL(SDL_Window** window, SDL_Renderer** renderer) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return false;
    }

    *window = SDL_CreateWindow("Collision Between Two Circle", 
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

int main(int argc, char* args[])
 {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    if (!initializeSDL(&window, &renderer)) {
        return 1;
    }

    int circle1x = 40;
    int circle1y = 250;
    int circle1r = 40;

    int circle2x = 250;
    int circle2y = 450;
    int circle2r = 40;

    SDL_Event e;
    bool gameisrunning = true;

    while(gameisrunning)
    {
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
            {
                gameisrunning = false;
                break;
            }
            if(e.type == SDL_KEYDOWN)
            {
                if(e.key.keysym.sym == SDLK_UP) 
                {
                    if(circle2y - 10 >= circle2r) circle2y -= 10;
                }

                else if(e.key.keysym.sym == SDLK_DOWN) 
                {
                    if(circle2y + 10 <= 500 - circle2r) circle2y += 10;
                }

                else if(e.key.keysym.sym == SDLK_LEFT) 
                {
                    if(circle2x - 10 >= circle2r) circle2x -= 10;
                }

                else if(e.key.keysym.sym == SDLK_RIGHT) 
                {
                    if(circle2x + 10 >= circle2r) circle2x += 10;
                }
                else break;
            }
        }

        circle1x += INCREMENT;
        if(circle1x > SCREEN_WIDTH - 40) circle1x = 40;

        int dx = circle1x - circle2x;
        int dy = circle1y - circle2y;
        int distance = sqrt(dx * dx + dy * dy);
        int total_radius = circle1r + circle2r;
        int r;

        bool f=0;
        if(distance < total_radius)
        {
            r = 0;
            f=1;
        }
        else{
            r = 255;
        }

        SDL_SetRenderDrawColor(renderer,0, 106, 78, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, r, 0, 0, 255);

        drawCircle(renderer, circle1x, circle1y, circle1r);

        SDL_SetRenderDrawColor(renderer, 0, 0, r, 255);

        drawCircle(renderer, circle2x, circle2y, circle2r);

        SDL_RenderPresent(renderer);

        if(f)
        {
            circle1x = 40;
            circle1y = 250;
            circle1r = 40;
            circle2x = 250;
            circle2y = 450;
            circle2r = 40;
        }

        

    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}