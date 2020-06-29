#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

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
        ///
        /// @brief Check if you pressed the Left button from the mouse
        ///
        /// @return A confirmation that you did push it
        ///
        static bool Attacking();
        ///
        /// @brief Check if you pressed the Right button from the mouse
        ///
        /// @return A confirmation that you did push it
        ///
        static bool Defending();
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
        ///
        /// @brief Check if you pressed only the Left
        /// button on your mouse between this and the
        /// other one supplied in the Defending method
        ///
        /// @return A confirmation that you did push it
        ///
        static bool OnlyAttacking();
        ///
        /// @brief Check if you pressed only the Right
        /// button on your mouse between this and the
        /// other one supplied in the Attacking method
        ///
        /// @return A confirmation that you did push it
        ///
        static bool OnlyDefending();
    };
}