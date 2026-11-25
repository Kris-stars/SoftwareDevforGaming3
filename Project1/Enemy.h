#pragma once
#include <string>

//base class and set up for enemys
class Enemy {
private:
    std::string name;
    int health;
    int maxHealth;
public:
    Enemy(std::string enemyName, int hp);
    virtual ~Enemy();
    std::string GetName() const;
    int GetHealth() const;
    int GetMaxHealth() const;
    bool IsAlive() const;
    void TakeDamage(int damage);
    virtual int Attack() = 0;
};
