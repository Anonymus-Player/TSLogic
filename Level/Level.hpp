#pragma once

#include "../LevelParser/LevelParser.hpp"
#include "../CentralStuff/GlobalVariables.hpp"
#include "../CentralStuff/Random.hpp"

namespace TSLogic
{
    
    class Level : public sf::Drawable
    {
    private:
        // Used for getting to other levels
        std::vector< Gate > Gates;
        // Layers the defines the background
        std::vector< TileMap > Background;
        // Enemies that will interract with the Protagonist
        std::vector< std::unique_ptr< Enemy > > Enemies;
        // This is the character which you can control
        std::unique_ptr< Player > Protagonist;
        // The Size of the entire map
        sf::Vector2f WorldSize;
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
        /// @brief It creates a new level by calling LoadLevel
        ///
        /// @param LevelFilename - The path to
        /// the level that needs to be loaded
        ///
        Level(const std::string& LevelFilename = "Levels/Main.json");
        ///
        /// @brief It loads a new level from a JSON file
        ///
        /// @param LevelFilename - The path to the
        /// level that needs to be loaded
        ///
        /// @see LevelParser/LevelParser.hpp::LevelParser
        ///
        void LoadLevel(const std::string& LevelFilename);
        ///
        /// @brief It updates the level, eg:
        /// moving the player, moving the enemies,
        /// doing collision checking and reaction
        /// and gates checking
        ///
        void UpdateLevel();
        ///
        /// @brief It handles Window events
        ///
        /// @param Event - Event to be evaluated
        ///
        void HandleEvents(const sf::Event::EventType& Event);
    };
}