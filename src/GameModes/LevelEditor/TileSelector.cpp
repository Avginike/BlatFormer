
#include "GameModes/LevelEditor.hpp"
#include "main.hpp"

#include <raymath.h>

namespace BlatFormer
{
    Texture2D LevelEditor::TileSelector::EraserTexture;
    void LevelEditor::TileSelector::Render()
    {
        Rectangle SelectorBackground = {(float)(SCREEN_WIDTH - TILE_SIZE * 1.5), 0, (float)(TILE_SIZE * 1.5), (float) SCREEN_HEIGHT};
        DrawRectangleRec(SelectorBackground, BLACK);

        DrawLine(SCREEN_WIDTH - TILE_SIZE * 1.5, 0, SCREEN_WIDTH - TILE_SIZE * 1.5, SCREEN_HEIGHT, WHITE);
        
        DrawTextureEx(EraserTexture, Vector2{(float)(SCREEN_WIDTH - TILE_SIZE * 0.75 - TILE_SIZE / 2 ), 0},0, TILE_SIZE / EraserTexture.height, WHITE);

        for(int i = 1; i < 16; i++)
            Level::RenderBlock(SCREEN_WIDTH - TILE_SIZE * 0.75 - TILE_SIZE / 2,i * (TILE_SIZE + 10),i);
        
        
    }
    void LevelEditor::TileSelector::Update()
    {
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            for(int i = 0; i < 16; i++)
            {     
                    Rectangle TileRect = {
                        float(SCREEN_WIDTH - TILE_SIZE * 0.75 - TILE_SIZE / 2),
                        float( i * (TILE_SIZE + 10)),
                        float(TILE_SIZE),
                        float(TILE_SIZE)
                        };
                    
                    if(CheckCollisionPointRec(GetMousePosition(), TileRect))
                    {
                        CurrentBlockID = i;
                        break;
                    }
            }
            if(
                CheckCollisionPointRec(GetMousePosition(),{
                float(SCREEN_WIDTH - TILE_SIZE * 0.75 - TILE_SIZE / 2),
                float( 16 * (TILE_SIZE + 10)),
                float(TILE_SIZE),
                float(TILE_SIZE)
                }))   
            {
                CurrentBlockID = 16;
            }
        }

    }

}