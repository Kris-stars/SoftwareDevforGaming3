#include "Enemy.h"
//enemy base stats
Enemy::Enemy(std::string enemyName, int hp) {
    name = enemyName;
    health = hp;
    maxHealth = hp;
}
//Destructor
Enemy::~Enemy() {}

//name of enemy
std::string Enemy::GetName() const { 
    return name;
}
//enemy health
int Enemy::GetHealth() const { 
    return health;
}
//enemy max health its starting health
int Enemy::GetMaxHealth() const { 
    return maxHealth;
}
//alive check
bool Enemy::IsAlive() const { 
    return health > 0;
}
//taking damge
void Enemy::TakeDamage(int damage) {
    health -= damage;
    if (health < 0) health = 0;
}
