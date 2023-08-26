
#include "Level.hpp"
#include "main.hpp"
#include "NibblePair.hpp"
#include "GameModes/Menus.hpp"

#include <vector>
#include <raylib.h>
#include <raymath.h>
#include <fstream>
#include <iostream>

namespace BlatFormer 
{
    Texture2D Level::OrbTexture;
    Texture2D Level::FinishTexture;

    void Level::Start()
    {
        OrbTexture = LoadTexture(ASSETS_PATH"sprites/orb.png");
        FinishTexture = LoadTexture(ASSETS_PATH"sprites/finish.png");

        int TileAmount = ceil((float)TILES_HORIZONTAL * (float)(TILES_VERTICAL + 1) / 2.0);
        LevelData = std::vector<NibblePair>(TileAmount, NibblePair());

        Load();

    }

    void Level::Save()
    {
        ofstream out{LevelPath,ios::binary};
        if(out.is_open())
        {
            out << (uint8_t) StartingPosition.x << (uint8_t) StartingPosition.y;
            for(int i = 0; i < LevelData.size(); i++)
            {
                out << LevelData[i].LH;
                
            }
        }
        else
        {
            std::cout << "Failed to save level" << std::endl;
        }

    }
    void Level::Load()
    {
        ifstream in{LevelPath,ios::binary};
        if(in.is_open())
        {
            uint8_t tempx, tempy;

            in >> tempx >> tempy;
            StartingPosition = {(float)tempx,(float)tempy};

            for(int i = 0; i < LevelData.size(); i++)
            {
                in >> LevelData[i].LH;
            }
        }
        else
        {
            std::cout << "Failed to load level" << std::endl;
        }
    }

    void Level::Render() 
    {
        RenderMap(0,0,1);
    }
    void Level::RenderMap(double xOffset, double yOffset, float scale) 
    {
        for(int y  = 0; y < TILES_VERTICAL + 1; y++)
        {
            for(int x = 0; x < TILES_HORIZONTAL; x++)
            {
               RenderBlock((x + xOffset) * TILE_SIZE  * scale, (y + yOffset) * TILE_SIZE * scale, GetGrid(x, y), scale);
            }
        }
    }
    void Level::Update()
    {
        if(IsKeyPressed(KEY_ESCAPE))
        {
            ExitMode();
        }
        
    }
    void Level::RenderBlock(double x, double y, uint8_t state, float scale)
    {
         
        Color color;

        if(state == 0)
            return;

        switch (state)
        {
            case 1:
                color = {0, 204, 255, 255}; // Pastel Blue
                break;
            case 2:
                color = PURPLE;
                break;
            case 3:
                color = GRAY;
                break;
            case 4:
                color = WHITE;
                break;
            case 5:
                color = DARKGRAY;
                break;
            case 6:
                color = LIGHTGRAY;
                break;
            case 7:
                color = PINK;
                break;
            case 8:
                color = RED;
                break;
            case 9:
                color = DARKPURPLE;
                break;
            case 10:
                color = BLUE;
                break;
            case 11:
                color = DARKBLUE;
                break;
            case 12:
                color = GREEN;
                break;
            case 13:
                color = DARKGREEN;
                break;
            case 14:
                color = YELLOW;
                break;
            case 15:
                color = WHITE;
                DrawTextureEx(FinishTexture, {(float)x , (float)y }, 0, TILE_SIZE / FinishTexture.height * scale, WHITE);
            default:
                return;
        }

        if (state > 2)
        {
            DrawRectangle(x, y, TILE_SIZE * scale, TILE_SIZE * scale, color);
        }
        else
        {
            DrawTextureEx(OrbTexture, {(float)x , (float)y }, 0, TILE_SIZE / OrbTexture.height * scale, color);
        }
    }

  
    void Level::Clear() 
    {
        for(int i = 0; i < LevelData.size(); i++)
        {
            LevelData[i].LH = 0;
        }
    }

    
    void Level::SetGrid(int x, int y, uint8_t state) 
    {
        int NibbleIndex = floor((y * (TILES_HORIZONTAL) + x) / 2.0);
        
        //check if number is odd
        if( x & 1 )
        {
            LevelData[NibbleIndex].SetH(state);
        }
        else
        {
            LevelData[NibbleIndex].SetL(state);
        }
        
    }

    uint8_t Level::GetGrid(int x, int y) 
    {
        int NibbleIndex = floor((y * (TILES_HORIZONTAL) + x) / 2.0);
        
        //check if number is odd
        if( x & 1 )
        {
            return LevelData[NibbleIndex].GetH();
        }
        else
        {
            return LevelData[NibbleIndex].GetL();
        }
    }

    

}