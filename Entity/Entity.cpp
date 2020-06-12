#include <iostream>
#include <SFML/Graphics/RenderTarget.hpp>

#include "Entity.hpp"

Entity::Entity(const sf::Vector2f& Position, const sf::Vector2f& Size)
{
    EntityRect.setPosition(Position);
    EntityRect.setSize(Size);
    EntityAnimation.AnimTexture = nullptr;
}

void Entity::initEntityAnim(const std::string& TextureFilename)
{
    EntityAnimation.AnimTexture = ResourceManager::Acquire(TextureFilename); 
    EntityRect.setTexture(EntityAnimation.AnimTexture.get());
    
    EntityAnimation.setFrameLimit(TextureFilename, static_cast< int >(EntityRect.getSize().x));
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(EntityRect, states);
}

bool Entity::CheckCollision(Entity& Other, const SmartRect::CollisionTypes& CollisionType)
{
    return EntityRect.CheckCollision(Other.EntityRect, CollisionType);
}

bool Entity::CheckCollision(const sf::FloatRect& Area)
{
    return EntityRect.CheckCollision(Area);
}

sf::Vector2f Entity::getPosition()
{
    return EntityRect.getPosition();
}

sf::Vector2f Entity::getSize()
{
    return EntityRect.getSize();
}

sf::Vector2f Entity::getFacingDirection()
{
    return EntityRect.FacingDirection;
}

sf::FloatRect Entity::getGlobalBounds()
{
    return EntityRect.getGlobalBounds();
}

void Entity::moveEntity(const float& DeltaTime, const sf::Vector2f& Direction, const float& SpeedFactor)
{
    EntityRect.moveRect(DeltaTime, Direction, SpeedFactor);
}

void Entity::EntityAnimate(const Actions& Action)
{
    EntityAnimation.Animate(EntityRect, Action);
}