#ifndef RENDERER_H
#define RENDERER_H
#include "GameObjects/GameObject.h"
#include "Spritesheet.h"
#include "State.h"

class Renderer {
public:
    explicit Renderer(SpriteSheet &sprite_sheet) : sprite_sheet(sprite_sheet) {}
    void render(State &state);

private:
    SpriteSheet &sprite_sheet;
    void render(const GameObject &object) const;
};

#endif // RENDERER_H
