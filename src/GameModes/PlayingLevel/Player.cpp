#include "GameModes/PlayingLevel.hpp"
#include "main.hpp"
#include "UIElements/DebugConsole.hpp"
#include <raylib.h>
#include <raymath.h>
#include <iostream>


namespace BlatFormer
{
    Texture2D PlayingLevel::Player::PlayerTexture;
    void PlayingLevel::Player::Start()
    {
        PlayerTexture = LoadTexture(ASSETS_PATH"sprites/blat.png");
    }

    void PlayingLevel::Player::Render()
    {
        DrawTextureEx(PlayerTexture, position, 0, TILE_SIZE / PlayerTexture.height, WHITE);
    }
    void PlayingLevel::Player::Update()
    {
        
        OldPosition = position;
        static int Collision_Steps = 2;


        position.x += velocity.x * GetFrameTime();
        
        bool DidCollide = DoCollision();

        if(DidCollide && velocity.x < 0)
        {
            position.x = OldPosition.x;
            velocity.x = 0;
        }
        else if(DidCollide && velocity.x > 0)
        {
            position.x = OldPosition.x;
            velocity.x = 0;
        }
        else
        {
            OldPosition = position;
        }

        DidCollide = DoCollision();

        position.y += velocity.y * GetFrameTime();

       

        
        

        /*
        Vector2 PerStepSpeed = {velocity.x / Collision_Steps, velocity.y / Collision_Steps};

        for(int i = 0; i < Collision_Steps; i++)
        {
            position.x += PerStepSpeed.x * GetFrameTime();
            if(DoCollision())
            {
                position = OldPosition;
                break;
            }
        }
        OldPosition = position;

        for(int i = 0; i < Collision_Steps; i++)
        {
            position.y += PerStepSpeed.y * GetFrameTime();
            if(DoCollision())
            {
                position = OldPosition;
                break;
            }
        }
        */
        

        
        //x movement
        if(abs(velocity.x) < 200)
        {
            if(IsKeyDown(KEY_A))
            {
                velocity.x -= 50;
            }
            else if(IsKeyDown(KEY_D))
            {
                velocity.x += 50;
            }
            else
            {
                velocity.x *= DEACCELERATION_PASSIVE;
            }
        }
        else
        {
            velocity.x = Lerp(velocity.x, 0, DEACCELERATION_BY_SPEEDCAP);
        }
        
        if(!CheckRectangleOverlapsGround(GetGroundDetectRectangle()))
        {
            velocity.y += gravity;
            
        }        
        else
        {
            if(velocity.y > 0)
            {
                velocity.y = 0;
            }
            position.y = (int)position.y;
        }
        
        
        //y movement
       

        static bool DidGravityReduction = false;
        static bool IsJumping = false;

        

        if(CheckRectangleOverlapsGround(GetGroundDetectRectangle())
         && IsKeyPressed(KEY_SPACE))
        {
            
                velocity.y = -1000;
                IsJumping = true;
        }
        
        if(IsJumping)
        {
            if(!IsKeyDown(KEY_SPACE) || velocity.y > 0 )
            {
                velocity.y /= 4;
                IsJumping = false;
            }
           
           
        }


        DebugConsole::Log(IsJumping ? "Jumping" : "Not Jumping");
        
        if(CheckRectangleOverlapsGround(GetCeilingDetectRectangle()))
        {
           velocity.y = 0;
           position.y += 2;
            //IsHoldJump = false;
        }
        
        
        #ifdef DEBUG
            DrawRectangleLines(GetGroundDetectRectangle().x, GetGroundDetectRectangle().y, GetGroundDetectRectangle().width, GetGroundDetectRectangle().height, RED);
            DrawRectangleLines(GetCeilingDetectRectangle().x, GetCeilingDetectRectangle().y, GetCeilingDetectRectangle().width, GetCeilingDetectRectangle().height, RED);
        #endif 

    }
    bool PlayingLevel::Player::DoCollision()
    {
        for(int y = 0; y < TILES_VERTICAL + 1; y++)
        {
            for(int x = 0; x < TILES_HORIZONTAL; x++)
            {
                if(level->GetGrid(x, y) != 0)
                {
                    if(CheckCollision(GetPlayerRectangle(), Rectangle{ float(x * TILE_SIZE), float(y * TILE_SIZE), float(TILE_SIZE), float(TILE_SIZE)}))
                    {
                        return true;
                    }
                }
            }
        }
        
        return false;
    }
   
    bool PlayingLevel::Player::CheckCollision(Rectangle colliderA,Rectangle colliderB)
    {
        //check AABB collision without outputting the normals 
        if(colliderA.x + colliderA.width >= colliderB.x && colliderA.x <= colliderB.x + colliderB.width && colliderA.y + colliderA.height >= colliderB.y && colliderA.y <= colliderB.y + colliderB.height)
        {
            return true;
        }
        return false;
    }

    bool PlayingLevel::Player::CheckRectangleOverlapsGround(Rectangle Rect)
    {
        


        for(int i = 0; i < TILES_VERTICAL + 1; i++)
        {
            for(int j = 0; j < TILES_HORIZONTAL; j++)
            {
                if(level->GetGrid(j, i) != 0 && CheckCollision(Rect, Rectangle{ float(j * TILE_SIZE), float(i * TILE_SIZE), float(TILE_SIZE), float(TILE_SIZE)}))
                {
                    return true;
                }
            }
        }
        return false;

        
    }
    Rectangle PlayingLevel::Player::GetCeilingDetectRectangle()
    {
        return Rectangle{position.x, position.y - 1,(float) TILE_SIZE, (float)1};
    }
    Rectangle PlayingLevel::Player::GetGroundDetectRectangle()
    {
        return Rectangle{position.x, position.y + TILE_SIZE,(float) TILE_SIZE, (float)1};
    }
    Rectangle PlayingLevel::Player::GetPlayerRectangle()
    {
        return Rectangle{position.x, position.y, (float)TILE_SIZE, (float)TILE_SIZE};
    }
    
    

}