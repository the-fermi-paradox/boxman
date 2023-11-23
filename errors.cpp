#include "errors.h"
void ErrorOut(const char *s, int error_code) {
    if constexpr (ERROR_LOGGING)
        printf("%s. SDL_Error: %s\n", s, SDL_GetError());
    exit(error_code);
}
