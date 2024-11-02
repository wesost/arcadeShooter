#include "game.hpp"
#include <iostream>
#include <fstream>

Game::Game()
{
    InitGame();
}

Game::~Game()
{
    Alien::UnloadImages();
}
void Game::Update() // called each frame
{
    if(run){
        int currentTime = GetTime();
        for (auto &projectile : spaceship.projectiles)
        {
            projectile.Update();
        }
        
        MoveAliens();

        AlienShootProjectile();
        for(auto& projectile: alienProjectiles){
            projectile.Update();
        }
        DeleteInactiveProjectiles();
        DeleteInactiveAliens();
        CheckCollisions();
        if(currentTime > lastAlienSpawned + alienSpawnInterval){ // check if it's time to spawn another alien  - don't want to spawn 60aliens/sec
            spawnAlien(); 
            lastAlienSpawned = GetTime(); // update time 
        }
        
    }
    else {
        if(IsKeyDown(KEY_ENTER)){
            Reset(); // start game over
            InitGame();
        }
    }
}

void Game::Draw() // draw everything
{
    spaceship.Draw();
    for (auto &projectile : spaceship.projectiles)
    {
        projectile.Draw();
    }
    for (auto &alien : spawnedAliens)
    {
        alien.Draw();
    }
    for (auto& projectile: alienProjectiles){
        projectile.Draw();
    }
}

void Game::HandleInput() /// player actions
{
    if(run){
        // detect keystroke
        if (IsKeyDown(KEY_LEFT))
        {
            spaceship.MoveLeft();
        }
        else if (IsKeyDown(KEY_RIGHT))
        {
            spaceship.MoveRight();
        }
        else if (IsKeyDown(KEY_SPACE))
        {
            spaceship.FireProjectile();
        }
        }
}

void Game::DeleteInactiveAliens(){ // deletes aliens if they go out of bounds y axis 
    for(auto it = spawnedAliens.begin(); it != spawnedAliens.end();){
        if(!it->active){ // set to inactive when they reach certain y val
            it = spawnedAliens.erase(it); /// 
        }
        else {
            ++it; // go next
        }
    }
}

void Game::DeleteInactiveProjectiles()
{
    for (auto it = spaceship.projectiles.begin(); it != spaceship.projectiles.end();)
    {
        if (!it->active)
        { // erase Projectile if off screen
            it = spaceship.projectiles.erase(it);
        }
        else
        {
            ++it; // else check next projectile
        }
    }
    for (auto it = alienProjectiles.begin(); it != alienProjectiles.end();)
    {
        if (!it->active)
        { // erase projectile if off screen to free memory
            it = alienProjectiles.erase(it);
        }
        else
        {
            ++it; // else check next projectile
        }
    }

}


void Game::MoveAliens(){ 

    for(auto& alien: spawnedAliens){ 
        if(alien.position.x + alien.alienImages[alien.type - 1].width * 0.05 > GetScreenWidth() -25){ // don't go out of bounds
            alien.leftRight = -1; // reverse direction x axis if wall hit
        }
        if(alien.position.x < 25){
            alien.leftRight = 1;
        }
        if(alien.position.y > 810){ // if alien goes out of bounds at the bottom of the screen
            alien.active = false;
        }
        alien.Update(alien.leftRight); // 

    }
}


void Game::AlienShootProjectile()
{
    double currentTime = GetTime();
    if(currentTime - timeLastAlienFired >= alienProjectileShootInterval && !spawnedAliens.empty()){ // check cooldown

        int randomIndex = GetRandomValue(0, spawnedAliens.size() -1); // which aliens shoot is randomized
        Alien& alien = spawnedAliens[randomIndex]; 
 
        float test = alien.position.x + (alien.alienImages[alien.type - 1].width * 0.05) / 2;

        float test2 = alien.position.y + alien.alienImages[alien.type - 1].height * 0.05;

        alienProjectiles.push_back(Projectile({test, test2}, 5)); // add projectile to active projectiles
        timeLastAlienFired = GetTime(); // update value
    }

}

void Game::CheckCollisions()
{
    //spaceship projectiles
    for(auto& projectile: spaceship.projectiles){
        auto it = spawnedAliens.begin();  
        while(it != spawnedAliens.end()){
            if (CheckCollisionRecs(it -> getRect(), projectile.GetRect())){ // check for collision
                it = spawnedAliens.erase(it); // kill alien!!
                projectile.active = false; // no colaterals
                score+=1; // increment score for each alien shot down
                checkForHighScore();
            }
            else{
                ++it; // go next if no hit
            }
        }
    }

    //alien projectiles
    for(auto& projectile: alienProjectiles){
        if(CheckCollisionRecs(projectile.GetRect(), spaceship.getRect())){
            projectile.active = false;
            lives--;
            if(lives <= 0){
                GameOver();
            }
            std::cout<< "Hit! " << std::endl; 
        }
    }

    //alien collsion with ship
    for (auto& alien: spawnedAliens){

    if(CheckCollisionRecs(alien.getRect(),spaceship.getRect())){
        GameOver();
    }
    }

}

void Game::GameOver(){
    //std::cout<<"Game over"<<std::endl;//test
    run = false;
}

void Game::InitGame()
{
    // spawnedAliens.push_back(Alien(1, {250.0, 45.0})); // test 
    
    timeLastAlienFired = 0.0;
    lives = 3;
    run = true; // game is running
    score = 0;
    highScore = LoadHighScoreFromFile();
    //levelLength = 60000; // 60 seconds per level
    alienSpawnInterval = 0.5; // every half second - easy to implement easier/harder difficulties by changing this
    lastAlienSpawned = GetTime();
}

void Game::Reset(){ // reset ship position, clear out active aliens and projectiles

    spaceship.Reset();
    spawnedAliens.clear();
    alienProjectiles.clear();
}

void Game::checkForHighScore()
{
    if(score>highScore){
        highScore = score;
        saveHighScoreToFile(highScore);
    }
}

void Game::saveHighScoreToFile(int highScore)
{
    std::ofstream highScoreFile("highScoreFile.txt");
    if(highScoreFile.is_open()){
        highScoreFile << highScore;
        highScoreFile.close();
    }
    else{
        std::cerr<<"failed to save high score" <<std::endl;
    }
}

int Game::LoadHighScoreFromFile()
{
    int loadedHighScore = 0;
    std::ifstream highScoreFile("highScoreFile.txt");
    if(highScoreFile.is_open()){
        highScoreFile>>loadedHighScore;
        highScoreFile.close();
    }
    else{
        std::cerr<<"failed to load high score" << std::endl;
    }
    return loadedHighScore;
}
void Game::spawnAlien() // spawn single alien
{
    int alienType = GetRandomValue(1,3); // get random values for type and position of alien
    float x = GetRandomValue(75.0, 650.0);
    float y = GetRandomValue(75.0, 80.0);
    int LR = GetRandomValue(-1,1); // initial x axis movement direction

    Alien alien = Alien(alienType, {x, y});
    alien.leftRight = LR; // once they spawn randomized if they move left/right
    spawnedAliens.push_back(alien); // add aliien to game
}

