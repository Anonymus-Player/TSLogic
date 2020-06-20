#include "../../TSLogic/TSLogic.hpp"

int main()
{
    TSLogic::AppWindow.create(sf::VideoMode(1280, 768), "app", sf::Style::Default);
    TSLogic::AppWindow.setVerticalSyncEnabled(true);

    std::vector< TSLogic::TileMap > Background;
    std::vector< std::unique_ptr< TSLogic::Enemy > > Enemies;

    if(!TSLogic::LevelParser::openFile("Levels/Test.json"))
        return EXIT_FAILURE;

    if(!TSLogic::LevelParser::loadBackground(Background))
        return EXIT_FAILURE;

    if(!TSLogic::LevelParser::loadEnemies(Enemies))
        return EXIT_FAILURE;

    TSLogic::Player Player = TSLogic::LevelParser::loadPlayer();

    Player.setCameraSize(sf::Vector2f(TSLogic::AppWindow.getSize()));
    Player.setLevelLimits({1280, 768});

    while(TSLogic::AppWindow.isOpen())
    {
        while(TSLogic::AppWindow.pollEvent(TSLogic::AppEvent))
        {
            if(TSLogic::AppEvent.type == sf::Event::Closed)
                TSLogic::AppWindow.close();
            else if(TSLogic::AppEvent.type == sf::Event::LostFocus)
                TSLogic::SleepWindow();
            else if(TSLogic::AppEvent.type == sf::Event::Resized)
            {
                Player.setCameraSize({static_cast< float >(TSLogic::AppEvent.size.width),
                static_cast< float >(TSLogic::AppEvent.size.height)});
            }
        }
        TSLogic::AppWindow.clear();
        TSLogic::DeltaTime = TSLogic::AppClock.restart().asSeconds();
        Player.Update(TSLogic::DeltaTime);
        TSLogic::IntelligentEnemy::setDestinationPos(Player.getPosition());

        for(std::unique_ptr< TSLogic::Enemy >& E : Enemies)
        {
            E->Update(TSLogic::DeltaTime);
                        
            Player.CheckCollision(*E, TSLogic::SmartRect::CollisionTypes::Outwards);
            Player.CheckCollision(sf::FloatRect({0, 0}, {1280, 768}));
            
            E->CheckCollision(Player, TSLogic::SmartRect::CollisionTypes::Outwards);
            E->CheckCollision(sf::FloatRect({0, 0}, {1280, 768}));
        }
        
        Player.CheckCollision(sf::FloatRect({0, 0}, {1280, 768}));

        Player.UpdateCamera();
        TSLogic::AppWindow.setView(Player.getPlayerCamera());

        for(TSLogic::TileMap& Layer : Background)
            TSLogic::AppWindow.draw(Layer);

        for(std::unique_ptr< TSLogic::Enemy >& E : Enemies)
            if(TSLogic::getPerspective().intersects(E->getGlobalBounds()))
                TSLogic::AppWindow.draw(*E);

        TSLogic::AppWindow.draw(Player);
        TSLogic::AppWindow.display();
    }
    return EXIT_SUCCESS;
}
