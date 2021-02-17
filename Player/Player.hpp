#pragma once

#include <SFML/System/Clock.hpp>

#include "../Enemy/Core/Enemy.hpp"
#include  "EventHandler/EventHandler.hpp"
#include "Camera/Camera.hpp"

namespace TSLogic
{
    // Basic information about player
    struct PlayerInfo : public EntityInfo
    {};

    class Player : public Entity 
    {
    private:
        /// 
        /// @brief Used for analyzing input  
        ///
        /// @return A predefined direction and a action to animate
        ///
        std::pair< sf::Vector2f, Actions > getAction();
        // Player's perspective
        Camera PlayerCamera;
        //
        sf::Clock AttackClock;
        //
        float CoolDownTime = 1.f;
    public:
        ///
        /// @brief The Initializer
        /// 
        Player(const sf::Vector2f& Position, const sf::Vector2f& Size, const std::string& TextureFilename);
        ///
        /// @brief Used for scaling the Camera in 
        /// order to support multiple resolutions 
        ///
        /// @param NewSize - The size of window after beeing resized
        ///
        void setCameraSize(const sf::Vector2f& NewSize);
        ///
        ///
        ///
        void AttackEnemy(Enemy& Other);
        ///
        /// @brief Gets the size of what the player sees
        ///
        /// @return The size represented as a sf::Vector2f
        ///
        sf::Vector2f getCameraSize();
        ///
        /// @brief Calls all function like: UpdateView and ProcessInput
        ///
        /// @param DeltaTime - The time between each frame
        ///
        void Update(float DeltaTime);
        ///
        /// @brief Gets the player's perspective
        ///
        /// @return The current perspective of the player
        ///
        sf::View getPlayerCamera();
        ///
        /// @brief Setups How far the camera can go 
        ///
        /// @param Limits - The Size of the level
        ///
        void setCameraLimits(const sf::Vector2f& Limits);
        ///
        /// @brief It update the player's view
        ///
        void UpdateCamera();
    };
}