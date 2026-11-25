#include "EnemyFactory.h"
#include "Goblin.h"
#include "Slime.h"
#include "Dragon.h"
//creates all the enemys using pointers
Enemy* EnemyFactory::CreateEnemy(std::string type) {
    //creating enemys
    if (type == "goblin") return new Goblin();
    if (type == "slime") return new Slime();
    if (type == "dragon") return new Dragon();
    return nullptr;
}
