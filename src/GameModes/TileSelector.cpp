#include "LevelEditor.hpp"
#include "main.hpp"

#include <raymath.h>

namespace BlatFormer
{
    void LevelEditor::TileSelector::Render()
    {
        Rectangle SelectorBackground = {(float)(SCREEN_WIDTH - TILE_SIZE * 1.5), 0, (float)(TILE_SIZE * 1.5), (float) SCREEN_HEIGHT};
        DrawRectangleRec(SelectorBackground, GRAY);

        DrawLine(SCREEN_WIDTH - TILE_SIZE * 1.5, 0, SCREEN_WIDTH - TILE_SIZE * 1.5, SCREEN_HEIGHT, BLACK);
        
        for(int i = 0; i < 16; i++)
            Level::RenderBlock(SCREEN_WIDTH - TILE_SIZE,i * (TILE_SIZE + 5),i);
    }
    void LevelEditor::TileSelector::Update()
    {

    }

}