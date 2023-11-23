#include <SDL.h>
#include <SDL2_image/SDL_image.h>

#define SCREEN_WIDTH 2560
#define SCREEN_HEIGHT 1600

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL failed to initialize. SDL Error: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Window *window = SDL_CreateWindow(
            "Boxman",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH / 2,
            SCREEN_HEIGHT / 2,
            SDL_WINDOW_SHOWN
    );
    if (window == NULL) {
        printf("Window failed to initialize. SDL Error: %s\n", SDL_GetError());
        return 1;
    }
    auto screen_surface = SDL_GetWindowSurface(window);
    if (screen_surface == NULL) {
        printf("Surface failed to initialize. SDL Error: %s\n", SDL_GetError());
        return 1;
    }
    if (SDL_FillRect(screen_surface, NULL, SDL_MapRGB(screen_surface->format, 0x80, 0x80, 0x70)) < 0) {
        printf("Failed to fill rectangle. SDL Error: %s\n", SDL_GetError());
        return 1;
    }
    if (SDL_UpdateWindowSurface(window) < 0) {
        printf("Failed to update window surface. SDL Error: %s\n", SDL_GetError());
        return 1;
    }
    /* Initialize Image subsystem */
    constexpr int img_flags = IMG_INIT_PNG;
    if (!IMG_Init(IMG_INIT_PNG) & img_flags) {
        printf("SDL2_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return 2;
    }
    SDL_Surface *hero = IMG_Load("/Users/lambda/sokoban/PNG/default/Crates/crate_01.png");
    if (hero == NULL) {
        printf("Failed to load hero sprite. SDL Error: %s\n", SDL_GetError());
        return 1;
    }
    printf("%d\n", hero->format->BitsPerPixel);
    for (int i = 0; i < 3; ++i) {
        SDL_Rect r = {100 * i, 100 * i, 100, 100};
        if (SDL_BlitScaled(hero, NULL, screen_surface, &r) < 0) {
            printf("Failed to Blit surface. SDL Error: %s\n", SDL_GetError());
            return 1;
        }
    }
    if (SDL_UpdateWindowSurface(window) < 0) {
        printf("Failed to update window surface. SDL Error: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Event e;
    bool quit = false;
    /* Main game loop */
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
            }
        }
    }
    SDL_DestroyWindow(window);

    //Quit SDL subsystems
    SDL_Quit();
}
