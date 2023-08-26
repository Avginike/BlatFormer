#pragma once
#include "DataStructures/GameMode.hpp"
#include "UIElements/UIElement.hpp"

#include <raylib.h>

namespace BlatFormer
{
    class PlayingLevel: public GameMode
    {
        void Start();
        
        void Update();
        void Render();

        class Player: public UIElement
        {
            friend class PlayingLevel;

            static Texture2D PlayerTexture;

            public:
                void Render();
                void Update();
        };

    };

}