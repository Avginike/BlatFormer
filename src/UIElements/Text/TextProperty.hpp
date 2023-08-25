#pragma once
#include <string>
#include <raylib.h>

namespace BlatFormer
{

    class TextProperty
    {
        public:
            static Font MainFont;

            std::string text{};
            Font* font{};
            Color color{BLACK};
            float fontSize{25};
            float spacing{5};

        TextProperty()
        {
            font = &MainFont;    
        }
        TextProperty(std::string str):text(str),fontSize(25)
        {
            font = &MainFont;
        }
        TextProperty(std::string str, Font* font, Color color):text(str),font(font),color(color){}
        TextProperty(std::string str, Font* font, Color color,float spacing):text(str),font(font),color(color),spacing(spacing){}
    };
    
}