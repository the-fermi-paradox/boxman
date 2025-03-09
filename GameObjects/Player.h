#ifndef PLAYER_H
#define PLAYER_H
#include "GameObjects/Moveable.h"
#include "Spritesheet.h"

class Player : public Moveable {
public:
    using Moveable::Moveable, Moveable::checkCollision;
    void handleEvent(const SDL_Event &e);
    void setAnimation(const SpriteSheet &sprite_sheet);
    void nextFrame();

protected:
    uint64_t frames{};
    std::string sprite_name;
    bool checkCollision(State &state) const override;
    static constexpr std::string_view ANIM_LEFT[3] = {"player_15", "player_14",
                                                      "player_16"};
    static constexpr std::string_view ANIM_RIGHT[3] = {"player_12", "player_11",
                                                       "player_13"};
    static constexpr std::string_view ANIM_UP[3] = {"player_03", "player_02",
                                                    "player_04"};
    static constexpr std::string_view ANIM_DOWN[3] = {"player_01", "player_23",
                                                      "player_24"};
};

#endif // PLAYER_H
