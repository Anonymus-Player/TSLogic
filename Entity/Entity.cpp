#include <iostream>
#include <SFML/Graphics/RenderTarget.hpp>

#include "Entity.hpp"

TSLogic::Entity::Entity(const sf::Vector2f& Position, const sf::Vector2f& Size)
{
    EntityRect.setPosition(Position);
    EntityRect.setSize(Size);
    EntityAnimation.AnimTexture = nullptr;
}

void TSLogic::Entity::initEntityAnim(const std::string& TextureFilename)
{
    EntityAnimation.AnimTexture = ResourceManager::Acquire(TextureFilename); 
    EntityRect.setTexture(EntityAnimation.AnimTexture.get());
    
    EntityAnimation.setFrameLimit(
        TextureFilename, static_cast< int >(EntityRect.getSize().x));
}

void TSLogic::Entity::draw(
    sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(EntityRect, states);
}

bool TSLogic::Entity::CheckCollision(
    Entity& Other, const SmartRect::CollisionTypes& CollisionType)
{
    return EntityRect.CheckCollision(Other.EntityRect, CollisionType);
}

bool TSLogic::Entity::CheckCollision(
    SmartRect& Other, const SmartRect::CollisionTypes& CollisionType)
{
    return EntityRect.CheckCollision(Other, CollisionType);
}

bool TSLogic::Entity::CheckCollision(const sf::FloatRect& Area)
{
    return EntityRect.CheckCollision(Area);
}

sf::Vector2f TSLogic::Entity::getPosition() const
{
    return EntityRect.getPosition();
}

sf::Vector2f TSLogic::Entity::getSize() const
{
    return EntityRect.getSize();
}

sf::Vector2f TSLogic::Entity::getFacingDirection() const
{
    return EntityRect.FacingDirection;
}

sf::FloatRect TSLogic::Entity::getGlobalBounds() const
{
    return EntityRect.getGlobalBounds();
}

int TSLogic::Entity::getHealth() const
{
    return EntityHealth;
}

int TSLogic::Entity::getDamage() const
{
    return EntityDamage;
}

void TSLogic::Entity::DealDamage(const int& Damage)
{
    EntityHealth -= Damage; 
}

void TSLogic::Entity::moveEntity(const float& DeltaTime, 
    const sf::Vector2f& Direction, const float& SpeedFactor)
{
    EntityRect.moveRect(DeltaTime, Direction, SpeedFactor);
}

void TSLogic::Entity::EntityAnimate(const Actions& Action)
{
    EntityAnimation.Animate(EntityRect, Action);
}