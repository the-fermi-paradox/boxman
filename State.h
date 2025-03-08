#ifndef BOXMAN_STATE_H
#define BOXMAN_STATE_H
#include "GameObjects/GameObject.h"
#include "GameObjects/Moveable.h"
#include "GameObjects/Crate.h"
#include "GameObjects/Obstacle.h"
#include "GameObjects/Target.h"

class Crate;
class Moveable;

class State {
public:
    std::vector<GameObject> floors;
    std::vector<Obstacle> statics;
    std::vector<Crate> dynamics;
    std::vector<Target> targets;
};

#endif // BOXMAN_STATE_H
