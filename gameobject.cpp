#include "gameobject.h"
#include <ranges>

std::string GameObject::getType(int n) {
    switch (n) {
        case 0:
            return "block_03";
        case 1:
            return "ground_01";
        case 2:
            return "player_01";
        case 3:
            return "crate_01";
        case 4:
            return "environment_01";
        default:
            return "block_01";
    }
}

void GameObject::setSpeed(int x, int y) {
  vx = x;
  vy = y;
}

void GameObject::setPosition(int x, int y) {
    collider.x = x;
    collider.y = y;
}

std::string GameObject::getType() const {
    return type;
}

void GameObject::handleEvent(SDL_Event &e) {
    if (!isPlayer) return;
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
    }
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_UP:
            case SDLK_k:
                vy = 0;
                break;
            case SDLK_DOWN:
            case SDLK_j:
                vy = 0;
                break;
            case SDLK_LEFT:
            case SDLK_h:
                vx = 0;
                break;
            case SDLK_RIGHT:
            case SDLK_l:
                vx = 0;
                break;
        }
    }
}

void GameObject::setAnimation(int i) {
  if (!vx && !vy) {
    if (type == ANIM_DOWN[0] || type == ANIM_DOWN[2]) {
      type = ANIM_DOWN[1];
    }
    else if (type == ANIM_LEFT[0] || type == ANIM_LEFT[2]) {
      type = ANIM_LEFT[1];
    }
    else if (type == ANIM_RIGHT[0] || type == ANIM_RIGHT[2]) {
      type = ANIM_RIGHT[1];
    }
    else if (type == ANIM_UP[0] || type == ANIM_UP[2]) {
      type = ANIM_UP[1];
    }
  }
  if (vx > 0) {
    type = ANIM_RIGHT[(i % 30) / 10];
  }
  else if (vx < 0) {
    type = ANIM_LEFT[(i % 30) / 10];
  }
  else if (vy < 0) {
    type = ANIM_UP[(i % 30) / 10];
  }
  else if (vy > 0) {
    type = ANIM_DOWN[(i % 30) / 10];
  }
}

bool GameObject::checkCollision(const GameObject &B) {
    if (!B.collidable) return false;
    auto& A = *this;
    if (&A == &B) return false;
    if( A.getBottom() <= B.getTop())
    {
        return false;
    }

    if( A.getTop() >= B.getBottom() - 30)
    {
        return false;
    }

    if( A.getRight() <= B.getLeft() )
    {
        return false;
    }

    if( A.getLeft() >= B.getRight())
    {
        return false;
    }
    return true;
}

bool GameObject::checkCollision(State &state) {
    for (auto& v : {&state.dynamics, &state.statics}) {
      for (auto &o : *v) {
        if (&o != this && checkCollision(o)) {
          if (o.getType() == "crate_01") {
            o.setSpeed(this->vx, this->vy);
            o.move(state);
          }
          return true;
        }
      }
    }
    return false;
}

void GameObject::move(State &state) {
    collider.x += vx;
    if (collider.x < 0 || (collider.x >= level_width) || checkCollision(state)) {
        collider.x -= vx;
    }
    collider.y += vy;
    if (collider.y < 0 || (collider.y >= level_height) || checkCollision(state)) {
        collider.y -= vy;
    }
}
int GameObject::getCategory() const {
  if (this->type == "ground_01") {
    return 0;
  } else if (this->type == "environment_01" || this->type == "block_03" || this->type == "block_01") {
    return 1;
  } else if (this->type == "crate_01" || this->type == "player_01") {
    return 2;
  }
}

int GameObject::getX() const {
  return collider.x;
}
int GameObject::getY() const {
  return collider.y;
}
int GameObject::getTop() const {
  return collider.y;
}
int GameObject::getBottom() const {
  return collider.y + collider.h;
}
int GameObject::getLeft() const {
  return collider.x;
}
int GameObject::getRight() const {
  return collider.x + collider.w;
}