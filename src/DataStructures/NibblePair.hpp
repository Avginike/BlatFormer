#pragma once
#include <cstdint>


namespace BlatFormer
{
    struct NibblePair
    {
        uint8_t LH;
    
        NibblePair();

        uint8_t GetL();
        uint8_t GetH();

        void SetL(uint8_t val);
        void SetH(uint8_t val);

    };
}