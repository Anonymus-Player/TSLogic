#include "SmartRect.hpp"
#include "../CentralStuff/TypeDefs.hpp"

void TSLogic::SmartRect::moveRect(const float& DeltaTime, const sf::Vector2f& Direction, const float& SpeedFactor)
{
    move(DeltaTime * MovingSpeed * Direction * SpeedFactor);
    PseudoLineThickness = DeltaTime * MovingSpeed;
    
    if(Direction != Directions::Stop)
        FacingDirection = Direction;
}

sf::Vector2f TSLogic::SmartRect::getCollisionDirection(const SmartRect& OtherObject)
{
    sf::FloatRect OtherObjectBounds = OtherObject.getGlobalBounds();
    sf::FloatRect ObjectBounds = getGlobalBounds();
    
    //
    sf::FloatRect OtherObjectPseudoLine = sf::FloatRect();
    sf::FloatRect ObjectPseudoLine = sf::FloatRect();
    
    // Up
    {
        // Constructing the upper portion of "This Object"
        ObjectPseudoLine = sf::FloatRect(ObjectBounds.left, ObjectBounds.top - PseudoLineThickness, 
                                        ObjectBounds.width, PseudoLineThickness * PseudoLineMultiplier);
        // Constructing the lower portion of "Other Object"
        OtherObjectPseudoLine = sf::FloatRect(OtherObjectBounds.left, OtherObjectBounds.top + 
                                            OtherObjectBounds.height - PseudoLineThickness, 
                                            OtherObjectBounds.width, PseudoLineThickness * PseudoLineMultiplier);
        
        // Verification
        if(ObjectPseudoLine.intersects(OtherObjectPseudoLine))
            return Directions::Up;
    }
    // Down
    {
        // Constructing the lower portion of "This Object"
        ObjectPseudoLine = sf::FloatRect(ObjectBounds.left, ObjectBounds.top + ObjectBounds.height - 
                                        PseudoLineThickness, ObjectBounds.width, PseudoLineThickness * PseudoLineMultiplier);
        // Constructing the upper portion of "Other Object"
        OtherObjectPseudoLine = sf::FloatRect(OtherObjectBounds.left, OtherObjectBounds.top - 
                                            PseudoLineThickness, OtherObjectBounds.width, 
                                            PseudoLineThickness * PseudoLineMultiplier);
        
        // Verification
        if(ObjectPseudoLine.intersects(OtherObjectPseudoLine))
            return Directions::Down;
    }
    // Left
    {
        // Constructing the left portion of "This Object"
        ObjectPseudoLine = sf::FloatRect(ObjectBounds.left - PseudoLineThickness, ObjectBounds.top, 
                                        PseudoLineThickness * PseudoLineMultiplier, ObjectBounds.height);
        // Constructing the right portion of "Other Object"
        OtherObjectPseudoLine = sf::FloatRect(OtherObjectBounds.left + OtherObjectBounds.width - 
                                            PseudoLineThickness, OtherObjectBounds.top, PseudoLineThickness * 
                                            PseudoLineMultiplier, OtherObjectBounds.height);
        
        // Verification
        if(ObjectPseudoLine.intersects(OtherObjectPseudoLine))
            return Directions::Left;
    }
    // Right
    {
        // Constructing the right portion of "This Object"
        ObjectPseudoLine = sf::FloatRect(ObjectBounds.left + ObjectBounds.width - PseudoLineThickness, 
                                        ObjectBounds.top, PseudoLineThickness * PseudoLineMultiplier, ObjectBounds.height);
        // Constructing the left portion of "Other Object"
        OtherObjectPseudoLine = sf::FloatRect(OtherObjectBounds.left - PseudoLineThickness, OtherObjectBounds.top, 
                                            PseudoLineThickness * PseudoLineMultiplier, OtherObjectBounds.height);
        
        // Verification
        if(ObjectPseudoLine.intersects(OtherObjectPseudoLine))
            return Directions::Right;
    }
    // If not, return the opposite direction of "Other Object"
    return -OtherObject.FacingDirection;
}

bool TSLogic::SmartRect::CheckCollision(const sf::FloatRect& Border)
{
    sf::Vector2f Difference = getInwardsCollision(Border);
    move(Difference);
    
    return Difference != Axis::None;
}

bool TSLogic::SmartRect::CheckCollision(const SmartRect& OtherObject, const CollisionTypes& CollisionType)
{
    if(CollisionType == CollisionTypes::Inwards)
    {
        sf::Vector2f Difference = getInwardsCollision(OtherObject);
        move(Difference);
        
        return Difference != Axis::None;
    }
    else if(CollisionType == CollisionTypes::Outwards)
    {
        sf::Vector2f Difference = getOutwardsCollision(OtherObject);
        move(Difference);
        
        return Difference != Axis::None;
    }
    
    return false;
}

