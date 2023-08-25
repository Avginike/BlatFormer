#pragma once

#include <string>
#include "UIElement.hpp"
#include <raylib.h>
#include "UIElements/Text/TextProperty.hpp"

namespace BlatFormer
{
    class Text: public UIElement
    {
        

        const int spacing = 5;
        public:



            

            TextProperty Properties{};
            
            
            Text() = default;
            Text(Vector2 position,std::string str, int fontSize,Color col);
            Text(Vector2 position,std::string str, int fontSize);
            Text(Vector2 position, std::string str);
           

            void Render();
            void RenderCentered();
            
    }; 


}  