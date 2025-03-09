#include "Errors.h"
#include "Game.h"
#include "GameObjects/Player.h"
#include "Renderer.h"
#include "Spritesheet.h"
#include "Window.h"
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
    Game game(State(), sprite_sheet);
    game.nextLevel();
    const auto WinScreen = Texture(W.GetRenderer(), "sokoban/good_ending.png");
    Renderer renderer(sprite_sheet);

    /* Main game loop */
    bool game_running = true;
    SDL_Event e;
    while (!game.getGameOver() && game_running) {
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    game_running = false;
                    break;
                case SDL_KEYDOWN:
                    switch (e.key.keysym.sym) {
                        case SDLK_RETURN:
                            game.reset();
                            break;
                    }
                    break;
            }
            game.state.player.handleEvent(e);
        }
        game.advanceState();
        W.clear();
        renderer.render(game.state);
        W.present();
        const auto curr = SDL_GetTicks64();
        while (curr - SDL_GetTicks64() < 1000 / 60)
            ;
    }
    // Display the win screen
    while (game_running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT || e.type == SDL_KEYDOWN)
                game_running = false;
        }
        W.clear();
        WinScreen.Render(nullptr, nullptr);
        W.present();
        const auto curr = SDL_GetTicks64();
        while (curr - SDL_GetTicks64() < 1000 / 60)
            ;
    }

    IMG_Quit();
    SDL_Quit();
}
