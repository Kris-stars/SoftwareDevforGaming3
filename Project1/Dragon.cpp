#include "Dragon.h"
#include <iostream>
#include <random>
//dragone base stats
Dragon::Dragon() : Enemy("Dragon", 100) {
    useFireNext = false; // first attack is normal.
}
//dragon attacks
int Dragon::Attack() {
    std::random_device random;
    if (useFireNext) {
        //fire does random damage from 20 to 30
        int damage = 20 + random() % 11;
        std::cout << "The Dragon breathes FIRE! (" << damage << " damage)\n";
        useFireNext = false;
        return damage;
    }
    //claws do random damage from 12 to 18
    int damage = 12 + random() % 7;
    std::cout << "The Dragon attacks with its claws! (" << damage << " damage)\n";
    useFireNext = true;
    return damage;
}
