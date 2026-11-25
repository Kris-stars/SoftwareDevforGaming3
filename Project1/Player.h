#pragma once
class Player {
private:
    int health;
    int potions;
    bool hasShield;
public:
    Player();
    void Reset();
    int GetHealth() const;
    int GetPotions() const;
    bool HasShield() const;
    bool IsAlive() const;
    void SetHealth(int hp);
    void SetPotions(int count);
    void GiveShield();
    void TakeDamage(int amount);
    int SwingSword() const;
    bool DrinkPotion();
};
