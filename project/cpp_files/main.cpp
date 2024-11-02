#include <iostream>
#include <raylib.h> 
#include "game.hpp"
#include "aliens.hpp"
#include <string>


using namespace std;



int main(){
    int windowWidth = 750;
    int windowHeight = 800;
    int offset = 50;
    Color grey = {29, 29, 27, 255};
    Color yellow = {243,216,63,255};
    Color red = {230,41,15,255};
    Color navy = {0,0,128,255};

    InitWindow(windowWidth+offset, windowHeight + 2* offset, "Arcade Shooter");
    Font font = LoadFontEx("AachenFont.ttf", 64, 0, 0);
    Texture2D spaceshipImage = LoadTexture("graphics/ship.png");

    // how fast game should run
    SetTargetFPS(60);
    Game game;

    while(WindowShouldClose() == false){ // window closes on esc, clicking close


        game.HandleInput(); // arrow key movement and spacebar shooting
        game.Update(); // update game state
        
        BeginDrawing();
        ClearBackground(grey);
        DrawRectangle(10,10,780,880,navy);
        DrawLineEx({25,830},{775,830}, 3, yellow);

        if (game.run){
            DrawTextEx(font, "Endless Mode",{290,15}, 34, 2, yellow); 
        }
        else{
            DrawTextEx(font, "Game Over!", {285, 15}, 34,2,red); // game has ended
            DrawTextEx(font,"Press 'ENTER' to restart",{150, 839}, 40,2,red);
        }

        
        float x = 55.0;
        float scale = 0.1f;
        for(int i =0; i<game.lives; i++){ // show lives remaining at bottom of screen
            DrawTextureEx(spaceshipImage, {275+x, 839}, 0.0f, scale, WHITE);
            x+=50;
        }
        DrawTextEx(font,"Score:",{50,15},34,2,yellow); // kinda eyeballing some of these coordinates TODO: make nice
        DrawTextEx(font,"Best:", {650,15},34,2,yellow);

        std::string numberText = std::to_string(game.score);
        DrawTextEx(font, numberText.c_str(),{50,40},34,2,yellow);

        std::string highScoreText = std::to_string(game.highScore);
        DrawTextEx(font, highScoreText.c_str(),{675,40},34,2,yellow);

        game.Draw();
        EndDrawing();

    }

    CloseWindow();



}