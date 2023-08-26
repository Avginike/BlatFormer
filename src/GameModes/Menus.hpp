#pragma once
#include "DataStructures/GameMode.hpp"
#include "UIElements/Text.hpp"
#include "main.hpp"
#include "UIElements/Sprite.hpp"
#include "UIElements/Button.hpp"
#include "Menu.hpp"
#include "DataStructures/Disableable.hpp"

#include <array>
#include <iostream>

namespace BlatFormer
{


    class MenuTest : public Menu
    {
        void Start();
    };


    class MainMenu : public Menu
    {
        

        Text GameName{Vector2{(float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2 - 100},"Cyka Blat!",70};
        Text GameNameOutline{GameName};

        Button PlayButton{
            Vector2{(float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2},Vector2{200,50},
            BLACK,[](){std::cout << "Button Pressed!";}};

        Button EditorButton = PlayButton;
        Button ExitButton = PlayButton;


        std::array<Texture2D,6> StarTextures;
        Sprite Sprites[100]{};

        public:
            MainMenu() = default;
            void Render();
            void Update();
            void Start();

    };

}