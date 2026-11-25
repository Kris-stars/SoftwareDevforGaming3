#pragma once
#include "Enemy.h"
//Goblin base
class Goblin : public Enemy {
public:
    Goblin();
    int Attack() override;
};
