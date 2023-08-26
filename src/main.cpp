#include <raylib.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stack>
#include <memory>

#include "main.hpp"
#include "DataStructures/GameMode.hpp"
#include "GameModes/Menus.hpp"
#include "UIElements/Button.hpp"
#include "DataStructures/Level.hpp"
#include "UIElements/Text.hpp"
#include "raymath.h"

namespace BlatFormer
{
    

    int SCREEN_WIDTH = 1280;
    int SCREEN_HEIGHT = 720;

    int TILE_SIZE = 32;

    int TILES_VERTICAL = ceil(SCREEN_HEIGHT / TILE_SIZE);
    int TILES_HORIZONTAL = ceil(SCREEN_WIDTH / TILE_SIZE); 

    Font MainFont;

    
}



using namespace BlatFormer;
int main()
{
    SetRandomSeed(time(NULL));

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Cyka Blat!");

    LoadTexture(ASSETS_PATH"sprites/blat.png");

    TextProperty::MainFont = LoadFontEx(ASSETS_PATH"Roboto-Bold.ttf", 70, nullptr,0);
    
    GameMode::SetEnterGameMode(std::make_unique<MainMenu>());
   
    SetExitKey(KEY_NULL);

    while(!GameMode::GameHasToExit)
    {

        

        BeginDrawing();  

        ClearBackground(BLACK);
        
        
        if(IsKeyPressed(KEY_F11) || IsKeyDown(KEY_LEFT_ALT) && IsKeyPressed(KEY_ENTER))
        {
            ToggleFullscreen();
        }
        GameMode::GameHasToExit = WindowShouldClose();

        GameMode::UpdateCurrentMode();
        GameMode::RenderCurrentMode();
        

        
       
        
        
        
        
       
        

        EndDrawing();
    }

    


    return 0;

}

