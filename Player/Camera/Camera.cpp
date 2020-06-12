#include "Camera.hpp"
#include "../../CentralStuff/TypeDefs.hpp"
#include "../../CentralStuff/CoreFunctions.hpp"

void Camera::setCameraSize(const sf::Vector2f& NewSize)
{
    float ScaleFactor = 1;
    while(NewSize.x / ScaleFactor > DefaultSize.x || NewSize.y / ScaleFactor > DefaultSize.y)
        ScaleFactor++;
    setSize(NewSize.x / ScaleFactor, NewSize.y / ScaleFactor);
    CameraSize = {NewSize.x / ScaleFactor, NewSize.y / ScaleFactor};
}

void Camera::UpdateCamera(const sf::FloatRect& EntityCenter)
{
    PlayerCentralPosition = getPlayerCenterPosition(EntityCenter);
    sf::Vector2f Direction = getCameraDirection();
    sf::Vector2f PositionDiff = PlayerCentralPosition - getCenter();
    
    move(Direction * PositionDiff);
    Collisions CollisionType = getCollisionType();
    correctCamera(CollisionType);
}

void Camera::correctCamera(const Camera::Collisions& CollisionType)
{
    sf::Vector2f CameraPosition = getCenter();
    sf::Vector2f SuperiorLimitsDiff = LevelLimits - (CameraPosition + CameraSize / 2.f);
    sf::Vector2f InferiorLimitsDiff = CameraPosition - CameraSize / 2.f;

    if(CollisionType == Collisions::Up)
        move(Axis::Vertical * -InferiorLimitsDiff.y);
    else if(CollisionType == Collisions::Down)
        move(Axis::Vertical * SuperiorLimitsDiff.y);
    else if(CollisionType == Collisions::Left)
        move(Axis::Horizontal * -InferiorLimitsDiff.x);
    else if(CollisionType == Collisions::Right)
        move(Axis::Horizontal * SuperiorLimitsDiff.x);
}

sf::Vector2f Camera::getCameraDirection()
{
    sf::Vector2f CameraPosition = getCenter();
    sf::Vector2f Direction = Axis::None;

    if(PlayerCentralPosition.y < CameraPosition.y && CameraPosition.y - CameraSize.y / 2.f > 0.f)
        Direction += Axis::Vertical;
    if(PlayerCentralPosition.y > CameraPosition.y && CameraPosition.y + CameraSize.y / 2.f < LevelLimits.y)
        Direction += Axis::Vertical;
    if(PlayerCentralPosition.x < CameraPosition.x && CameraPosition.x - CameraSize.x / 2.f > 0.f)
        Direction += Axis::Horizontal;
    if(PlayerCentralPosition.x > CameraPosition.x && CameraPosition.x + CameraSize.x / 2.f < LevelLimits.x)
        Direction += Axis::Horizontal;
    return Direction;
}

Camera::Collisions Camera::getCollisionType()
{
    sf::Vector2f CameraPosition = getCenter();
    if(CameraPosition.y - CameraSize.y / 2.f < 0.f)
        return Collisions::Up;
    else if(CameraPosition.y + CameraSize.y / 2.f > LevelLimits.y)
        return Collisions::Down;
    else if(CameraPosition.x - CameraSize.x / 2.f < 0.f)
        return Collisions::Left;
    else if(CameraPosition.x + CameraSize.x / 2.f > LevelLimits.x)
        return Collisions::Right;
    else
        return Collisions::Nope;
}

void Camera::setLevelLimits(const sf::Vector2f& Limits)
{
    LevelLimits = Limits;
}

sf::Vector2f Camera::getPlayerCenterPosition(const sf::FloatRect& EntityRect)
{
    return sf::Vector2f(EntityRect.left, EntityRect.top) + sf::Vector2f(EntityRect.width, EntityRect.height) / 2.f;
}