#include "../../TSLogic/TSLogic.hpp"

int main()
{
    TSLogic::AppWindow.create(sf::VideoMode(1280, 768), "app", sf::Style::Default);
    TSLogic::AppWindow.setVerticalSyncEnabled(true);

    TSLogic::Level Map("Levels/Test.json"); 

    while(TSLogic::AppWindow.isOpen())
    {
        while(TSLogic::AppWindow.pollEvent(TSLogic::AppEvent))
        {
            Map.HandleEvents(TSLogic::AppEvent.type);
        }
        
        TSLogic::AppWindow.clear();
        Map.UpdateLevel();
        TSLogic::AppWindow.draw(Map);
        TSLogic::AppWindow.display();
    }
    return EXIT_SUCCESS;
}
