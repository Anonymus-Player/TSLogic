#pragma once

#include <fstream>
#include <json/json.h>

#include "../Enemy/IntelligentEnemy/IntelligentEnemy.hpp"
#include "../Enemy/BasicEnemy/BasicEnemy.hpp"
#include "../Barriers/Barries.hpp"
#include "../TileMap/TileMap.hpp"
#include "../Player/Player.hpp"
#include "../Gate/Gate.hpp"

namespace TSLogic
{
    class LevelParser
    {
    private:
        // File handler for JSON parser
        static inline std::ifstream Reader;
        // The parset itself - the
        static inline Json::Value Root;
    public:
        ///
        /// @brief Opens a file and checks if it exists and if it can be read correctly
        ///
        /// @param Filename - The file that you want to read.
        ///
        /// @note It uses a JSON parser and that the file needs 
        /// to have a specific stucture: see Examples/Level.json
        ///
        /// @return A confirmation that everything was OK
        ///
        static bool openFile(const std::string& Filename);
        ///
        /// @brief Loads information about Player from the file opened using openFile()
        ///
        /// @note Player information has this structure:
        ///
        /// "Player" : -> Field name
        /// {
        ///     "Position" : [600, 600], -> Its position stored as a array of 2 floats
        ///     "Size" : [24, 32], -> Its size, which has the same storage specifier as above
        ///     "Filename" : "Resources/Player.png" -> Its texture filename stored as a string
        /// }
        ///
        /// @return The Player stored in the currently opened file
        ///
        static Player loadPlayer();
        ///
        /// @brief Loads enemies from the same file used in loadPlayer method
        ///
        /// @note Enemies information has this structure:
        ///
        /// "Enemies" : -> Its field name
        /// [
        ///     [
        ///         0, -> Its type: 0 -> Basic, 1 -> Intelligent
        ///         400, -> Its vertical position
        ///         400, -> Its horizontal position
        ///         24, -> Its vertical size
        ///         32, -> Its horizontal size
        ///         "Resources/BasicEnemy.png" -> Its texture filename
        ///     ], 
        ///     ... -> Next Item
        /// ]
        ///
        /// @param Enemies - A vector that can hold
        /// every derived type of TSLogic::Enemy
        ///
        /// @return A confirmation that everything was OK, 
        /// if not, everything that was inside will be cleared
        ///
        static bool loadEnemies(std::vector< std::unique_ptr< Enemy > >& Enemies);
        ///
        /// @brief Loads map from the same file used in loadPlayer method
        ///
        /// @note Map information has this structure:
        ///
        /// "Background" : -> Its field name
        /// {
        ///     "TileSize" : [32, 32], -> How big a tile is
        ///     "Size" : [40, 24], -> How many of them are in one layer
        ///     "Layers" : -> Where other important information are stored
        ///     [
        ///         {
        ///             "Filename" : "Tilesets/PathAndObjects.png", -> Its Tileset filename
        ///             "Info" : -> The Map info array
        ///             [
        ///                 [
        ///                     96, -> Its texture vertical position
        ///                     320, -> Its texture horizontal position
        ///                     0 -> Its rotation, @see TileMap/TileMap.hpp::TSLogic::Rotation 
        ///                 ], 
        ///                 ... -> Next item
        ///             ]
        ///         },
        ///         ... -> Next item
        ///     ]
        /// }
        ///
        /// @note The position of the tile is known 
        /// based on where it is on the map info array
        ///
        /// @note The tile crops from the tileset like this:
        /// Crop Position -> From the map info array, and
        /// Crop Size -> From the "Size" field
        ///
        /// @param Background - Where the map info will be loaded
        ///
        /// @return A confirmation that everything was OK, 
        /// if not, everything that was inside will be cleared
        ///
        static bool loadBackground(std::vector< TileMap >& Background);
        ///
        /// @brief Loads the gates to the next map
        /// from the same file used in loadPlayer method
        ///
        /// @note Gates information has this structure:
        /// 
        /// "Gates" : -> Its field name
        /// [
        ///     {
        ///         "Area" : [1024, 0, 96, 4], -> Where it is and how big it is
        ///         "Direction" : [0, -1], -> In what direction the protagonist should come
        ///         "Filename" : "Levels/Level2.json" -> The path to a new JSON file
        ///     },
        ///     ... -> Next Item
        /// ]
        ///
        /// @note For the "Direction" field:
        /// 
        /// @see SmartRect/SmartRect.hpp::TSLogic::SmartRect::Directions
        ///
        /// @param Gates - A vector that it holds every gate
        ///
        /// @return A confirmation that everything was OK, 
        /// if not, everything that was inside will be cleared
        ///
        static bool loadGates(std::vector< Gate >& Gates);
        ///
        /// @brief Loads the barrires to the next map
        /// from the same file used in loadPlayer method
        ///
        /// @note Barriers information has this structure:
        ///
        /// "Barriers" : -> Its field name
        /// [
        ///     [0, 344, 448, 8], -> Where it is and how big it is
        ///     ... -> Next item
        /// ]
        ///
        /// @param Borders - A vector that it holds every barrier
        ///
        /// @return A confirmation that everything was OK, 
        /// if not, everything that was inside will be cleared
        ///
        static bool loadBarriers(Barriers& Borders);
    };
}