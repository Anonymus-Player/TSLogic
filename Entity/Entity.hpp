#pragma once

#include <memory>

#include "../Animation/Animation.hpp"
#include "../ResourceManager/ResourceManager.hpp"
#include "../SmartRect/SmartRect.hpp"

namespace TSLogic
{
    struct EnityInfo
    {
        // Where it is
        sf::Vector2f Position;
        // How big it is
        sf::Vector2f Size;
        // The path of its texure
        std::string TextureFilename;
    };

    // Core class for NPC's, Player and Enemies 
    class Entity : public sf::Drawable
    {
    protected:
        // Internal Variable used for defining
        // how nuch health an entity has
        int EntityHealth;
        // Internal Variable used for defining
        // how nuch damage an entity can deal
        int EntityDamage;
        ///
        /// @brief Move the entity with a determined speed to a specific direction
        ///
        /// @param DeltaTime - The time between each frame
        ///
        /// @param Direction - Where it needs to go
        ///
        /// @see SmartRect/SmartRect.hpp::TSLogic::Directions
        /// -> Those are all possible directions 
        ///
        void moveEntity(const float& DeltaTime, 
            const sf::Vector2f& Direction, const float& SpeedFactor = 1.f);
        ///
        /// @brief Function used as a wrapper around Animation::Animate method
        ///
        /// @param Action - Predefined action or direction 
        ///
        void EntityAnimate(const Actions& Action);
        ///
        /// @brief Here is where animations will be ititialize
        /// by calling Animation::setFrameLimit()
        ///
        /// @param TextureFilename - Path of the image to be loaded
        ///
        void initEntityAnim(const std::string& TextureFilename);
    private:
        // Variable used for animating an entity movement or action
        Animation EntityAnimation;
        // Internal variable for moving, drawing and collinding entity.
        // Well the Entity itself is there, but not the logic
        SmartRect EntityRect;
        ///
        /// @brief Draw the object to a render target
        ///
        /// @note This is a pure virtual function that is implemented
        /// in this class and defines how the object is drawn
        ///
        /// @param target - Render target to draw to
        ///
        /// @param states - Current render states
        ///
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    public:
        ///
        /// @brief Initialize the Entity
        ///
        /// @param Position - Where you want the enemy will be initially localized 
        ///
        /// @param Size - How big you want the Enity to be in pixel size
        ///
        Entity(const sf::Vector2f& Position, const sf::Vector2f& Size);
        ///
        /// @brief Check if 2 entities are colliding with each other,
        /// if it collides it will react by moving this entity
        ///
        /// @note The collision is split between 2 section:
        /// Inwards and Outwards, depending on CollisonType parameter 
        ///
        /// @param Other - The other entity that checking the collision with
        ///
        /// @param CollisionType - What kind of check it has to perform
        ///
        /// @return A confirmation that it was colliding
        ///
        bool CheckCollision(Entity& Other, const SmartRect::CollisionTypes& CollisionType);
         ///
        /// @brief Check if an entitt and n object are colliding with each
        /// other, if it collides it will react by moving this entity
        ///
        /// @note The collision is split between 2 section:
        /// Inwards and Outwards, depending on CollisonType parameter 
        ///
        /// @param Other - The object that checking the collision with
        ///
        /// @param CollisionType - What kind of check it has to perform
        ///
        /// @return A confirmation that it was colliding
        ///
        bool CheckCollision(SmartRect& Other, const SmartRect::CollisionTypes& CollisionType);
        ///
        /// @brief Checks if an entity is colliding with an object,
        /// if it does it will make sure that the entity is inside
        /// that object, because this method was designed to be used
        /// for making sure that the entity is inside a area 
        ///
        /// @param Area - The bounding box of that object that you want
        /// the entity to be in, ex: A cage, the whole level, etc.
        ///
        /// @return A confirmation that it was trying to escape
        ///
        bool CheckCollision(const sf::FloatRect& Area);
        ///
        /// @brief It will subtract from the
        /// Health using the "Damage" parameter
        ///
        /// @param Damage - How much it will subtract
        ///
        void DealDamage(const int& Damage);
        ///
        /// @brief Gets the position of the entity
        ///
        /// @return Current position
        ///
        sf::Vector2f getPosition() const;
        ///
        /// @brief Gets the size of the entity
        ///
        /// @return Current size
        ///
        sf::Vector2f getSize() const;
        ///
        /// @brief Gets the direction that the entity is facing
        ///
        /// @return Current facing direction
        ///
        sf::Vector2f getFacingDirection() const;
        ///
        /// @brief Gets the bounding box of the entity
        ///
        /// @return Global bounding rectangle of the entity
        ///
        sf::FloatRect getGlobalBounds() const;
        ///
        /// @brief Gets how much health an entity has
        ///
        /// @return Current health value
        ///
        int getHealth() const;
        ///
        /// @brief Gets how much damage an entity can deal
        ///
        /// @return Current Damange value
        ///
        int getDamage() const;
        ///
        ///
        ///
        bool IsDead() const; 
    };
}