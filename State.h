#ifndef BOXMAN_STATE_H
#define BOXMAN_STATE_H
#include "GameObjects/GameObject.h"
#include "GameObjects/Moveable.h"
#include "GameObjects/Obstacle.h"
#include "GameObjects/Target.h"

class Moveable;

struct State {
    std::vector<GameObject> floors;
    std::vector<Obstacle> statics;
    std::vector<Moveable> dynamics;
    std::vector<Target> targets;
};

#endif // BOXMAN_STATE_H
