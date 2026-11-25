#include "GameManager.h"
#include "EnemyFactory.h"
#include <iostream>
#include <string>
#include <random>
#include <fstream>

//game starts at level 1
GameManager::GameManager() {
    level = 1;
}
//game deconstructor
GameManager::~GameManager() {
    ClearEnemies();
}
//delets all enemys and pointers
void GameManager::ClearEnemies() {
    for (Enemy* enemy : enemies) {
        delete enemy;
    }
    enemies.clear();
}


//create enemies for the current level
void GameManager::CreateEnemies() {
    ClearEnemies();

    // Create the enemies for this level using the Factory.
    if (level == 1) {
        enemies.push_back(EnemyFactory::CreateEnemy("goblin"));
    }
    else if (level == 2) {
        enemies.push_back(EnemyFactory::CreateEnemy("slime"));
        enemies.push_back(EnemyFactory::CreateEnemy("slime"));
    }
    else {
        enemies.push_back(EnemyFactory::CreateEnemy("dragon"));
    }
}

//save the player and enemy stats to save.txt
bool GameManager::SaveGame() const {
    std::ofstream file("save.txt");

    if (!file) {
        std::cout << "Could not save game.\n";
        return false;
    }

    //write everything in the same order
    file << level << "\n";
    file << player.GetHealth() << "\n";
    file << player.GetPotions() << "\n";
    file << player.HasShield() << "\n";

    //save each enemy health
    for (Enemy* enemy : enemies) {
        file << enemy->GetHealth() << "\n";
    }

    file.close();
    if (!file) {
        std::cout << "Could not finish saving game.\n";
        return false;
    }

    std::cout << "Game saved!\n";
    return true;
}

//load the saved stats from save.txt
bool GameManager::LoadGame() {
    std::ifstream file("save.txt");

    if (!file) {
        std::cout << "No saved game found.\n";
        return false;
    }

    int savedLevel;
    int savedHealth;
    int savedPotions;
    int savedShield;
    int enemyHealth1;
    int enemyHealth2 = 0;

    //read everything in the same order it was saved
    if (!(file >> savedLevel >> savedHealth >> savedPotions
        >> savedShield >> enemyHealth1)) {
        std::cout << "Save file is invalid.\n";
        return false;
    }

    //level 2 has two slimes
    if (savedLevel == 2) {
        if (!(file >> enemyHealth2)) {
            std::cout << "Save file is invalid.\n";
            return false;
        }
    }

    //check if the level and player stats are valid
    if (savedLevel < 1 || savedLevel > 3 ||
        savedHealth < 1 || savedHealth > 100 ||
        savedPotions < 0 || savedPotions > 3 ||
        savedShield < 0 || savedShield > 1) {

        std::cout << "Save file is invalid.\n";
        return false;
    }

    //check if enemy health is valid
    if ((savedLevel == 1 && (enemyHealth1 < 1 || enemyHealth1 > 40)) ||
        (savedLevel == 2 && (enemyHealth1 < 0 || enemyHealth1 > 30 ||
            enemyHealth2 < 0 || enemyHealth2 > 30 ||
            (enemyHealth1 == 0 && enemyHealth2 == 0))) ||
        (savedLevel == 3 && (enemyHealth1 < 1 || enemyHealth1 > 100))) {

        std::cout << "Save file is invalid.\n";
        return false;
    }

    //load the player stats
    level = savedLevel;
    player.Reset();
    player.SetHealth(savedHealth);
    player.SetPotions(savedPotions);

    if (savedShield == 1) {
        player.GiveShield();
    }

    //load the enemy stats
    CreateEnemies();

    enemies[0]->TakeDamage(enemies[0]->GetHealth() - enemyHealth1);

    if (level == 2) {
        enemies[1]->TakeDamage(enemies[1]->GetHealth() - enemyHealth2);
    }

    std::cout << "Loaded Level " << level << "!\n";
    return true;
}

