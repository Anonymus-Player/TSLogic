#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <string>

namespace TSLogic
{
    struct GateInfo
    {
        // Where the next level is located
        std::string LevelFilename;
        // The gate bounds
        sf::FloatRect GateArea;
    };

    class Gate
    {
    private:
        // The gate bounds
        sf::FloatRect GateArea;
        // The direction that the protagonist should come
        sf::Vector2f ComingDirection;
        // Where the next level is located
        std::string LevelFilename;
    public:
        ///
        /// @brief Initialize a new gate to another level
        ///
        /// @param Area - Where it is and how big it is
        ///
        /// @param Filename - Where the next level is
        ///
        /// @param Direction - In what direction
        /// the protagonist should come
        ///
        /// @see SmartRect/SmartRect.hpp::TSLogic::SmartRect::Directions
        ///
        /// @note Because TSLogic::LevelParser uses JSON
        /// your level file needs to be: WhateverLevel.json
        ///
        Gate(const sf::FloatRect& Area, 
            const sf::Vector2f& Direction, const std::string& Filename);
        ///
        /// @brief Check if an entity collides with the gate
        ///
        /// @param EntityBounds - The bounding box of the entity
        ///
        /// @param EntityDirection - What's the direction of the entity
        ///
        /// @return A confirmation that it collided
        ///
        std::pair< bool, std::string > Collides(const sf::FloatRect& EntityBounds, 
            const sf::Vector2f& EntityDirection);
    };
}