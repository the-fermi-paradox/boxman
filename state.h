#ifndef BOXMAN_STATE_H
#define BOXMAN_STATE_H

class GameObject;
struct State {
    std::vector<GameObject> floors;
    std::vector<GameObject> statics;
    std::vector<GameObject> dynamics;
};

#endif // BOXMAN_STATE_H
