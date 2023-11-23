#ifndef BOXMAN_WINDOW_H
#define BOXMAN_WINDOW_H
#include <SDL.h>
#include <SDL2_image/SDL_image.h>
#include "errors.h"

class Window {
public:
    Window(int width, int height);
    ~Window();
    SDL_Renderer *GetRenderer();
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool minimized;
    bool mouseFocus;
    bool keyboardFocus;
    int width;
    int height;

};

#endif //BOXMAN_WINDOW_H
