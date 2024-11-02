#pragma once
#include <raylib.h>
#include "projectile.hpp"
#include <vector>

class Spaceship
{
private:
    Texture2D image;
    Vector2 position; // represent position of spaceship
    double lastFireTime; // for fire delay

public:
    Spaceship();
    ~Spaceship();
    void Draw(); // draw ship
    void MoveLeft(); // on user input
    void MoveRight();
    void FireProjectile(); // shoot em up
    Rectangle getRect();   // for hitbox
    std::vector<Projectile> projectiles; // all active shots fired from ship
    void Reset(); 
    


};
