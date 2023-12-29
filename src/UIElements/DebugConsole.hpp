#pragma once

#include <string>
#include <list>

namespace BlatFormer
{
    namespace DebugConsole
    {
        namespace
        {
            extern std::list<std::string> LogList;
        }
        void Render();
        void Log(std::string Message);  
    }
}