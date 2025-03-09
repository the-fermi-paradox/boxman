#include "Renderer.h"

#include "GameObjects/GameObject.h"
#include "State.h"

void Renderer::render(const GameObject &object) const
{
    sprite_sheet.RenderSprite(object.getX(), object.getY(), object.getSprite());
}
void Renderer::render(State &state)
{
    auto renderContainer = [&](auto &container) -> void {
        for (const auto &object: container) {
            this->render(object);
        }
    };
    renderContainer(state.floors);
    renderContainer(state.targets);
    renderContainer(state.statics);
    renderContainer(state.dynamics);
    render(state.player);
}
