#ifndef TARGET_H
#define TARGET_H
#include "GameObjects/GameObject.h"

class Target : public GameObject {
public:
    using GameObject::GameObject;
    void setFilled(bool value);
    [[nodiscard]] bool getFilled() const;

protected:
    bool filled = false;
};

#endif // TARGET_H
