#pragma once
#include "Enemy.h"
//base stats for dragon
class Dragon : public Enemy {
private:
    bool useFireNext;
public:
    Dragon();
    int Attack() override;
};
