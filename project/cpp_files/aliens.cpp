#include "aliens.hpp"

Texture2D Alien::alienImages[3] = {};

void Alien::UnloadImages() // free up once window is closed
{
    for(int i =0; i<4; i++){
        UnloadTexture(alienImages[i]);
    }
}

Alien::Alien(int type, Vector2 position)
{
    this->type = type;
    this->position = position;
    active = true; // false when destroyed or out of bounds

    if(alienImages[type-1].id ==0){

        switch (type){
            case 1:
                alienImages[0] = LoadTexture("graphics/alien1.png"); //normal
                break;
            case 2:
                alienImages[1] = LoadTexture("graphics/alien2.png"); // medium speed
                break;
    
            case 3:
                alienImages[2] = LoadTexture("graphics/alien3.png"); // moves fast?
                break;
    
            default:
                alienImages[0] = LoadTexture("graphics/alien1.png");
                break;

    }
}
}


void Alien::Draw(){

    float scale = 0.05f; 
    DrawTextureEx(alienImages[type-1], position, 0.0f, scale, WHITE); // scale down large png

}

int Alien::getType(){ // 1, 2, 3, 4, etc
    return type;
}

Rectangle Alien::getRect() // get hitbox
{
    return {position.x, position.y, float(alienImages[type - 1].width *0.05), float(alienImages[type-1].height*0.05)};
}

void Alien::Update(int direction){

    position.x += this->leftRight;  // direction 
    if(this->type == 1){
        this->position.y += 0.3; 
    }
    if(this->type==2){
        this->position.y += 0.5; // slow
    }
    else if(this->type == 3){
        this->position.y += 1; // fast
    }
}