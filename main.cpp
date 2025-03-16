#include <SDL2/SDL.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <cargs.h>
#include <filesystem>
#include "Errors.h"
#include "Game.h"
#include "GameObjects/Player.h"
#include "Renderer.h"
#include "Spritesheet.h"
#include "Window.h"
constexpr int TILE_WIDTH = 64;
constexpr int TILE_HEIGHT = 64;

static cag_option options[] = {{.identifier = 'l',
                                .access_letters = "l",
                                .access_name = "key",
                                .value_name = "VALUE",
                                .description = "Specify a level to start from"},

                               {.identifier = 'h',
                                .access_letters = "h",
                                .access_name = "help",
                                .description = "Shows the command help"}};

int main(int argc, char **argv)
{
    std::string value;
    cag_option_context context;
    cag_option_init(&context, options, std::size(options), argc, argv);
    while (cag_option_fetch(&context)) {
        switch (cag_option_get_identifier(&context)) {
            case 'l':
                value = cag_option_get_value(&context);
                break;
            case 'h':
                printf("Usage: cargsdemo [OPTION]...\n");
                printf("Demonstrates the cargs library.\n\n");
                cag_option_print(options, std::size(options), stdout);
                printf("\nNote that all formatting is done by cargs.\n");
                return EXIT_SUCCESS;
            case '?':
            default:
                cag_option_print_error(&context, stdout);
                break;
        }
    }
    int level = !value.empty() ? std::stoi(value) : 1;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        ErrorOut("Failed to initialize video subsystem");
    }
    if (!IMG_Init(IMG_INIT_PNG)) {
        ErrorOut("SDL2_image could not initialize!");
    }

    if (constexpr uint64_t audio_flags = MIX_INIT_MP3;
        (Mix_Init(audio_flags) & audio_flags) != audio_flags) {
        ErrorOut("SDL2_mixer could not initialize!");
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        ErrorOut("SDL2_mixer could not open audio!");
        return -1;
    }

    Mix_Music *music =
            Mix_LoadMUS(std::filesystem::absolute("music/puzzle.mp3").c_str());
    if (!music) {
        ErrorOut("Failed to load music!");
    } else {
        Mix_PlayMusic(music, -1); // Loop indefinitely
    }

    const Window W(1000, 1000);
    SpriteSheet sprite_sheet(W.GetRenderer(),
                             "sokoban/Spritesheet/spritesheet.png",
                             "sokoban/Spritesheet/spritesheet.json");
    Game game(State(), sprite_sheet);
    game.gotoLevel(level);
    const auto WinScreen = Texture(W.GetRenderer(), "sokoban/good_ending.png");
    Renderer renderer(sprite_sheet);

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
    Mix_FreeMusic(music);
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}
