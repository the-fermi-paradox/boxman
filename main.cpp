#include <__format/format_functions.h>
#include <level.h>

#include "errors.h"
#include "spritesheet.h"
#include "texture.h"
#include "window.h"
using json = nlohmann::json;
constexpr int TILE_WIDTH = 64;
constexpr int TILE_HEIGHT = 64;

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        ErrorOut("Failed to initialize video subsystem");
    }

    constexpr int img_flags = IMG_INIT_PNG;
    if ((!IMG_Init(IMG_INIT_PNG)) & img_flags) {
        ErrorOut("SDL2_image could not initialize!");
    }

    const Window W(1000, 1000);
    SpriteSheet sprite_sheet(W.GetRenderer(),
                             "sokoban/Spritesheet/spritesheet.png",
                             "sokoban/Spritesheet/spritesheet.json");
    Level level("level.json", sprite_sheet);
    GameObject &player = level.getPlayer();

    /* Main game loop */
    bool game_running = true;
    int frames = 0;
    SDL_Event e;
    while (game_running) {
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    game_running = false;
                    break;
                case SDL_KEYDOWN:
                    switch (e.key.keysym.sym) {
                        case SDLK_RETURN:
                            level.reset();
                    }
            }
            player.handleEvent(e);
        }
        player.move(level.state);
        player.setAnimation(frames);
        W.clear();
        level.drawLevel(sprite_sheet);
        W.present();
        SDL_WINDOWPOS_UNDEFINED;
        auto curr = SDL_GetTicks64();
        while (curr - SDL_GetTicks64() < 1000 / 60) {
        }
        ++frames;
    }

    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}
