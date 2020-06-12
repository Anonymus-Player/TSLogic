#include "IntelligentEnemy.hpp"
#include "../../CentralStuff/TypeDefs.hpp"

IntelligentEnemy::IntelligentEnemy(const sf::Vector2f& Position, const sf::Vector2f& Size, const std::string& TextureFilename)
    : Enemy(Position, Size, TextureFilename)
{}

void IntelligentEnemy::Update(float DeltaTime)
{
    EnemySpeed = DeltaTime * MovingSpeed / 2.f;
    auto [EnemyDirection, EnemyAction] = getAction();
    moveEntity(DeltaTime, EnemyDirection, 0.9f);
    EntityAnimate(EnemyAction);
}

std::pair< sf::Vector2f, Actions > IntelligentEnemy::getAction()
{
    if(isColliding())
        return EvitObstacle();
    else
    {
        sf::Vector2f Position = getPosition();
        
        if(Position.x < PlayerPos.x - EnemySpeed)
            return {SmartRect::Directions::Right, Actions::MoveRight};
        else if(Position.x > PlayerPos.x + EnemySpeed)
            return {SmartRect::Directions::Left, Actions::MoveLeft};
        else if(Position.y < PlayerPos.y - EnemySpeed)
            return {SmartRect::Directions::Down, Actions::MoveDown};
        else if(Position.y > PlayerPos.y + EnemySpeed)
            return {SmartRect::Directions::Up, Actions::MoveUp};
        else
            return {SmartRect::Directions::Stop, Actions::None};
    }
}

std::pair< sf::Vector2f, Actions > IntelligentEnemy::EvitObstacle()
{
    sf::Vector2f Position = getPosition();
    sf::Vector2f Size = getSize();

    if(DirectionOnCollision == SmartRect::Directions::Stop)
        DirectionOnCollision = getFacingDirection();

    if(DirectionOnCollision == SmartRect::Directions::Up || DirectionOnCollision == SmartRect::Directions::Down)
    {
        float LeftDiff = Position.x + Size.x - Obstcale.left;
        float RightDiff = Obstcale.left + Obstcale.width - Position.x;

        if(LeftDiff < 0.f || RightDiff < 0.f)
        {
            if(DirectionOnCollision == SmartRect::Directions::Up)
            {
                float UpDiff = Position.y + Size.y - Obstcale.top;

                if(UpDiff >= 0.f)
                    return {SmartRect::Directions::Up, Actions::MoveUp};
                else
                {
                    DirectionOnCollision = SmartRect::Directions::Stop;
                    Obstcale = sf::FloatRect();
                    return {SmartRect::Directions::Stop, Actions::None};
                }
            }
            else if(DirectionOnCollision == SmartRect::Directions::Down)
            {
                float DownDiff = Obstcale.top + Obstcale.height - Position.y;

                if(DownDiff >= 0.f)
                    return {SmartRect::Directions::Down, Actions::MoveDown};
                else
                {
                    DirectionOnCollision = SmartRect::Directions::Stop;
                    Obstcale = sf::FloatRect();
                    return {SmartRect::Directions::Stop, Actions::None};
                }
            }
            else
            {
                DirectionOnCollision = SmartRect::Directions::Stop;
                Obstcale = sf::FloatRect();
                return {SmartRect::Directions::Stop, Actions::None};
            }
        }
        else
        {
            if(LeftDiff < RightDiff)
                return {SmartRect::Directions::Left, Actions::MoveLeft};
            else
                return {SmartRect::Directions::Right, Actions::MoveRight}; 
        }
    }
    else if(DirectionOnCollision == SmartRect::Directions::Left || DirectionOnCollision == SmartRect::Directions::Right)
    {
        float UpDiff = Position.y + Size.y - Obstcale.top;
        float DownDiff = Obstcale.top + Obstcale.height - Position.y;

        if(UpDiff < 0.f || DownDiff < 0.f)
        {
            if(DirectionOnCollision == SmartRect::Directions::Left)
            {
                float LeftDiff = Position.x + Size.x - Obstcale.left;

                if(LeftDiff >= 0.f)
                    return {SmartRect::Directions::Left, Actions::MoveLeft};
                else
                {
                    DirectionOnCollision = SmartRect::Directions::Stop;
                    Obstcale = sf::FloatRect();
                    return {SmartRect::Directions::Stop, Actions::None};
                }
            }
            else if(DirectionOnCollision == SmartRect::Directions::Right)
            {
                float RightDiff = Obstcale.left + Obstcale.width - Position.x;
                
                if(RightDiff >= 0.f)
                    return {SmartRect::Directions::Right, Actions::MoveRight};
                else
                {
                    DirectionOnCollision = SmartRect::Directions::Stop;
                    Obstcale = sf::FloatRect();
                    return {SmartRect::Directions::Stop, Actions::None};
                }
            }
            else
            {
                DirectionOnCollision = SmartRect::Directions::Stop;
                Obstcale = sf::FloatRect();
                return {SmartRect::Directions::Stop, Actions::None};
            }
        }
        else
        {
            if(UpDiff < DownDiff)
                return {SmartRect::Directions::Up, Actions::MoveUp};
            else
                return {SmartRect::Directions::Down, Actions::MoveDown};
        }
    }
    else
    {
        DirectionOnCollision = SmartRect::Directions::Stop;
        Obstcale = sf::FloatRect();
        return {SmartRect::Directions::Stop, Actions::None};
    }
}

bool IntelligentEnemy::isColliding()
{
    return Obstcale != sf::FloatRect();
}

void IntelligentEnemy::setObstcaleInfo(const sf::FloatRect& ObstcaleRect)
{
    Obstcale = ObstcaleRect;
}

void IntelligentEnemy::setDestinationPos(const sf::Vector2f& Destination)
{
    PlayerPos = Destination;
}