#include "Errors.h"
#include <SDL2/SDL.h>
void ErrorOut(const char *s, const int error_code)
{
    if constexpr (ERROR_LOGGING)
        printf("%s. SDL_Error: %s\n", s, SDL_GetError());
    exit(error_code);
}
void ErrorWithoutExit(const char *s)
{
    if constexpr (ERROR_LOGGING)
        printf("%s. SDL_Error: %s\n", s, SDL_GetError());
}