sf::Vector2f TSLogic::SmartRect::getInwardsCollision(const sf::FloatRect& Border)
{
    sf::FloatRect ObjectBounds = getGlobalBounds();

    if(ObjectBounds.top < Border.top)
    {   
        // If it tries to escape from the top portion return the
        // difference between the border top portion and this top portion
        return Axis::Vertical * (Border.top - ObjectBounds.top);
    }
    if(ObjectBounds.top + ObjectBounds.height > Border.top + Border.height)
    {   
        // If it tries to escape from the lower portion return the
        // difference between the border lower portion and this lower portion
        return Axis::Vertical * ((Border.top + Border.height) 
                              - (ObjectBounds.top + ObjectBounds.height));
    }
    if(ObjectBounds.left < Border.left)
    {   
        // If it tries to escape from the left portion return the
        // difference between the border left portion and this left portion
        return Axis::Horizontal * (Border.left - ObjectBounds.left);
    }
    if(ObjectBounds.left + ObjectBounds.width > Border.left + Border.width)
    {   
        // If it tries to escape from the right portion return the
        // difference between the border right portion and this right portion
        return Axis::Horizontal * ((Border.left + Border.width) 
                                - (ObjectBounds.left + ObjectBounds.width));
    }
    
    return Axis::None;
}

sf::Vector2f TSLogic::SmartRect::getOutwardsCollision(const SmartRect& OtherObject)
{
    sf::FloatRect ObjectBounds = getGlobalBounds();
    sf::FloatRect OtherObjectBounds = OtherObject.getGlobalBounds();
    
    // Check to see on which side I'm colliding with
    sf::Vector2f CollisionDirection = getCollisionDirection(OtherObject);

    if(ObjectBounds.intersects(OtherObjectBounds))
    {
        if(CollisionDirection == Directions::Up)
        {
            // If it tries to enter from the upper portion return
            // the difference difference between the "Other Object"
            // bottom portion and "This Object" upper portion  
            return Axis::Vertical * (OtherObjectBounds.height + 
                    (OtherObjectBounds.top - ObjectBounds.top));
        }
        if(CollisionDirection == Directions::Down)
        {
            // If it tries to enter from the bottom portion return
            // the difference difference between the "Other Object"
            // upper portion and "This Objec"t bottom portion      
            return Axis::Vertical * (OtherObjectBounds.top - 
                    (ObjectBounds.top + ObjectBounds.height));
        }
        if(CollisionDirection == Directions::Left)
        { 
            // If it tries to enter from the left portion return
            // the difference difference between the "Other Object"
            // right portion and "This Object" left portion  
            return Axis::Horizontal * (OtherObjectBounds.width + 
                    (OtherObjectBounds.left - ObjectBounds.left));
        }
        if(CollisionDirection == Directions::Right)
        {  
            // If it tries to enter from the right portion return
            // the difference difference between the "Other Object"
            // left portion and "This Object" right portion  
            return Axis::Horizontal * (OtherObjectBounds.left - 
                    (ObjectBounds.left + ObjectBounds.width));
        }   
    }

    return Axis::None;
}

sf::Vector2f TSLogic::SmartRect::getInwardsCollision(const SmartRect& OtherObject)
{
    sf::FloatRect ObjectBounds = getGlobalBounds();
    sf::FloatRect OtherObjectBounds = OtherObject.getGlobalBounds();
    sf::Vector2f PositionDifference = Axis::None;

    if(ObjectBounds.top < OtherObjectBounds.top)
    {
        // If it tries to escape from the top portion
        // return the difference between the "Other Object"
        // top portion and "This Object top portion 
        PositionDifference += (Axis::Vertical * 
        (OtherObjectBounds.top - ObjectBounds.top));
    }
    if(ObjectBounds.top + ObjectBounds.height > OtherObjectBounds.top + OtherObjectBounds.height)
    {
        // If it tries to escape from the bottom portion
        // return the difference between the "Other Object"
        // bottom portion and "This Object bottom portion 
        PositionDifference += (Axis::Vertical * 
        ((OtherObjectBounds.top + OtherObjectBounds.height) - 
        (ObjectBounds.top + ObjectBounds.height)));
    }
    if(ObjectBounds.left < OtherObjectBounds.left)
    {
        // If it tries to escape from the left portion
        // return the difference between the "Other Object"
        // left portion and "This Object left portion 
        PositionDifference += (Axis::Horizontal * 
        (OtherObjectBounds.left - ObjectBounds.left));
    }
    if(ObjectBounds.left + ObjectBounds.width > OtherObjectBounds.left + OtherObjectBounds.width)
    {
        // If it tries to escape from the right portion
        // return the difference between the "Other Object"
        // rifgt portion and "This Object right portion 
        PositionDifference += (Axis::Horizontal * 
        ((OtherObjectBounds.left + OtherObjectBounds.width) - 
        (ObjectBounds.left + ObjectBounds.width)));
    }

    return PositionDifference;
}