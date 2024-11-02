#include "Spaceship.hpp"

Spaceship::Spaceship()
{
    image = LoadTexture("graphics/ship.png"); // png of spaceship - make customizable
    float scaledWidth = image.width * 0.1; 
    float scaledHeight = image.height * 0.1;
    position.x = (GetScreenWidth() - scaledWidth) / 2;
    position.y = GetScreenHeight() - scaledHeight - 100; 
    lastFireTime = 0.0;
}

Spaceship::~Spaceship(){  
    UnloadTexture(image);
}

void Spaceship::Draw(){
    float scale = 0.1f;
    DrawTextureEx(image, position, 0.0f, scale, WHITE); 

}

void Spaceship::MoveLeft(){
    position.x -= 7; 
    if(position.x < 25){
        position.x = 25;
    }
}
void Spaceship::MoveRight(){ 
    float scaledWidth = image.width * 0.1; // TODO make member variable of spaceship class instead of redeclaring everywhere
    float scaledHeight = image.height * 0.1;
    position.x += 7; 
    if(position.x > GetScreenWidth() - scaledWidth - 25){ // check bounds
        position.x = GetScreenWidth() - scaledHeight -25; 
    }
}

void Spaceship::FireProjectile()
{
    float scaledWidth = image.width * 0.1; 
    
    if(GetTime() - lastFireTime >= 0.35) {// check cooldown
        projectiles.push_back(Projectile({position.x + scaledWidth/2 - 2,position.y},-7)); 
        lastFireTime = GetTime();
    }
}

Rectangle Spaceship::getRect() // for hitboxes
{
    return {position.x, position.y, float(image.width*0.05), float(image.height*0.05)};
}

void Spaceship::Reset()
{
    position.x = (GetScreenWidth() - image.width *0.05)/2.0f; // reset to center position
    position.y = GetScreenHeight() - image.height*0.05*2 - 100;
    projectiles.clear(); // clear out projectile
}
