#pragma once

#include "../../Entity/Entity.hpp"

// Core class For Enemies
class Enemy : public Entity
{
protected:
    /// 
    /// @brief Used for analyzing input (random-generated or algorithm-generated)
    ///
    /// @return A predefined direction and a action to animate
    ///
    virtual std::pair< sf::Vector2f, Actions > getAction() = 0;
public:
    //
    enum class Type
    {
        Basic,
        Intelligent
    };
    ///
    /// @brief Enemy constructor, this is where enemy will be initialized
    ///
    /// @param Position - Where you want the enemy will be initially localized 
    ///
    /// @param Size - How big you want the enemy to be in pixel size
    ///
    /// @param TextureFilename - Path to the texture
    ///
    Enemy(const sf::Vector2f& Position, const sf::Vector2f& Size, const std::string& TextureFilename);
    ///
    /// @brief It occupies with moving, attacking, defending where is the case
    ///
    /// @param DeltaTime - Time between frames
    ///
    virtual void Update(float DeltaTime) = 0;
};

struct EnemyInfo : public EnityInfo
{
    //
    Enemy::Type Type;
};