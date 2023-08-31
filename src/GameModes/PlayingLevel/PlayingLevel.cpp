#include "GameModes/PlayingLevel.hpp"
#include "main.hpp"

#include <raymath.h>

namespace BlatFormer
{
    void PlayingLevel::Update()
    {
        player.Update();
        Level::Update();
        
    }
    void PlayingLevel::Render()
    {
        Level::Render();
        player.Render();
        
        
    }
    void PlayingLevel::Start()
    {
        Level::Start();
        player.position = Vector2Scale(StartingPosition, TILE_SIZE);
        player.Start();
    }
    
}