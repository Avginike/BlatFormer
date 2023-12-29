#include "DebugConsole.hpp"
#include "main.hpp"
#include <raylib.h>

namespace BlatFormer 
{
    namespace DebugConsole
    {
        namespace
        {
            std::list<std::string> LogList;
        }

        void Render()
        {
            DrawRectangle(0,0,SCREEN_WIDTH / 6, SCREEN_HEIGHT / 7, {100,0,0,100});
            
            int n = 0;
            for(auto i = LogList.rbegin(); i != LogList.rend(); i++, n++)
            {
                DrawText( i->c_str(), 0, n * 20, 10, WHITE);
            }

        }

        void Log(std::string Message) 
        {
            LogList.push_back(Message);
            if(LogList.size() > 10)
            {
                LogList.pop_front();
            }
        }
    }

}
