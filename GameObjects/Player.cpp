#include "Player.h"
#include "State.h"

void Player::setAnimation(const SpriteSheet &sprite_sheet)
{
    if (!vx && !vy) {
        if (sprite_name == ANIM_DOWN[0] || sprite_name == ANIM_DOWN[2]) {
            sprite_name = ANIM_DOWN[1];
        } else if (sprite_name == ANIM_LEFT[0] || sprite_name == ANIM_LEFT[2]) {
            sprite_name = ANIM_LEFT[1];
        } else if (sprite_name == ANIM_RIGHT[0] ||
                   sprite_name == ANIM_RIGHT[2]) {
            sprite_name = ANIM_RIGHT[1];
        } else if (sprite_name == ANIM_UP[0] || sprite_name == ANIM_UP[2]) {
            sprite_name = ANIM_UP[1];
        }
    }
    if (vx > 0) {
        sprite_name = ANIM_RIGHT[(frames % 30) / 10];
    } else if (vx < 0) {
        sprite_name = ANIM_LEFT[(frames % 30) / 10];
    } else if (vy < 0) {
        sprite_name = ANIM_UP[(frames % 30) / 10];
    } else if (vy > 0) {
        sprite_name = ANIM_DOWN[(frames % 30) / 10];
    }

    if (!sprite_name.empty()) {
        sprite = sprite_sheet.GetSpriteFromName(sprite_name);
    }
}
void Player::nextFrame() { frames++; }

void Player::handleEvent(const SDL_Event &e)
{
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_UP:
            case SDLK_k:
                vx = 0;
                vy -= speed;
                break;
            case SDLK_DOWN:
            case SDLK_j:
                vx = 0;
                vy += speed;
                break;
            case SDLK_LEFT:
            case SDLK_h:
                vy = 0;
                vx -= speed;
                break;
            case SDLK_RIGHT:
            case SDLK_l:
                vy = 0;
                vx += speed;
                break;
        }
    } else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_UP:
            case SDLK_k:
            case SDLK_DOWN:
            case SDLK_j:
                vy = 0;
                break;
            case SDLK_LEFT:
            case SDLK_h:
            case SDLK_RIGHT:
            case SDLK_l:
                vx = 0;
                break;
        }
    }
}
bool Player::checkCollision(State &state) const
{
    for (auto &object: state.dynamics) {
        if (this->checkCollision(object)) {
            object.setSpeed(this->vx, this->vy);
            object.move(state);
            return true;
        }
    }
    return Moveable::checkCollision(state);
}
