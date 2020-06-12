#include "EventHandler.hpp"

bool getInput::OnlyMovingUp()
{
    return MovingUp() && !MovingDown() && !MovingLeft() && !MovingRight();
}

bool getInput::OnlyMovingDown()
{
    return MovingDown() && !MovingUp() && !MovingLeft() && !MovingRight();
}

bool getInput::OnlyMovingLeft()
{
    return MovingLeft() && !MovingUp() && !MovingDown() && !MovingRight();
}

bool getInput::OnlyMovingRight()
{
    return MovingRight() && !MovingUp() && !MovingDown() && !MovingLeft();
}

bool getInput::MovingUp()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::W);
}

bool getInput::MovingDown()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::S);
}

bool getInput::MovingLeft()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::A);
}

bool getInput::MovingRight()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::D);
}