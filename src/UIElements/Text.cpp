#include <raylib.h>
#include <string>

#include "Text.hpp"
#include "UIElement.hpp"

namespace BlatFormer
{
    
    
    Text::Text(Vector2 pos, std::string str, int fontSize): UIElement(pos),Properties(str)
    {
        Properties.fontSize = fontSize;
    }
    
    Text::Text(Vector2 pos, std::string str): UIElement(pos),Properties(str){}

    Text::Text(Vector2 position,std::string str, int fontSize, Color col): UIElement(position),Properties(str)
    {
        Properties.fontSize = fontSize;
        Properties.color = col;
    }
    void Text::Render()
    {
        DrawTextEx(*(Properties.font), Properties.text.c_str(), position,Properties.fontSize,spacing, Properties.color);
    }
    void Text::RenderCentered()
    {
        auto TextSize = MeasureTextEx(*(Properties.font), Properties.text.c_str(), Properties.fontSize,spacing);

        DrawTextEx(*(Properties.font), Properties.text.c_str(), 
        Vector2{position.x - TextSize.x / 2, position.y - TextSize.y / 2}, 
        Properties.fontSize,spacing, Properties.color);
    }

} // namespace Blatformer
