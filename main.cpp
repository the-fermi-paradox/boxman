#include "window.h"
#include "errors.h"

static constexpr int SCREEN_WIDTH     = 2560;
static constexpr int SCREEN_HEIGHT    = 1600;


class Texture {
public:
    Texture() {
        texture = nullptr;
    }
    Texture(SDL_Renderer *renderer, const char *path) {
        texture = IMG_LoadTexture(renderer, path);
        if (texture == nullptr)
            ErrorOut("Failed to load texture");
    }
    ~Texture() {
        if (texture) SDL_DestroyTexture(texture);
    }
    SDL_Texture *texture;
};

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        ErrorOut("Failed to initialize video subsystem");
    }
    Window W(1000, 500);
    SDL_Renderer *renderer = W.GetRenderer();
    SDL_RenderClear(renderer);

    /* Initialize Image subsystem */
    constexpr int img_flags = IMG_INIT_PNG;
    if (!IMG_Init(IMG_INIT_PNG) & img_flags) {
        ErrorOut("SDL2_image could not initialize! SDL_image Error: %s\n");
    }
    Texture crate1(renderer, "/Users/lambda/sokoban/PNG/default/Crates/crate_01.png");
    for (int i = 0; i < 3; ++i) {
        SDL_RenderCopy(renderer, crate1.texture, NULL, NULL);
    }
    SDL_RenderPresent(renderer);
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

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}
