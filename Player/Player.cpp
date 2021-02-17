#include "Player.hpp"

TSLogic::Player::Player(const sf::Vector2f& Position, const sf::Vector2f& Size, const std::string& TextureFilename): 
    Entity(Position, Size)
{
    initEntityAnim(TextureFilename);
    EntityHealth = 100;
    EntityDamage = 10;
}

void TSLogic::Player::Update(float DeltaTime)
{
    auto [PlayerDirection, PlayerAction] = getAction();
    moveEntity(DeltaTime, PlayerDirection);
    EntityAnimate(PlayerAction);
}

std::pair< sf::Vector2f, TSLogic::Actions > TSLogic::Player::getAction()
{
    if(getInput::OnlyMovingUp())
    {    
        return {SmartRect::Directions::Up, Actions::MoveUp};
    }
    else if(getInput::OnlyMovingDown())
    {    
        return {SmartRect::Directions::Down, Actions::MoveDown};
    }
    else if(getInput::OnlyMovingLeft())
    {
        return {SmartRect::Directions::Left, Actions::MoveLeft};
    }
    else if(getInput::OnlyMovingRight())
    {
        return {SmartRect::Directions::Right, Actions::MoveRight};
    }
    else
        return {SmartRect::Directions::Stop, Actions::None};
}

void TSLogic::Player::AttackEnemy(Enemy& Other)
{
    sf::Time AttackTime = AttackClock.getElapsedTime();
    if(AttackTime.asSeconds() >= CoolDownTime && AttackTime.asSeconds() <= CoolDownTime * 1.5f)
    {
        if(getInput::OnlyAttacking())
        {
            if(Other.ReadyToAttack())
            {
                EntityHealth -= Other.getDamage();
                Other.DealDamage(EntityDamage);
            }
        }
        else if(getInput::OnlyDefending()) {}

        AttackClock.restart();
        return;
    }
    else
    {
        if(Other.ReadyToAttack())
        {
            EntityHealth -= Other.getDamage();
        }
        if(AttackTime.asSeconds() > CoolDownTime * 1.5f)
        {
            AttackClock.restart();
        }
    }
}

void TSLogic::Player::setCameraSize(const sf::Vector2f& NewSize)
{
    PlayerCamera.setCameraSize(NewSize);
}

void TSLogic::Player::UpdateCamera()
{
    PlayerCamera.UpdateCamera(getGlobalBounds());
}

sf::View TSLogic::Player::getPlayerCamera()
{
    return PlayerCamera;
}

sf::Vector2f TSLogic::Player::getCameraSize()
{
    return PlayerCamera.getSize();
}

void TSLogic::Player::setCameraLimits(const sf::Vector2f& Limits)
{
    PlayerCamera.setCameraLimits(Limits);
}