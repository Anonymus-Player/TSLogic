#pragma once

#include <SFML/System/Clock.hpp>

#include "../Core/Enemy.hpp"

namespace TSLogic
{
    class IntelligentEnemy : public Enemy
    {
    private:
        // Used for avoiding it
        sf::FloatRect Obstacle = sf::FloatRect();
        // Used to store the player position in order to follow it
        static inline sf::Vector2f PlayerPos;
        // Used to set a treshold value in order to stop following on one of axis
        static inline float EnemySpeed;
        // The direction of the enemy in the moment of collision
        sf::Vector2f DirectionOnCollision = SmartRect::Directions::Stop;
        //
        static inline sf::Clock AttackClock;
        ///
        /// @brief Chooses the shorthest path according
        /// to the DirectionOnCollision variable
        ///
        /// @return A predefined direction and a action
        /// to animate in case of collision with an obstacle
        ///
        std::pair< sf::Vector2f, Actions > AvoidObstacle();
        ///
        /// @brief Follows player and if it is colliding calls AvoidObstacle()
        ///
        /// @return A predefined direction and a action to animate
        ///
        virtual std::pair< sf::Vector2f, Actions > getAction() override;
        ///
        /// @brief Checks if it is colliding with an obstacle
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
        /// @brief Sets the Obstacle variable information such as: position and size
        ///
        /// @param ObstacleRect - The Globalbounds of the obstacle
        ///
        void setObstacleInfo(const sf::FloatRect& ObstacleRect);
        ///
        /// @brief Sets where is the player across all instances
        ///
        /// @param Destination - Player position
        ///
        static void setDestinationPos(const sf::Vector2f& Destination);
        ///
        ///
        ///
        bool ReadyToAttack() override;
    };
}