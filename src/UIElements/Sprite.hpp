#pragma once
#include <raylib.h>
#include "UIElement.hpp"

namespace BlatFormer
{
    class Sprite : public UIElement
    {

        public:
            Texture2D* texture;

            Sprite() = default;
            Sprite(Vector2 pos, Vector2 siz,Texture2D tex):UIElement(pos,siz),texture(&tex){}
            ~Sprite() = default;

            void Render();
            void RenderCentered();
         
    };
}