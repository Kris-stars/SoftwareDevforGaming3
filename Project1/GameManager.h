#pragma once
#include "Player.h"
#include "Enemy.h"
#include <vector>

class GameManager {
private:
    Player player;
    int level;
    std::vector<Enemy*> enemies;

    void ClearEnemies();
    void CreateEnemies();
    bool SaveGame() const;
    bool LoadGame();
    int Battle();

public:
    GameManager();
    ~GameManager();
    void Start();
};
