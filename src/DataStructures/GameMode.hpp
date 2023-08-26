#pragma once
#include <vector>
#include <cstdint>
#include <string>
#include <stack>
#include <memory>

using namespace std;


namespace BlatFormer
{
    class GameMode
    {
        static std::stack<std::unique_ptr<GameMode>> modeStack;
        

        public:
            static bool GameHasToExit;
            static void ExitGame();
            

            static void SetEnterGameMode(std::unique_ptr<GameMode> mode);



            virtual void Render(){}
            virtual void Update(){}

           
            virtual void Start(){}
            virtual void End(){}

            void PushMode(std::unique_ptr<GameMode> mode);
            void ExitMode();

            static void UpdateCurrentMode();
            static void RenderCurrentMode();
            
           
    };

    
    

}