#include "GameMode.hpp"




namespace BlatFormer {

    std::stack<std::unique_ptr<GameMode>> GameMode::modeStack = std::stack<std::unique_ptr<GameMode>>();
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
        modeStack.pop();
        
    }
    void GameMode::RenderCurrentMode() 
    {
        modeStack.top()->Render();
    }
    void GameMode::UpdateCurrentMode() 
    {
        modeStack.top()->Update();
    }
}