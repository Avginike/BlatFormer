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
        position.x += velocity.x * GetFrameTime();
        position.y += velocity.y * GetFrameTime();

        if(!IsGrounded())
        {
            velocity.y += gravity;
        }
        else
        {
            velocity.y = 0;
        }


        if(abs(velocity.x) < 200)
        {
            if(IsKeyDown(KEY_A))
            {
                velocity.x -= 25;
            }
            else if(IsKeyDown(KEY_D))
            {
                velocity.x += 25;
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

        static bool DidGravityReduction = false;
        static bool IsHoldJump = false;

        if(IsKeyPressed(KEY_SPACE) && IsGrounded())
        {
            IsHoldJump = true;
            velocity.y = -300;
        }
        if(IsKeyDown(KEY_SPACE) && (jumptime < MAX_JUMP_TIME) && IsHoldJump)
        {
            
            velocity.y = -300;
            jumptime += GetFrameTime();
            cout << jumptime << endl;
            if(jumptime > MAX_JUMP_TIME * 2/3 && !DidGravityReduction)
            {
                gravity /= 3;
                DidGravityReduction = true;
                cout << "gravity reduced" << endl;
            }
            
        }
        else
        {
            IsHoldJump = false;
            DidGravityReduction = false;
            gravity = GRAVITY_BASE;
            jumptime = 0;
        }
        
        for(int i = 0; i < TILES_VERTICAL + 1; i++)
        {
            for(int j = 0; j < TILES_HORIZONTAL; j++)
            {
                if(level->GetGrid(j, i) != 0)
                {
                    float NormalX;
                    float NormalY;
                    float collisiontime = CheckCollision(Rectangle{ float(j * TILE_SIZE), float(i * TILE_SIZE), float(TILE_SIZE), float(TILE_SIZE)}, NormalX, NormalY);
                    

                    if(collisiontime != 1.0f)
                    {
                        
                        float remainingtime = 1.0f - collisiontime;
                        position.x += velocity.x * collisiontime; 
                        position.y += velocity.y * collisiontime;
                        level->SetGrid(j,i,2);

                        float DotProduct = Vector2DotProduct(Vector2{velocity.x, velocity.y}, Vector2{NormalX, NormalY}) * remainingtime;
                        velocity.x = DotProduct * NormalY;
                        velocity.y = DotProduct * NormalX;

                    }
                    
                }
            }
        }
        


    }
    float PlayingLevel::Player::CheckCollision(Rectangle collider, float& NormalX, float& NormalY)
    {
        float xInvEntry, yInvEntry;
        float xInvExit, yInvExit;

        if(velocity.x > 0.0f)
        {
            xInvEntry = collider.x - (position.x + TILE_SIZE);
            xInvExit = (collider.x + collider.width) - position.x;
        }
        else
        {
            xInvEntry = (collider.x + collider.width) - position.x;
            xInvExit = collider.x - (position.x + TILE_SIZE);
        }
        if(velocity.y > 0.0f)
        {
            yInvEntry = collider.y - (position.y + TILE_SIZE);
            yInvExit = (collider.y + collider.height) - position.y;
        }
        else
        {
            yInvEntry = (collider.y + collider.height) - position.y;
            yInvExit = collider.y - (position.y + TILE_SIZE);
        }

        float xEntry, yEntry;
        float xExit, yExit;
        if(velocity.x == 0)
        {
            xInvEntry = -std::numeric_limits<float>::infinity();
            xInvExit = std::numeric_limits<float>::infinity();
        }
        else
        {
            xEntry = xInvEntry / velocity.x;
            xExit = xInvExit / velocity.x;
        }
        if(velocity.y == 0)
        {
            yInvEntry = -std::numeric_limits<float>::infinity();
            yInvExit = std::numeric_limits<float>::infinity();
        }
        else
        {
            yEntry = yInvEntry / velocity.y;
            yExit = yInvExit / velocity.y;
        }
        float entryTime = std::max(xEntry, yEntry); 
        float exitTime = std::min(xExit, yExit);

        if(entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f) 
        { 
            NormalX = 0.0f; 
            NormalY = 0.0f; 
            return 1.0f; 
        }
        else // if there was a collision 
        { 
            // calculate normal of collided surface
            if (xEntry > yEntry) 
            { 
                if (xInvEntry < 0.0f) 
                { 
                    NormalX = 1.0f; 
                    NormalY = 0.0f; 
                } 
                else 
                { 
                    NormalX = -1.0f; 
                    NormalY = 0.0f;
                } 
            } 
            else 
            { 
                if (yInvEntry < 0.0f) 
                { 
                    NormalX = 0.0f; 
                    NormalY = 1.0f; 
                } 
                else 
                { 
                    NormalX = 0.0f; 
                    NormalY = -1.0f; 
                } 
            } 
            return entryTime;
        }
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

    bool PlayingLevel::Player::IsGrounded()
    {
        uint8_t HigherThanBottom = static_cast<uint8_t>(position.y / TILE_SIZE);

        Rectangle BottomRectangle = GetGroundDetectRectangle();

        for(int i = HigherThanBottom; i < TILES_VERTICAL + 1; i++)
        {
            for(int j = 0; j < TILES_HORIZONTAL; j++)
            {
                if(level->GetGrid(j, i) != 0 && CheckCollision(BottomRectangle, Rectangle{ float(j * TILE_SIZE), float(i * TILE_SIZE), float(TILE_SIZE), float(TILE_SIZE)}))
                {
                    position.y = Lerp(position.y, i * TILE_SIZE - TILE_SIZE, pow(1, GetFrameTime()));
                    return true;
                }
            }
        }
        return false;

        
    }
    Rectangle PlayingLevel::Player::GetGroundDetectRectangle()
    {
        return Rectangle{position.x, position.y + TILE_SIZE - TILE_SIZE / 12,(float) TILE_SIZE, (float)TILE_SIZE / 12};
    }
    Rectangle PlayingLevel::Player::GetPlayerRectangle()
    {
        return Rectangle{position.x, position.y, (float)PlayerTexture.height, (float)PlayerTexture.width};
    }
    
    

}