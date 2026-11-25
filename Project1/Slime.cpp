#include "Slime.h"
#include <iostream>
#include <random>
//Simle with stats 
Slime::Slime() : Enemy("Slime", 30) {}
int Slime::Attack() {
    //random damage from 7 to 12
    std::random_device random;
    int damage = 7 + random() % 6;
    std::cout << "A Slime jumps at you! (" << damage << " damage)\n";
    return damage;
}
