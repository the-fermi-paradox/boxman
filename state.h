#ifndef BOXMAN_STATE_H
#define BOXMAN_STATE_H
#include "gameobject.h"

class GameObject;
struct State {
  std::vector<GameObject> floors;
  std::vector<GameObject> statics;
  std::vector<GameObject> dynamics;
};

#endif // BOXMAN_STATE_H
