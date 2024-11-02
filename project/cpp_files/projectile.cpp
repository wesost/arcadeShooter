#include "projectile.hpp"
#include <iostream>

Projectile::Projectile(Vector2 position, int speed)
{
    this -> position = position;
    this -> speed = speed;
    active = true;
}

void Projectile::Draw(){
    if(active){
        DrawRectangle(position.x, position.y, 4, 15, {243, 216, 63, 255});

    }
}

Rectangle Projectile::GetRect() // Projectile hitbox
{
    Rectangle rect;
    rect.x = position.x;
    rect.y = position.y;
    rect.width = 4;
    rect.height = 15;
    return rect; // 
}

void Projectile::Update(){
    position.y += speed;
    if(active){
        if(position.y > GetScreenHeight() - 100 || position.y < 25)
        active = false; 
    }
}