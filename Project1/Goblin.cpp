#include "Goblin.h"
#include <iostream>
#include <random>
//goblin base stats
Goblin::Goblin() : Enemy("Goblin", 40) {}
int Goblin::Attack() {
    //random damage from 5 to 10
    std::random_device random;
    int damage = 5 + random() % 6;
    std::cout << "The Goblin swings its club! (" << damage << " damage)\n";
    return damage;
}
