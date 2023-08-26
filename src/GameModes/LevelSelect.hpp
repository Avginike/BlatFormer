#pragma once
#include "Menu.hpp"
#include "LevelSelect.hpp"
#include "main.hpp"
#include "Menus.hpp"
#include "DataStructures/Level.hpp"
#include "DataStructures/GameMode.hpp"

namespace BlatFormer
{
    



    template<typename T>
    class LevelSelect : public Menu
    {
        FilePathList GetLevels()
        {
            return LoadDirectoryFilesEx(LEVLES_PATH,".lvl",true);
        }
        string GetLevelName(string filepath)
        {
            size_t lastSlashPos = filepath.find_last_of("/\\");
            size_t lastDotPos = filepath.find_last_of(".");
            
            if (lastSlashPos == std::string::npos)
            {
                lastSlashPos = 0;
            }
            else
            {
                lastSlashPos++;
            }
            
            if (lastDotPos != std::string::npos && lastDotPos > lastSlashPos)
            {
                return filepath.substr(lastSlashPos, lastDotPos - lastSlashPos);
            }
            
            return filepath.substr(lastSlashPos);
        }
        public:
        
            void Start()
            {
                
                Buttons.push_back(Button(Vector2{105,(float)SCREEN_HEIGHT - 30},Vector2{200,50},BLACK,[&](){ExitMode();}));
                Buttons.front().Label = TextProperty{"Exit"};

                InitLevelButtons();
            }
            
            void InitLevelButtons()
            {
                FilePathList FileList = GetLevels();
                for(int i = 0; i < FileList.count; i++)
                {
                    Buttons.push_back(Button(Vector2{(float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2 + (float)i * 150},
                    Vector2{200,50},BLACK,
                    [=]()
                    {
                        auto mode = std::make_unique<T>( (string)FileList.paths[i]);
                        PushMode(std::move(mode));

                        
                    }));
                    
                    Buttons.back().Label = TextProperty{GetLevelName(FileList.paths[i])};
                }
            } 
            
            ~LevelSelect() = default;
            


    };

} // namespace BlatFormer
  