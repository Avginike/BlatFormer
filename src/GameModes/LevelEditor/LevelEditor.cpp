#include "GameModes/LevelEditor.hpp"

#include "main.hpp"

#include <raymath.h>
#include <iostream>

namespace BlatFormer
{
    
    void LevelEditor::Render()
    {
        Level::RenderMap(xOffset, yOffset,scale);
        DrawGrid(xOffset, yOffset, scale);

        Vector2 MousePos = GetMousePosition();
        Selector.Render();
    }
    void LevelEditor::Update() 
    {
        Selector.Update();

        Vector2 mousePos = GetMousePosition();
        
        if(mousePos.x < (SCREEN_WIDTH - TILE_SIZE * 1.5))
        {
            
            mousePos.x -= xOffset * scale * TILE_SIZE;
            mousePos.y -= yOffset * scale * TILE_SIZE;
            

            int hoveredTileX = static_cast<int>(mousePos.x / (TILE_SIZE * scale));
            int hoveredTileY = static_cast<int>(mousePos.y / (TILE_SIZE * scale));

       
            if((hoveredTileX >= 0 && hoveredTileX < TILES_HORIZONTAL && hoveredTileY >= 0 && hoveredTileY < TILES_VERTICAL + 1)
            && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            {
                SetGrid(hoveredTileX, hoveredTileY, Selector.CurrentBlockID);
            }

        }

        float MouseWheelState = GetMouseWheelMove();
        

        scale += MouseWheelState * 0.1f;

        

        
       

        if(IsKeyDown(KEY_W))
        {
            yOffset += EditorMoveSpeed / scale;
        }
        if(IsKeyDown(KEY_A))
        {
            xOffset += EditorMoveSpeed / scale;
        }
        if(IsKeyDown(KEY_D))
        {
            xOffset -= EditorMoveSpeed / scale;
        }
        if(IsKeyDown(KEY_S))
        {
            if(IsKeyDown(KEY_LEFT_CONTROL))
                Save();
            else 
                yOffset -= EditorMoveSpeed / scale;
        }

        if(IsKeyDown(KEY_LEFT_CONTROL) &&  IsKeyPressed(KEY_R))
        {
            Level::Clear();
           
        }
        
        xOffset = clamp(xOffset, -( TILES_HORIZONTAL - MaxEditorOffset) * scale , double(TILES_HORIZONTAL - MaxEditorOffset ) * scale );
        yOffset = clamp(yOffset, -(TILES_VERTICAL - MaxEditorOffset) * scale, double(TILES_VERTICAL - MaxEditorOffset) * scale) ;

        scale = clamp(scale, 0.75f, 2.0f);
    

        Level::Update();
    }
    void LevelEditor::DrawGrid(double xOffset, double yOffset, float scale)
    {
        for(int y = 0; y < TILES_VERTICAL + 2; y++)
        {
            DrawLine(xOffset * TILE_SIZE * scale , (y + yOffset) * TILE_SIZE * scale, xOffset * TILE_SIZE * scale + (TILE_SIZE * TILES_HORIZONTAL) * scale, (y + yOffset) * TILE_SIZE * scale, RED);
        }
        for(int x = 0; x < TILES_HORIZONTAL + 1; x++)
        {
            DrawLine((x + xOffset) * TILE_SIZE * scale, yOffset * TILE_SIZE * scale, (x + xOffset) * TILE_SIZE * scale, yOffset * TILE_SIZE * scale + (TILE_SIZE * (TILES_VERTICAL + 1)) * scale, RED);
        }
    }
    void LevelEditor::Start()
    {
        Level::Start();
        LevelEditor::TileSelector::EraserTexture = LoadTexture(ASSETS_PATH"sprites/eraser.png");
    }
}
