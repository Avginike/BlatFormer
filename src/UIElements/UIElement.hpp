
#pragma once
#include <raylib.h>

namespace BlatFormer
{
    class UIElement
    {

        public:
            virtual ~UIElement() = default;

            Vector2 position;
            Vector2 size;

            UIElement() = default;
            UIElement(Vector2 pos, Vector2 siz):position(pos),size(siz){};
            UIElement(Vector2 pos):position(pos){};


            virtual void Render() = 0;
            virtual void RenderCentered() { Render(); };
            virtual void Update(){};

            static void Render(UIElement &Element);
            static void Update(UIElement &Element);    

    };
}