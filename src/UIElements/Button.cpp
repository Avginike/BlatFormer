#include <raylib.h>
#include <raymath.h>



#include "UIElements/Button.hpp"


namespace BlatFormer
{
    void Button::Update() 
    {
        Update(OnClickEvent);
    }
    void Button::Update(std::function<void(Button&)> ClickEvent) 
    {

        double k = 10 * GetFrameTime();

        if(CheckCollisionPointRec(GetMousePosition(), {position.x  - sizex / 2, position.y - sizey / 2, sizex, sizey}))
        {
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                ClickEvent(*this);
            }

            scale = Lerp(scale, 1.2, k);
        }
        else
            scale = Lerp(scale, 1, k);
            
    }
    void Button::Update(std::function<void()> ClickEvent)
    {
        Update([&](Button&){ClickEvent();});
    }

    void Button::Render()
    {
        sizex = size.x * scale;
        sizey = size.y * scale;

        Rectangle ScaledRectangle = Rectangle{position.x  - sizex / 2, position.y - sizey / 2, size.x * scale, size.y * scale};

        DrawRectangleRounded(ScaledRectangle,0.25,10, color);
        DrawRectangleRoundedLines(ScaledRectangle,0.25,10,2, BLACK);

        if(Label.text != "")
        {
            Vector2 TextSize = MeasureTextEx(*(Label.font), Label.text.c_str(), Label.fontSize * scale,Label.spacing);
            TextSize = Vector2Scale(TextSize, 0.5);

            DrawTextEx(*(Label.font), Label.text.c_str(), Vector2Subtract(position,TextSize),Label.fontSize * scale,Label.spacing, Label.color);
        }
    }

    


} // namespace BlatFormer
