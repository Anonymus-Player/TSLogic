#include "Level.hpp"

TSLogic::Level::Level(const std::string& LevelFilename)
{
    LoadLevel(LevelFilename);
}

void TSLogic::Level::LoadLevel(const std::string& LevelFilename)
{
    LevelParser::openFile(LevelFilename);
    LevelParser::loadBackground(Background);
    LevelParser::loadEnemies(Enemies);
    LevelParser::loadGates(Gates);
    LevelParser::loadBarriers(Borders);
    Protagonist = std::make_unique< Player >(LevelParser::loadPlayer());
    WorldSize = Background.at(0).getWorldSize();
    Protagonist->setCameraLimits(WorldSize);
    Protagonist->setCameraSize(static_cast< sf::Vector2f >(AppWindow.getSize()));
}

void TSLogic::Level::HandleEvents(const sf::Event::EventType& Event)
{
    switch (Event)
    {
        case sf::Event::Closed:
        {
            TSLogic::AppWindow.close();
            break;
        }
        case sf::Event::LostFocus:
        {
            TSLogic::SleepWindow();
            break;
        }
        case sf::Event::Resized:
        {
            Protagonist->setCameraSize({static_cast< float >(TSLogic::AppEvent.size.width),
                                        static_cast< float >(TSLogic::AppEvent.size.height)});
            break;
        }
        default:
            break;
    }
}

void TSLogic::Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for(auto& Layer : Background)
    {    
        target.draw(Layer, states);
    }
    for(auto& Enemy : Enemies)
    {    
        if(TSLogic::getPerspective().intersects(Enemy->getGlobalBounds()))
            TSLogic::AppWindow.draw(*Enemy, states);
    }

    TSLogic::AppWindow.draw(*Protagonist, states);
}

void TSLogic::Level::UpdateLevel()
{
    DeltaTime = AppClock.restart().asSeconds();
    Protagonist->Update(DeltaTime);
    IntelligentEnemy::setDestinationPos(Protagonist->getPosition());
    CheckCollisions();
    Protagonist->UpdateCamera();
    TSLogic::AppWindow.setView(Protagonist->getPlayerCamera());
    GatesCheck();
}

void TSLogic::Level::CheckCollisions()
{
    for(auto& Enemy : Enemies)
    {     
        if(TSLogic::getPerspective().intersects(Enemy->getGlobalBounds()))
        {
            Enemy->Update(DeltaTime);

            if(Enemy->CheckCollision(*Protagonist, SmartRect::CollisionTypes::Outwards))
            {
                Protagonist->AttackEnemy(*Enemy);
            }
            Borders.CheckCollision(*Enemy);
            Enemy->CheckCollision(sf::FloatRect({0, 0}, WorldSize));

            if(Protagonist->CheckCollision(*Enemy, SmartRect::CollisionTypes::Outwards))
            {
                Protagonist->AttackEnemy(*Enemy);
            }
            Borders.CheckCollision(*Protagonist);
            Protagonist->CheckCollision(sf::FloatRect({0, 0}, WorldSize));
        }
    }
    
    Borders.CheckCollision(*Protagonist);
    Protagonist->CheckCollision(sf::FloatRect({0, 0}, WorldSize));

    RemoveDeadEnemies();
}

void TSLogic::Level::RemoveDeadEnemies()
{
    for(auto Enemy = Enemies.begin(); Enemy != Enemies.end();)
    {
        if((*Enemy)->IsDead())
        {
            Enemy = Enemies.erase(Enemy);
        }
        else
        {
            Enemy++;
        }
    }
}

bool TSLogic::Level::IsPlayerDead() const
{
    return Protagonist->IsDead();
}

void TSLogic::Level::GatesCheck()
{
    for(auto& Gate : Gates)
    {
        // CConfirm = Collision Confirmation
        auto [CConfirm, LevelFile] = Gate.Collides
        (
            Protagonist->getGlobalBounds(), 
            Protagonist->getFacingDirection()
        );

        if(CConfirm == true)
        {
            Background.clear();
            Enemies.clear();
            Borders.clear();
            Gates.clear();
            Protagonist.~unique_ptr();

            LoadLevel(LevelFile);
            return;
        }
    }
}