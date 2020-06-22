#include "Barries.hpp"

void TSLogic::Barriers::loadBarriers(const std::vector< BarrierInfo >& BarrierBounds)
{
    SmartRect Rect;

    for(auto& Bound : BarrierBounds)
    {
        Rect.setPosition({Bound.first.left, Bound.first.top});
        Rect.setSize({Bound.first.width, Bound.first.height});
        BarrierRects.emplace_back(BarrierCore{Rect, Bound.second});
    }
}

void TSLogic::Barriers::CheckCollision(Entity& Person)
{
    for(auto& BarrierRect : BarrierRects)
    {
        Person.CheckCollision(BarrierRect.first, BarrierRect.second);
    }
}

void TSLogic::Barriers::clear()
{
    BarrierRects.clear();
}