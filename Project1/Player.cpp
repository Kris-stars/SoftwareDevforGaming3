#include "Player.h"
#include <random>
//Starting vaules
Player::Player() { 
    Reset(); 
}
//Just to reset player when need to restart
void Player::Reset() { 
    health = 100; potions = 0; hasShield = false; 
}
//Gets player helath
int Player::GetHealth() const { 
    return health;
}
//Gets potions after level
int Player::GetPotions() const { 
    return potions;
}
//Check for shield
bool Player::HasShield() const { 
    return hasShield;
}
//Check for player health
bool Player::IsAlive() const { 
    return health > 0;
}
//player health
void Player::SetHealth(int hp) {
    if (hp < 0) hp = 0;
    if (hp > 100) hp = 100;
    health = hp;
}
//This is seting amount need to play around
void Player::SetPotions(int count) { 
    if (count >= 0 && count <= 3) potions = count; 
}
//Gives a shield
void Player::GiveShield() { 
    hasShield = true; 
}
//Player taking Damage
void Player::TakeDamage(int amount) { 
    SetHealth(health - amount); 
}
int Player::SwingSword() const
{
    //this is to make it random every single time because the program dos make random but every start is not 
    std::random_device random;
    // 10 to 20 inclusive random damage
    return 10 + random() % 11;
} 
//DrinkPotion for health to player
bool Player::DrinkPotion() {
    if (potions == 0 || health == 100) return false;
    potions--;
    SetHealth(health + 50);
    return true;
}
