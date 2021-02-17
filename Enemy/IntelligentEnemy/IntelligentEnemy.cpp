#include "IntelligentEnemy.hpp"
#include "../../CentralStuff/TypeDefs.hpp"
#include "../../CentralStuff/Random.hpp"

TSLogic::IntelligentEnemy::IntelligentEnemy(const sf::Vector2f& Position, const sf::Vector2f& Size, const std::string& TextureFilename)
    : Enemy(Position, Size, TextureFilename)
{
    EntityHealth = 50;
    EntityDamage = 5;
}

void TSLogic::IntelligentEnemy::Update(float DeltaTime)
{
    EnemySpeed = DeltaTime * MovingSpeed / 2.f;
    auto [EnemyDirection, EnemyAction] = getAction();
    moveEntity(DeltaTime, EnemyDirection, 0.9f);
    EntityAnimate(EnemyAction);
}

bool TSLogic::IntelligentEnemy::ReadyToAttack()
{
    if(AttackClock.getElapsedTime().asSeconds() >= RandomGenerator< float >::getRandom())
    {
        AttackClock.restart();
        return true;
    }

    return false;
}

std::pair< sf::Vector2f, TSLogic::Actions > TSLogic::IntelligentEnemy::getAction()
{
    if(isColliding())
    {    
        return AvoidObstacle();
    }
    else
    {
        sf::Vector2f Position = getPosition();
        
        if(Position.x < PlayerPos.x - EnemySpeed)
        {    
            return {SmartRect::Directions::Right, Actions::MoveRight};
        }
        else if(Position.x > PlayerPos.x + EnemySpeed)
        {    
            return {SmartRect::Directions::Left, Actions::MoveLeft};
        }
        else if(Position.y < PlayerPos.y - EnemySpeed)
        {    
            return {SmartRect::Directions::Down, Actions::MoveDown};
        }
        else if(Position.y > PlayerPos.y + EnemySpeed)
        {    
            return {SmartRect::Directions::Up, Actions::MoveUp};
        }
        
        return {SmartRect::Directions::Stop, Actions::None};
    }
}

std::pair< sf::Vector2f, TSLogic::Actions > TSLogic::IntelligentEnemy::AvoidObstacle()
{
    sf::Vector2f Position = getPosition();
    sf::Vector2f Size = getSize();

    if(DirectionOnCollision == SmartRect::Directions::Stop)
        DirectionOnCollision = getFacingDirection();

    if(DirectionOnCollision == SmartRect::Directions::Up || DirectionOnCollision == SmartRect::Directions::Down)
    {
        float LeftDiff = Position.x + Size.x - Obstacle.left;
        float RightDiff = Obstacle.left + Obstacle.width - Position.x;

        if(LeftDiff < 0.f || RightDiff < 0.f)
        {
            if(DirectionOnCollision == SmartRect::Directions::Up)
            {
                float UpDiff = Position.y + Size.y - Obstacle.top;

                if(UpDiff >= 0.f)
                {    
                    return {SmartRect::Directions::Up, Actions::MoveUp};
                }
                else
                {
                    DirectionOnCollision = SmartRect::Directions::Stop;
                    Obstacle = sf::FloatRect();
                    return {SmartRect::Directions::Stop, Actions::None};
                }
            }
            else if(DirectionOnCollision == SmartRect::Directions::Down)
            {
                float DownDiff = Obstacle.top + Obstacle.height - Position.y;

                if(DownDiff >= 0.f)
                {    
                    return {SmartRect::Directions::Down, Actions::MoveDown};
                }
                else
                {
                    DirectionOnCollision = SmartRect::Directions::Stop;
                    Obstacle = sf::FloatRect();
                    return {SmartRect::Directions::Stop, Actions::None};
                }
            }
            else
            {
                DirectionOnCollision = SmartRect::Directions::Stop;
                Obstacle = sf::FloatRect();
                return {SmartRect::Directions::Stop, Actions::None};
            }
        }
        else
        {
            if(LeftDiff < RightDiff)
            {    
                return {SmartRect::Directions::Left, Actions::MoveLeft};
            }
            else
            {    
                return {SmartRect::Directions::Right, Actions::MoveRight};
            } 
        }
    }
    else if(DirectionOnCollision == SmartRect::Directions::Left || DirectionOnCollision == SmartRect::Directions::Right)
    {
        float UpDiff = Position.y + Size.y - Obstacle.top;
        float DownDiff = Obstacle.top + Obstacle.height - Position.y;

        if(UpDiff < 0.f || DownDiff < 0.f)
        {
            if(DirectionOnCollision == SmartRect::Directions::Left)
            {
                float LeftDiff = Position.x + Size.x - Obstacle.left;

                if(LeftDiff >= 0.f)
                {    
                    return {SmartRect::Directions::Left, Actions::MoveLeft};
                }
                else
                {
                    DirectionOnCollision = SmartRect::Directions::Stop;
                    Obstacle = sf::FloatRect();
                    return {SmartRect::Directions::Stop, Actions::None};
                }
            }
            else if(DirectionOnCollision == SmartRect::Directions::Right)
            {
                float RightDiff = Obstacle.left + Obstacle.width - Position.x;
                
                if(RightDiff >= 0.f)
                {    
                    return {SmartRect::Directions::Right, Actions::MoveRight};
                }
                else
                {
                    DirectionOnCollision = SmartRect::Directions::Stop;
                    Obstacle = sf::FloatRect();
                    return {SmartRect::Directions::Stop, Actions::None};
                }
            }
            else
            {
                DirectionOnCollision = SmartRect::Directions::Stop;
                Obstacle = sf::FloatRect();
                return {SmartRect::Directions::Stop, Actions::None};
            }
        }
        else
        {
            if(UpDiff < DownDiff)
            {    
                return {SmartRect::Directions::Up, Actions::MoveUp};
            }
            else
            {    
                return {SmartRect::Directions::Down, Actions::MoveDown};
            }
        }
    }
    else
    {
        DirectionOnCollision = SmartRect::Directions::Stop;
        Obstacle = sf::FloatRect();
        return {SmartRect::Directions::Stop, Actions::None};
    }
}

bool TSLogic::IntelligentEnemy::isColliding()
{
    return Obstacle != sf::FloatRect();
}

void TSLogic::IntelligentEnemy::setObstacleInfo(const sf::FloatRect& ObstacleRect)
{
    Obstacle = ObstacleRect;
}

void TSLogic::IntelligentEnemy::setDestinationPos(const sf::Vector2f& Destination)
{
    PlayerPos = Destination;
}