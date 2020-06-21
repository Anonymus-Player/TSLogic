#include "Gate.hpp"


TSLogic::Gate::Gate(const sf::FloatRect& Area, 
    const sf::Vector2f& Direction, const std::string& Filename)
    : GateArea{Area}, ComingDirection{Direction}, LevelFilename{Filename}
{}

std::pair< bool, std::string > TSLogic::Gate::Collides(
        const sf::FloatRect& EntityBounds, const sf::Vector2f& EntityDirection)
{
    if(EntityBounds.intersects(GateArea) && ComingDirection == EntityDirection)
    {
        return {true, LevelFilename};
    }
    else
    {
        return {false, std::string()};
    }
}