//1 means win, 0 means lose, -1 means save and quit
int GameManager::Battle() {
    //do not recreate enemies when loading a saved battle
    if (enemies.empty()) CreateEnemies();

    //random number for the lucky block
    std::random_device random;

    std::cout << "\n========== LEVEL " << level << " ==========\n";

    //display player health
    while (player.IsAlive()) {
        std::cout << "\nYour HP: " << player.GetHealth()
            << " | Potions: " << player.GetPotions() << "\n";

        //enemy count and display
        int number = 1;
        for (Enemy* enemy : enemies) {
            std::cout << number << ". " << enemy->GetName()
                << " HP: " << enemy->GetHealth() << "\n";
            number++;
        }
        //display options
        std::cout << "\n1. Attack\n";
        //only show block when player has a shield
        if (player.HasShield()) {
            std::cout << "2. Block\n";
        }
        //only show potion when player has potions
        if (player.GetPotions() > 0) {
            std::cout << "3. Drink potion\n";
        }
        //save only when the player chooses this option
        std::cout << "4. Save and Quit\n";
        std::cout << "Choose: ";
        std::string choice;
        if (!(std::cin >> choice)) return -1;

        if (choice == "4") {
            if (SaveGame()) return -1;
            continue;
        }

        // Potions are free: enemies do not attack
        if (choice == "3") {
            if (player.GetPotions() == 0) {
                std::cout << "Invalid option.\n";
                continue;
            }
            if (player.DrinkPotion()) std::cout << "Potion used!\n";
            else std::cout << "You cannot use a potion.\n";
            continue;
        }

        // A shield check if you have it
        if (choice == "2" && !player.HasShield()) {
            std::cout << "Invalid option.\n";
            continue;
        }

        if (choice == "1") {
            int target = 0;
            //slime enemy have to chocie which one
            if (level == 2) {
                //if slime 1 is dead go straight to slime 2
                if (!enemies[0]->IsAlive()) {
                    target = 1;
                }
                //if slime 2 is dead go straight to slime 1
                else if (!enemies[1]->IsAlive()) {
                    target = 0;
                }
                //if both are alive let player choose
                else {
                    std::cout << "Attack Slime 1 or 2? ";
                    std::string slimeChoice;
                    if (!(std::cin >> slimeChoice)) return -1;

                    if (slimeChoice == "1") target = 0;
                    else if (slimeChoice == "2") target = 1;
                    else {
                        std::cout << "Choose 1 or 2.\n";
                        continue;
                    }
                }
            }
            //check if the slime is dead already and dos not waste turn
            if (!enemies[target]->IsAlive()) {
                std::cout << "That enemy is already defeated.\n";
                continue;
            }
            //damage 
            int damage = player.SwingSword();
            enemies[target]->TakeDamage(damage);
            std::cout << "You deal " << damage << " damage!\n";
        }
        //if its not 1,2 or 3 remake the choice 
        else if (choice != "2") {
            std::cout << "Choose 1, 2 or 3.\n";
            continue;
        }

        //check if every enemy has been defeated
        bool allDefeated = true;
        for (Enemy* enemy : enemies) {
            if (enemy->IsAlive()) allDefeated = false;
        }
        if (allDefeated) return 1;

        //every living enemy takes a turn after an attack or block
        for (Enemy* enemy : enemies) {
            if (enemy->IsAlive()) {
                int damage = enemy->Attack();
                if (choice == "2") {
                    std::cout << "Your shield blocks the damage!\n";
                }
                //10 percent chance of blocking without the shield
                else if (random() % 10 == 0) {
                    std::cout << "Lucky block! You take no damage!\n";
                }
                else {
                    player.TakeDamage(damage);
                    std::cout << "You take " << damage << " damage.\n";
                }
                if (!player.IsAlive()) return 0;
            }
        }
    }

    return 0;
}
//start of game
void GameManager::Start() {
    while (true) {
        std::cout << "\n===== THE DRAGON'S DUNGEON =====\n";
        std::cout << "1. New Game\n2. Load Game\n3. Exit\nChoose: ";

        std::string choice;
        if (!(std::cin >> choice)) return;

        if (choice == "1") {
            //new game
            player.Reset();
            level = 1;
            ClearEnemies();
        }
        else if (choice == "2") {
            if (!LoadGame()) continue;
        }
        else if (choice == "3") {
            return;
        }
        else {
            std::cout << "Invalid option.\n";
            continue;
        }

        bool won = true;

        //gos through every level
        for (; level <= 3; level++) {
            int result = Battle();

            //save and quit ends the program
            if (result == -1) return;
            if (result == 0) {
                won = false;
                break;
            }

            //chechpoints and rewards
            if (level == 1) {
                player.GiveShield();
                std::cout << "\nLevel 1 complete! You got a SHIELD!\n";
            }
            else if (level == 2) {
                player.SetPotions(3);
                std::cout << "\nLevel 2 complete! You got 3 POTIONS!\n";
            }

            ClearEnemies();
        }

        //resets enemys by deleting pointers
        ClearEnemies();

        //if level is 4 meaning beat level 3 you win
        if (won) std::cout << "\nYOU WIN! You defeated the Dragon!\n";
        else std::cout << "\nYOU LOSE! Try again!\n";

        std::string again;
        while (true) {
            //check for yes or no
            std::cout << "Play again? (y/n): ";
            if (!(std::cin >> again)) return;
            if (again == "y" || again == "Y") break;
            if (again == "n" || again == "N") return;
            std::cout << "Please type y or n.\n";
        }
    }
}
