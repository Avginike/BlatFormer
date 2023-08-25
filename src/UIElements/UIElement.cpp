#include "UIElement.hpp"

namespace BlatFormer
{
    void UIElement::Render(UIElement &Element) 
    {
        Element.Render();
    }
    void UIElement::Update(UIElement &Element)
    {
        Element.Update();
    }
} // namespace BlatFormer
