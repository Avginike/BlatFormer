#include "DataStructures/GameMode.hpp"
#include "Menu.hpp"
#include "LevelSelect.hpp"

#include <iostream>
#include <algorithm>

namespace BlatFormer
{
   
    void Menu::Render() 
    {
        void(*func)(UIElement&) = UIElement::Render;

        for_each(Buttons.begin(),Buttons.end(),func);
        for_each(Labels.begin(),Labels.end(),func);
    }
    void Menu::Update() 
    {
        void(*func)(UIElement&) = UIElement::Update;

        for_each(Buttons.begin(),Buttons.end(),func);
        for_each(Labels.begin(),Labels.end(),func);

        if(IsKeyPressed(KEY_ESCAPE))
        {
            ExitMode();
        }
    }
}