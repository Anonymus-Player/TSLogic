#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

class SmartRect : public sf::RectangleShape
{
private:
    // Used for Collision logic
    static inline float PseudoLineThickness = 2.f;
    // Used for defining directions for collision instead of using magic numbers
    struct Axis
    {
        static inline const sf::Vector2f None = {0.f, 0.f};
        static inline const sf::Vector2f Vertical = {0.f, 1.f};
        static inline const sf::Vector2f Horizontal = {1.f, 0.f};
    };
    ///
    /// @brief This is where collision is check, but inwards
    ///
    /// @param OtherObject - The Object itself
    ///
    /// @return The Difference in order to correct to push in a appropriate direction 
    ///
    sf::Vector2f getInwardsCollision(const SmartRect& OtherObject);
    ///
    /// @brief This is where collision is check, but inwards and for collisions with the margin of the level
    ///
    /// @param OtherObjectFloatRect - The binding box of the object
    ///
    /// @return The Difference in order to correct to push in a appropriate direction 
    ///
    sf::Vector2f getInwardsCollision(const sf::FloatRect& OtherObjectFloatRect);
    ///
    /// @brief This is where collision is check, but outwards
    ///
    /// @param OtherObject - The Object itself
    ///
    /// @return The Difference in order to correct to push in a appropriate direction 
    ///
    sf::Vector2f getOutwardsCollision(const SmartRect& OtherObject);
    ///
    /// @brief Used for colliding with 2 moving objects in order to get the direction based on a "PesudoLine" (range area) in that direction
    ///
    /// @param OtherObject - The Object itself
    ///
    /// @return a Direction (see Directions declared below)
    ///
    sf::Vector2f getCollisionDirection(const SmartRect& OtherObject);
public:
    // Used for defining directions instead of using magic numbers
    struct Directions
    {
        static inline const sf::Vector2f Stop = {0.f, 0.f};
        static inline const sf::Vector2f Up = {0.f, -1.f};
        static inline const sf::Vector2f Down = {0.f, 1.f};
        static inline const sf::Vector2f Left = {-1.f, 0.f};
        static inline const sf::Vector2f Right = {1.f, 0.f};
    };
    // You got it
    enum class CollisionTypes
    {
        Inwards,
        Outwards
    };
    // This can be used lately for projectiles and other stuff
    sf::Vector2f FacingDirection = Directions::Stop;
    ///
    /// @brief I think this is self-explanatory
    ///
    /// @param DeltaTime - Time between frames
    ///
    /// @param Direction - Self-Explanatory
    ///
    /// @param SpeedFactor
    ///
    void moveRect(const float& DeltaTime, const sf::Vector2f& Direction, const float& SpeedFactor = 1.f);
    ///
    /// @brief Like .Intersect method of the float rect but It moves the entity (at this point)
    ///
    /// @param OtherObject - The object itself
    ///
    /// @param CollisionType - Idk, at this point I'm just lazy
    ///
    /// @return It is a Boolean. I don't think this needs explation
    ///
    bool CheckCollision(const SmartRect& OtherObject, const CollisionTypes& CollisionType);
    ///
    /// @brief Like .Intersect method of the float rect but It moves the entity (at this point)
    ///
    /// @param OtherObjectFloatRect - The bounding box of the object
    ///
    /// @warning This is used for inwards collision and needs to be used for the margins of the level 
    ///
    /// @return It is a Boolean. I don't think this needs explation
    ///
    bool CheckCollision(const sf::FloatRect& OtherObjectFloatRect);
};
