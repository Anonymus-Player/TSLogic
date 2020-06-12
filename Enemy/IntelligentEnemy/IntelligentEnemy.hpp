#pragma once

#include "../Core/Enemy.hpp"

class IntelligentEnemy : public Enemy
{
private:
    // Used for eviting it
    sf::FloatRect Obstcale = sf::FloatRect();
    // Used to store the player position in order to follow it
    static inline sf::Vector2f PlayerPos;
    // Used to set a treshold value in order to stop following on one of axis
    static inline float EnemySpeed;
    // The direction of the enemy in the mooment of collision
    sf::Vector2f DirectionOnCollision = SmartRect::Directions::Stop;
    ///
    /// @brief Chooses the shorthest path according to the DirectionOnCollision variable
    ///
    /// @return A predefined direction and a action to animate in case of collision with an obstcale
    ///
    std::pair< sf::Vector2f, Actions > EvitObstacle();
    ///
    /// @brief Follows player and if it is colliding calls EvitObstcale()
    ///
    /// @return A predefined direction and a action to animate
    ///
    virtual std::pair< sf::Vector2f, Actions > getAction() override;
    ///
    /// @brief Checks if it is colliding with an obstcale
    ///
    /// @return True if it does, False if it doesn't
    ///
    bool isColliding();
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
    IntelligentEnemy(const sf::Vector2f& Position, const sf::Vector2f& Size, const std::string& TextureFilename);
    ///
    /// @brief It occupies with moving, attacking, defending where is the case
    ///
    /// @param DeltaTime - Time between frames
    ///
    virtual void Update(float DeltaTime) override;
    ///
    /// @brief Sets the Obstcale varibale information such as: position and size
    ///
    /// @param ObstcaleRect - The Globalbounds of the obstcale
    ///
    void setObstcaleInfo(const sf::FloatRect& ObstacaleRect);
    ///
    /// @brief Sets where is the player across all instances
    ///
    /// @param Destination - Player position
    ///
    static void setDestinationPos(const sf::Vector2f& Destination);
};
