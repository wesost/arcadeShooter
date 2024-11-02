#pragma once
#include <raylib.h>

class Projectile {
    public:
        Projectile(Vector2 position, int speed);
        
        void Update(); // update position
        void Draw();   // draw projectile
        bool active;   // inactive once hits alien or ship or goes out of bounds
        Rectangle GetRect(); // hitboxes
    private:
        Vector2 position;
        int speed;


};