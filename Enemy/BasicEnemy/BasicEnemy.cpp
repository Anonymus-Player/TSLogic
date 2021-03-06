#include "BasicEnemy.hpp"
#include "../../CentralStuff/Random.hpp"
#include "../../CentralStuff/TypeDefs.hpp"

constexpr float MaxDistance = 128.f;
constexpr float MaxActions = 3.f;

TSLogic::BasicEnemy::BasicEnemy(const sf::Vector2f& Position, const sf::Vector2f& Size, const std::string& TextureFilename)
    : Enemy(Position, Size, TextureFilename)
{}

void TSLogic::BasicEnemy::Update(float DeltaTime)
{
    auto [EnemyDirection, EnemyAction] = getAction();
    moveEntity(DeltaTime, EnemyDirection);
    WalkingDistance -= DeltaTime * MovingSpeed;
    EntityAnimate(EnemyAction);
}

std::pair< sf::Vector2f, TSLogic::Actions > TSLogic::BasicEnemy::getAction()
{
    if(WalkingDistance > 0.f)
    {
        if(Action == Actions::MoveUp)
        {    
            return {SmartRect::Directions::Up, Actions::MoveUp};
        }
        else if(Action == Actions::MoveDown)
        {    
            return {SmartRect::Directions::Down, Actions::MoveDown};
        }
        else if(Action == Actions::MoveLeft)
        {    
            return {SmartRect::Directions::Left, Actions::MoveLeft};
        }
        else if(Action == Actions::MoveRight)
        {    
            return {SmartRect::Directions::Right, Actions::MoveRight};
        }
        
        return {SmartRect::Directions::Stop, Actions::None};
    }
    else
    {
        Action = static_cast< Actions >(RandomGenerator<int>::getRandom(MaxActions));
        WalkingDistance = MaxDistance;
        return {SmartRect::Directions::Stop, Actions::None};
    }
}