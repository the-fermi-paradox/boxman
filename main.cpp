#include "window.h"
#include "errors.h"
#include "texture.h"

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        ErrorOut("Failed to initialize video subsystem");
    }

    constexpr int img_flags = IMG_INIT_PNG;
    if (!IMG_Init(IMG_INIT_PNG) & img_flags) {
        ErrorOut("SDL2_image could not initialize!");
    }

    Window W(1000, 500);
    SDL_Renderer *renderer = W.GetRenderer();
    Texture crate1(renderer, "/Users/lambda/sokoban/PNG/default/Crates/crate_01.png");
    for (int i = 0; i < 3; ++i) {
        SDL_Rect r = {i * 100, 0, 100, 100};
        SDL_RenderCopy(renderer, crate1.texture, nullptr, &r);
    }
    SDL_Event e;
    bool game_running = true;
    /* Main game loop */
    while (game_running) {
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    game_running = false;
                    break;
            }
        }
    }

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}
