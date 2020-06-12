#pragma once

#include <SFML/Window/Keyboard.hpp>

class getInput
{
private:
    ///
    ///
    ///
    static bool MovingUp();
    ///
    ///
    ///
    static bool MovingDown();
    ///
    ///
    ///
    static bool MovingLeft();
    ///
    ///
    ///
    static bool MovingRight();
public:
    ///
    ///
    ///
    static bool OnlyMovingUp();
    ///
    ///
    ///
    static bool OnlyMovingDown();
    ///
    ///
    ///
    static bool OnlyMovingLeft();
    ///
    ///
    ///
    static bool OnlyMovingRight();
};
