#pragma once

#include <fstream>
#include <json/json.h>

#include "../TileMap/TileMap.hpp"
#include "../Enemy/BasicEnemy/BasicEnemy.hpp"
#include "../Enemy/IntelligentEnemy/IntelligentEnemy.hpp"
#include "../Player/Player.hpp"

class LevelParser
{
private:
    //
    static inline std::ifstream Reader;
    //
    static inline Json::Value Root;
public:
    ///
    ///
    ///
    static bool openFile(const std::string& FileName);
    ///
    ///
    ///
    static Player loadPlayer();
    ///
    ///
    ///
    static bool loadEnemies(std::vector< std::unique_ptr< Enemy > >& Enemies);
    ///
    ///
    ///
    static bool loadBackground(std::vector< TileMap >& Background);
};
