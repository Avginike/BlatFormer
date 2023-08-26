#pragma once
#include <raylib.h>
#include <string>
#include <functional>

#include "UIElements/UIElement.hpp"
#include "UIElements/Text.hpp"
using namespace std;

namespace BlatFormer
{
    

    class Button : public UIElement
    {
        float scale{1};
        float sizex;
        float sizey;
        
        public:

            TextProperty Label{};
            std::function<void()> OnClickEvent;
            Color color = BLACK;
            
            
           
        void Update();
        void Update(std::function<void()> ClickEvent);
        void Update(std::function<void(Button&)> ClickEvent);
        void Render();
        

        Button() = default;
        
        Button(Vector2 position, Vector2 siz, Color col, std::function<void()> OnClickEvent): UIElement(position,siz),color(col),OnClickEvent(OnClickEvent){};
        
    };
}