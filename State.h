#ifndef BOXMAN_STATE_H
#define BOXMAN_STATE_H
#include <vector>
#include "GameObjects/Crate.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Moveable.h"
#include "GameObjects/Obstacle.h"
#include "GameObjects/Player.h"
#include "GameObjects/Target.h"

class Crate;
class Moveable;

class State {
public:
    std::vector<GameObject> floors;
    std::vector<Obstacle> statics;
    std::vector<Crate> dynamics;
    std::vector<Target> targets;
    Player player;
    bool won{};
};

#endif // BOXMAN_STATE_H
