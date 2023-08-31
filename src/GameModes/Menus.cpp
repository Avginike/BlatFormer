#include "DataStructures/GameMode.hpp"
#include "Menus.hpp"
#include "UIElements/Sprite.hpp"
#include "main.hpp"
#include "LevelSelect.hpp"

#include "LevelEditor.hpp"
#include "PlayingLevel.hpp"

#include <iostream>
#include <array>

#include <raymath.h>

namespace BlatFormer
{


    void MainMenu::Render() 
    {
        
        for(auto &Sprite : Sprites)
        {
            Sprite.Render();
        }

        GameNameOutline.RenderCentered();
        GameName.RenderCentered();
        
        PlayButton.Render();
        EditorButton.Render();
        ExitButton.Render();
        
    }
    void MainMenu::Update()
    {

        PlayButton.Update();
        EditorButton.Update();
        ExitButton.Update();

        if(IsKeyPressed(KEY_ESCAPE))
        {
            ExitMode();
        }
        
    }
    void MainMenu::Start()
    {

        


        ExitButton.OnClickEvent = [](){ ExitGame(); };
        EditorButton.OnClickEvent = [&](){ PushMode(std::make_unique<LevelSelect<LevelEditor>>()); };
        PlayButton.OnClickEvent = [&](){ PushMode(std::make_unique<LevelSelect<PlayingLevel>>()); };

        PlayButton.Label.text = "Start";
        EditorButton.Label.text = "Editor";
        ExitButton.Label.text = "Exit";

        EditorButton.position = Vector2Add(PlayButton.position, Vector2{0,75});
        ExitButton.position = Vector2Add(EditorButton.position, Vector2{0,75});

        GameNameOutline.position.x += 5;
        GameNameOutline.position.y += 5;
        
        GameName.Properties.color = WHITE;
        GameNameOutline.Properties.color = GRAY;
        

        int x{1};
        for(auto &texture: StarTextures)
        {
            texture = LoadTexture(((string)ASSETS_PATH + "sprites/stars" + to_string(x) + ".png").c_str());
            x++;
        }
        int y{0};
        for(auto &sprite : Sprites)
        {
            uint8_t random = GetRandomValue(0,5);
            
            float spritesize = 32;
            
            float spritey = 6 * (y + GetRandomValue(-90,90));
            float spritex =  8 * y - GetRandomValue(-30,30);

            sprite.position = {spritex,spritey};
            sprite.size = {spritesize,spritesize};
            sprite.texture = &(StarTextures)[random];
            
            y++;
        }
        
        
    }

}