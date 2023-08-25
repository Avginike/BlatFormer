#pragma once

namespace BlatFormer
{
    template<typename T>
    class disableable
    {
        T data;
        bool Enabled = true;
    };
}
