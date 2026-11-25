#pragma once
#include "Enemy.h"
//slime base
class Slime : public Enemy {
public:
    Slime();
    int Attack() override;
};
