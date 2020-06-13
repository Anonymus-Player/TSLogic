#include "EventHandler.hpp"

bool TSLogic::getInput::OnlyMovingUp()
{
    return MovingUp() && !MovingDown() && !MovingLeft() && !MovingRight();
}

bool TSLogic::getInput::OnlyMovingDown()
{
    return MovingDown() && !MovingUp() && !MovingLeft() && !MovingRight();
}

bool TSLogic::getInput::OnlyMovingLeft()
{
    return MovingLeft() && !MovingUp() && !MovingDown() && !MovingRight();
}

bool TSLogic::getInput::OnlyMovingRight()
{
    return MovingRight() && !MovingUp() && !MovingDown() && !MovingLeft();
}

bool TSLogic::getInput::MovingUp()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::W);
}

bool TSLogic::getInput::MovingDown()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::S);
}

bool TSLogic::getInput::MovingLeft()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::A);
}

bool TSLogic::getInput::MovingRight()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::D);
}