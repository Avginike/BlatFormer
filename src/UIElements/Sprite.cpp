#include <raylib.h>
#include "Sprite.hpp"

namespace BlatFormer
{
    void Sprite::Render()
    {
        DrawTexturePro(*texture, {0,0,(float)texture->width,(float)texture->height}, {position.x, position.y,size.x,size.y}, {0, 0}, 0, WHITE);
    }
    void Sprite::RenderCentered()
    {
        DrawTexturePro(*texture, {0,0,(float)texture->width,(float)texture->height}, {position.x - size.x / 2, position.y - size.y / 2,size.x,size.y}, {0, 0}, 0, WHITE);
    }
} // namespace 
