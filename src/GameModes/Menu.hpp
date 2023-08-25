#pragma once

#include "DataStructures/GameMode.hpp"
#include "UIElements/Text.hpp"
#include "UIElements/Button.hpp"

#include <vector>


namespace BlatFormer
{
    class Menu : public GameMode
    {
        

        public:
            vector<Button> Buttons;
            vector<Text> Labels;
            
            
        virtual void Render();
        virtual void Update();
     

    };
}