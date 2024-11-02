#pragma once
#include "spaceship.hpp"
#include "aliens.hpp"

class Game {
    public:
        Game();
        ~Game();
        void Draw(); // draw ship, aliens, projectiles
        void Update(); // update positions, delete inactive elements, check for game over/reset conditions, spawn new aliens
        void HandleInput(); // arrow and spacebar keys for movement and shooting
        bool run; // true if runs false if game stopped
        int lives;
        int score;
        int highScore;
        // int level; // store level TODO: implement levels
        // int levelLength; // length of level
        float alienSpawnInterval;  // how often aliens spawn
        int lastAlienSpawned;    // time last alien was spawned for

    private:
        Spaceship spaceship; // player ship
        std::vector<Alien> spawnedAliens; // spawned enimies
        std::vector<Projectile> alienProjectiles; // enemy projectiles

        float timeLastAlienFired; // for spacing out fire rate of aliens
        float alienProjectileShootInterval = 0.35;
        void DeleteInactiveProjectiles(); // cleanup out of bounds projectiles
               
        void MoveAliens(); // aliens advance toward player

        //void MoveDownAliens(int distance);
        void AlienShootProjectile(); // picks random alien makes them shoot 
        void CheckCollisions(); // projectile and ship, projectile and alien, alien and ship
        void GameOver(); // When hit by alien or 3 projectiles
        void InitGame(); // initialize values
        void Reset();    // reset after game over
        void checkForHighScore();  // self explanatory
        void saveHighScoreToFile(int highScore); // save high score
        int LoadHighScoreFromFile();   /// load previous high score

        void spawnAlien();  // spawn a single alien at top of screen
        void DeleteInactiveAliens(); // clean up aliens that pass player out of bounds in +y direction

        

        // void initLevel(); // initialize level TODO: implement levels with varying difficulty

};