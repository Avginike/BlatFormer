#pragma once
#include "DataStructures/Level.hpp"
#include "UIElements/UIElement.hpp"

#include <raylib.h>
#include <string>

namespace BlatFormer
{
   
    class PlayingLevel: public Level
    {
        class Player: public UIElement
        {
            friend class PlayingLevel;

            const float GRAVITY_BASE = 9.18f * 2;
            const float DEACCELERATION_BY_SPEEDCAP = 0.1f;
            const float DEACCELERATION_PASSIVE = 0.9f;
            const float MAX_JUMP_TIME = 0.2f;

        

            bool grounded{false};
            static Texture2D PlayerTexture;

            Vector2 velocity{0};
            float jumptime{0};
            float gravity = 9.18f;

            inline Rectangle GetGroundDetectRectangle();
            inline Rectangle GetPlayerRectangle();
            
            Level* level;

            float CheckCollision(Rectangle collider, float& NormalX, float& NormalY);
            
            bool CheckCollision(Rectangle colliderA,Rectangle colliderB);
            bool IsGrounded();

            public:
                void Start();
                void Render();
                void Update();
                Player(Level* PlayingLevel):level(PlayingLevel){ };

        };
        Player player;
        public:
            void Start();
            
            void Update();
            void Render();

            

            PlayingLevel(string filepath): Level(filepath), player(this){};

    };

}