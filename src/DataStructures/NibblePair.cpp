#include "NibblePair.hpp"

namespace BlatFormer
{
    NibblePair::NibblePair():LH{0}{}
    
    uint8_t NibblePair::GetH()
    {
        return LH & 0x0F;
    }
    uint8_t NibblePair::GetL()
    {
        return (LH & 0xF0) >> 4;
    }
    void NibblePair::SetH(uint8_t val)
    {
        LH = (LH & 0xF0) | (val & 0x0F);
    }
    void NibblePair::SetL(uint8_t val)
    {
        LH = (LH & 0x0F) | (val << 4);
    }

}