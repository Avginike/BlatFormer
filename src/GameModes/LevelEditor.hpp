#pragma once

#include "DataStructures/Level.hpp"
#include "UIElements/UIElement.hpp"

namespace BlatFormer
{
    class LevelEditor : public Level
    {
        
        const double MaxEditorOffset = 10;
        const float EditorMoveSpeed = 0.09f;
    
        float scale{1};



        double xOffset{0};
        double yOffset{0};

        void DrawGrid(double xOffset, double yOffset, float scale);

        class TileSelector: public UIElement
        {  
            friend class LevelEditor;
            static Texture2D EraserTexture;

            uint8_t CurrentBlockID{0};
            public:
                void Update();
                void Render();

            
        };

        TileSelector Selector{};

        public:
            void Update();
            void Render();
            void Start();

            LevelEditor(string filepath): Level(filepath){};  
    };


}
