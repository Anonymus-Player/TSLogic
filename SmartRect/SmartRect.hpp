#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

namespace TSLogic
{
    class SmartRect : public sf::RectangleShape
    {
    private:
        // Used for Collision logic
        static inline float PseudoLineThickness = 2.f;
        // Used for defining directions for
        // collision instead of using magic numbers
        struct Axis
        {
            static inline const sf::Vector2f None = {0.f, 0.f};
            static inline const sf::Vector2f Vertical = {0.f, 1.f};
            static inline const sf::Vector2f Horizontal = {1.f, 0.f};
        };
        ///
        /// @brief This is where collision is check, but inwards
        ///
        /// @param OtherObject - The Object that
        /// is trying to escape from this one
        ///
        /// @return The Difference in order to correct
        /// to push in a appropriate direction 
        ///
        sf::Vector2f getInwardsCollision(const SmartRect& OtherObject);
        ///
        /// @brief This is where collision is check, but inwards
        /// and for collisions with the margin of the level
        ///
        /// @param Border - The binding box of the object
        ///
        /// @return The Difference in order to
        /// correct to push in a appropriate direction 
        ///
        sf::Vector2f getInwardsCollision(const sf::FloatRect& Border);
        ///
        /// @brief This is where collision is check, but outwards
        ///
        /// @param OtherObject - The Object that
        /// is trying to enter in this one
        ///
        /// @return The Difference in order to
        /// correct to push in a appropriate direction 
        ///
        sf::Vector2f getOutwardsCollision(const SmartRect& OtherObject);
        ///
        /// @brief Used for colliding with 2 moving objects
        /// in order to get the direction based on a
        /// "PseudoLine" (range area) in that direction
        ///
        /// @param OtherObject - The Object that is colliding with this one
        ///
        /// @return One of the possible Directions
        ///
        /// @see SmartRect::Directions (declared below)
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
        // And it's used for Collision reaction
        sf::Vector2f FacingDirection = Directions::Stop;
        ///
        /// @brief Moves the object to a desired
        /// direction, with a frame independent
        /// speed and a modifiable Speed factor
        ///
        /// @param DeltaTime - Time between frames
        ///
        /// @param Direction - Where do you want to move
        ///
        /// @param SpeedFactor - How fast do you want to move
        ///
        void moveRect(const float& DeltaTime, const sf::Vector2f& Direction, const float& SpeedFactor = 1.f);
        ///
        /// @brief Like .Intersect method of the sf::FloatRect,
        /// but it moves the object (at this point)
        ///
        /// @param OtherObject - The Object that is colliding with this one
        ///
        /// @param CollisionType - What type of boject collision it is
        ///
        /// @return A confirmation that "ThisObject" collided with "OtherObject"
        ///
        bool CheckCollision(const SmartRect& OtherObject, const CollisionTypes& CollisionType);
        ///
        /// @brief Like .Intersect method of the sf::FloatRect,
        /// but It moves the entity (at this point)
        ///
        /// @param Border - The bounding box of the object
        ///
        /// @note This is used for inwards collision and
        /// needs to be used for the margins of the map
        ///
        /// @return A confirmation that this object tried to escape
        ///
        bool CheckCollision(const sf::FloatRect& Border);
    };
} 