#include <The-Spell-EngineLogic/Enginelogic.hpp>

int main()
{
    AppWindow.create(sf::VideoMode(1280, 768), "app", sf::Style::Default);
    AppWindow.setVerticalSyncEnabled(true);

    std::vector< TileMap > Background;
    std::vector< std::unique_ptr< Enemy > > Enemies;

    if(!LevelParser::openFile("Levels/Test.json"))
        return EXIT_FAILURE;

    if(!LevelParser::loadBackground(Background))
        return EXIT_FAILURE;

    if(!LevelParser::loadEnemies(Enemies))
        return EXIT_FAILURE;

    Player Player = LevelParser::loadPlayer();

    Player.setCameraSize(sf::Vector2f(AppWindow.getSize()));
    Player.setLevelLimits({1280, 768});

    while(AppWindow.isOpen())
    {
        while(AppWindow.pollEvent(AppEvent))
        {
            if(AppEvent.type == sf::Event::Closed)
                AppWindow.close();
            else if(AppEvent.type == sf::Event::LostFocus)
                SleepWindow();
            else if(AppEvent.type == sf::Event::Resized)
            {
                Player.setCameraSize({static_cast< float >(AppEvent.size.width),
                static_cast< float >(AppEvent.size.height)});
            }
        }
        AppWindow.clear();
        DeltaTime = AppClock.restart().asSeconds();
        Player.Update(DeltaTime);
        IntelligentEnemy::setDestinationPos(Player.getPosition());

        for(std::unique_ptr< Enemy >& E : Enemies)
        {
            E->Update(DeltaTime);
                        
            Player.CheckCollision(*E, SmartRect::CollisionTypes::Outwards);
            Player.CheckCollision(sf::FloatRect({0, 0}, {1280, 768}));
            
            E->CheckCollision(Player, SmartRect::CollisionTypes::Outwards);
            E->CheckCollision(sf::FloatRect({0, 0}, {1280, 768}));
        }
        
        Player.CheckCollision(sf::FloatRect({0, 0}, {1280, 768}));

        Player.UpdateCamera();
        AppWindow.setView(Player.getPlayerCamera());

        for(TileMap& Layer : Background)
            AppWindow.draw(Layer);

        for(std::unique_ptr< Enemy >& E : Enemies)
            if(getPerspective().intersects(E->getGlobalBounds()))
                AppWindow.draw(*E);

        AppWindow.draw(Player);
        AppWindow.display();
    }
    return EXIT_SUCCESS;
}
