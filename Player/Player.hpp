#pragma once

#include "../Entity/Entity.hpp"
#include  "EventHandler/EventHandler.hpp"
#include "Camera/Camera.hpp"

struct PlayerInfo : public EnityInfo
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
public:
    ///
    /// @brief The Initializer
    /// 
    Player(const sf::Vector2f& Position, const sf::Vector2f& Size, const std::string& TextureFilename);
    ///
    /// @brief Used for scaling the Cmera in order to support multiple resoultions 
    ///
    /// @param NewSize - The size of window after beeing resized
    ///
    void setCameraSize(const sf::Vector2f& NewSize);
    ///
    /// @brief Gets the size of what the player sees
    ///
    /// @return The size represented in a sf::Vector2f
    ///
    sf::Vector2f getCameraSize();
    ///
    /// @brief Calls all function like: UpdateView and ProcessInput
    ///
    /// @param DeltaTime - Time between frames
    ///
    void Update(float DeltaTime);
    ///
    /// @return Player's camera
    ///
    sf::View getPlayerCamera();
    ///
    /// @brief Setup "The Level Border" 
    ///
    /// @param Limits - The Size of the level
    ///
    void setLevelLimits(const sf::Vector2f& Limits);
    ///
    /// @brief Does what you see
    ///
    void UpdateCamera();
};