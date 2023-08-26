#include "GameMode.hpp"




namespace BlatFormer {

    std::stack<std::unique_ptr<GameMode>> GameMode::modeStack = std::stack<std::unique_ptr<GameMode>>();
    bool GameMode::GameHasToExit = false;
    void GameMode::SetEnterGameMode(std::unique_ptr<GameMode> mode) 
    {
        modeStack.push(std::move(mode));
        modeStack.top()->Start();

    }
    void GameMode::PushMode(std::unique_ptr<GameMode> mode) 
    {
        End();
        modeStack.push(std::move(mode)); 
        modeStack.top()->Start();
    }
    void GameMode::ExitMode()
    {
        End();
        
        if(modeStack.size() > 1)
        {
            modeStack.pop();
        }
        else
        {
            ExitGame();
        }
        
    }
    void GameMode::RenderCurrentMode() 
    {
        modeStack.top()->Render();
    }
    void GameMode::UpdateCurrentMode() 
    {
        modeStack.top()->Update();
    }
    void GameMode::ExitGame()
    {
        GameHasToExit = true;
    }
    
}