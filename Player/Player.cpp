#include "Player.hpp"
#include <iostream>

Player::Player(const sf::Vector2f& Position, const sf::Vector2f& Size, const std::string& TextureFilename): 
    Entity(Position, Size)
{
    initEntityAnim(TextureFilename);
}

void Player::Update(float DeltaTime)
{
    auto [PlayerDirection, PlayerAction] = getAction();
    moveEntity(DeltaTime, PlayerDirection);
    EntityAnimate(PlayerAction);
}

std::pair< sf::Vector2f, Actions > Player::getAction()
{
    if(getInput::OnlyMovingUp())
        return {SmartRect::Directions::Up, Actions::MoveUp};
    else if(getInput::OnlyMovingDown())
        return {SmartRect::Directions::Down, Actions::MoveDown};
    else if(getInput::OnlyMovingLeft())
        return {SmartRect::Directions::Left, Actions::MoveLeft};
    else if(getInput::OnlyMovingRight())
        return {SmartRect::Directions::Right, Actions::MoveRight};
    else
        return {SmartRect::Directions::Stop, Actions::None};
}

void Player::setCameraSize(const sf::Vector2f& NewSize)
{
    PlayerCamera.setCameraSize(NewSize);
}

void Player::UpdateCamera()
{
    PlayerCamera.UpdateCamera(getGlobalBounds());
}

sf::View Player::getPlayerCamera()
{
    return PlayerCamera;
}

sf::Vector2f Player::getCameraSize()
{
    return PlayerCamera.getSize();
}

void Player::setLevelLimits(const sf::Vector2f& Limits)
{
    PlayerCamera.setLevelLimits(Limits);
}