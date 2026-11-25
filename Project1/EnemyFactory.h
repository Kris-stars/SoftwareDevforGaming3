#pragma once
#include "Enemy.h"
#include <string>
//Factory design for enemys
class EnemyFactory {
public:
    static Enemy* CreateEnemy(std::string type);
};
