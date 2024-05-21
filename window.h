#ifndef BOXMAN_WINDOW_H
#define BOXMAN_WINDOW_H
#include <SDL.h>
#include <SDL2_image/SDL_image.h>
#include "errors.h"

class Window {
public:
    Window(int width, int height, int lWidth=640, int lHeight=640);
    ~Window();
    SDL_Renderer *GetRenderer();
    void present();
    void clear() {
        SDL_RenderClear(renderer);
    }

    int getLWidth() const;
    int getLHeight() const;
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool minimized;
    bool mouseFocus;
    bool keyboardFocus;
    int lWidth;
    int lHeight;
    int width;
    int height;

};

#endif //BOXMAN_WINDOW_H
