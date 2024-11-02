#pragma once
#include <raylib.h>

class Alien{
    public:
        static Texture2D alienImages[3]; // 3 different .pngs for 3 different aliens
        Vector2 position;
        Rectangle getRect(); // get hitbox for collision detection
        int type; // type 1,2,3 - different movement speeds
        bool active; // check if alien in bounds if not delete similar to projectile
        static void UnloadImages(); // free space once window closed
        void Update(int direction); // alien movement
        void Draw();
        int getType();  // 1,2, or 3
        int leftRight; // move left or right x axis - -1 or 1
        Alien(int type, Vector2 position); // constructor
        
    private:

};