#pragma once

#include "../Core/Enemy.hpp"

class BasicEnemy : public Enemy
{
private:
    // Used for setting a know what distance
    float WalkingDistance = 0.f;
    // Used for Animation purposes
    Actions Action = Actions::None;
protected:
    /// 
    /// @brief Used for analyzing random-generated input
    ///
    /// @return A predefined direction and a action to animate
    ///
    virtual std::pair< sf::Vector2f, Actions > getAction() override;
public:
    ///
    /// @brief Enemy constructor, this is where enemy will be initialized
    ///
    /// @param Position - Where you want the enemy will be initially localized 
    ///
    /// @param Size - How big you want the enemy to be in pixel size
    ///
    /// @param TextureFilename - Path to the texture
    ///
    BasicEnemy(const sf::Vector2f& Position, const sf::Vector2f& Size, const std::string& TextureFilename);
    ///
    /// @brief It occupies with moving, attacking, defending where is the case
    ///
    /// @param DeltaTime - Time between frames
    ///
    virtual void Update(float DeltaTime) override;
};