#pragma once

#include <SFML/Graphics/View.hpp>

namespace TSLogic
{
    class Camera : public sf::View
    {
    private:
        // Collision types
        enum class Collisions
        {
            Nope,
            Up,
            Down,
            Left,
            Right
        };
        ///
        /// @brief Get a specific (sort of) direction accordingly
        ///
        /// @return A direction axy and if it exceed a limit
        ///
        sf::Vector2f getCameraDirection();
        ///
        /// @brief This function in order to
        /// returns what type of collision it is
        ///
        /// @return A camera collision type
        ///
        /// @see Camera::Collisions
        ///
        Camera::Collisions getCollisionType();
        ///
        /// @brief After exceeding the limit the moving
        /// function will have a little but semnificative
        /// error and this function will correct it
        ///
        /// @param CollisionType - What type of camera collision it is
        ///
        /// @see Camera::Collisions
        ///
        void correctCamera(const Camera::Collisions& CollisionType);
        // The position of the central point in Player rectangle
        sf::Vector2f PlayerCentralPosition;
        // The area where the player can act
        sf::Vector2f LevelLimits;
        // Used for scaling the camera
        float ScaleFactor = 1;
        // Used for defining directions instead of using magic numbers
        struct Axis
        {
            static inline const sf::Vector2f None = {0, 0};
            static inline const sf::Vector2f Vertical = {0, 1};
            static inline const sf::Vector2f Horizontal = {1, 0};
        };
        ///
        /// @brief Getting the central position with a formula
        ///
        /// @return The Central Position Used by the View
        ///
        sf::Vector2f getPlayerCenterPosition(const sf::FloatRect& PlayerRect);
        ///
        /// @brief Compares the vertical side of the new window size
        ///
        /// @param NewSize - The new vertical size of the window
        ///
        /// @return The evaluation of that comparison
        ///
        bool CompareVSize(const float& NewSize);
        ///
        /// @brief Compares the horizontal side of the new window size
        ///
        /// @param NewSize - The new horizontal size of the window
        ///
        /// @return The evaluation of that comparison
        ///
        bool CompareHSize(const float& NewSize);
        ///
        /// @brief Evaluates the horizontal an the vertical
        /// comparisons from the functions upper
        ///
        /// @param NewSize - The new size of the window
        ///
        /// @return The evaluation of that comparison
        ///
        bool SizeEval(const sf::Vector2f& NewSize);
        // How big the camera is
        sf::Vector2f CameraSize = {0.f, 0.f};
    public:
        ///
        /// @brief Used for scaling the perspective
        /// in order to support multiple resoultions 
        ///
        /// @param NewSize - The size of window after beeing resized
        ///
        void setCameraSize(const sf::Vector2f& NewSize);
        ///
        /// @brief Setups How far the camera can go
        ///
        /// @param Limits - The Size of the map
        ///
        void setCameraLimits(const sf::Vector2f& Limits);
        ///
        /// @brief It updates the camera every frame
        ///
        void UpdateCamera(const sf::FloatRect& EntityCenter);
    };
}