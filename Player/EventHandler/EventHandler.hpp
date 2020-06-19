#pragma once

#include <SFML/Window/Keyboard.hpp>

namespace TSLogic
{
    class getInput
    {
    private:
        ///
        /// @brief Check if you pressed the W key on your keyboard
        ///
        /// @return A confirmation that you did push it
        ///
        static bool MovingUp();
        ///
        /// @brief Check if you pressed the S key on your keyboard
        ///
        /// @return A confirmation that you did push it
        ///
        static bool MovingDown();
        ///
        /// @brief Check if you pressed the A key on your keyboard
        ///
        /// @return A confirmation that you did push it
        ///
        static bool MovingLeft();
        ///
        /// @brief Check if you pressed the D key on your keyboard
        ///
        /// @return A confirmation that you did push it
        ///
        static bool MovingRight();
    public:
        ///
        /// @brief Check if you pressed only the W key
        /// on your keyboard between all other supplied
        /// in the Moving... methods
        ///
        /// @return A confirmation that you did push it
        ///
        static bool OnlyMovingUp();
        ///
        /// @brief Check if you pressed only the S key
        /// on your keyboard between all other supplied
        /// in the Moving... methods
        ///
        /// @return A confirmation that you did push it
        ///
        static bool OnlyMovingDown();
        ///
        /// @brief Check if you pressed only the A key
        /// on your keyboard between all other supplied
        /// in the Moving... methods
        ///
        /// @return A confirmation that you did push it
        ///
        static bool OnlyMovingLeft();
        ///
        /// @brief Check if you pressed only the D key
        /// on your keyboard between all other supplied
        /// in the Moving... methods
        ///
        /// @return A confirmation that you did push it
        ///
        static bool OnlyMovingRight();
    };
}