#include <iostream>

#include "TileMap.hpp"
#include "../ResourceManager/ResourceManager.hpp"
#include "../CentralStuff/CoreFunctions.hpp"

#define NoTexturePos sf::Vector2f(-1, -1)

void TSLogic::TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = TileMapTexture.get();

    target.draw(Vertices, states);
}

bool TSLogic::TileMap::RotateTile(sf::Vertex* Tile, Rotation TileRotation)
{
    if(TileRotation == Rotation::Negative)
        return false;

    constexpr float Pi = 3.14f;
    sf::Vector2f TileCenter = Tile[0].position + TileSize / 2.f;

    for(int Index = 0; Index < 4; Index++)
    {
        Tile[Index].position = RotateAround(Tile[Index].position, 
        TileCenter, static_cast< float >(TileRotation) * Pi / 2.f);
    }

    return true;
}

void TSLogic::TileMap::setTileSize(const sf::Vector2f& Size)
{
    TileSize = Size;
}

void TSLogic::TileMap::setMapSize(const sf::Vector2u& Size)
{
    LayerSize = Size;
}

sf::Vector2f TSLogic::TileMap::getWorldSize()
{
    return TileSize * static_cast< sf::Vector2f >(LayerSize);
}

bool TSLogic::TileMap::loadTexture(const std::string& Filename)
{
    try
    {
        TileMapTexture = ResourceManager::Acquire(Filename);
    }
    catch(const std::exception& Exception)
    {
        std::cerr << Exception.what() << '\n';
        return false;
    }
    
    return true;
}

bool TSLogic::TileMap::loadTileMap(const std::string& TileSet, const std::vector< TileInfo >& Tiles)
{
    if(!loadTexture(TileSet))
    {
        std::cerr << "Failed To load Texture\n";
        return false;
    }

    if(TileSize == sf::Vector2f() || LayerSize == sf::Vector2u())
    {
        std::cerr << "Something is not Right with Size\n";
        return false;
    }

    Vertices.setPrimitiveType(sf::Quads);

    for(unsigned i = 0; i < LayerSize.x; i++)
        for(unsigned j = 0; j < LayerSize.y; j++)
        {
            TileInfo Tile = Tiles[i + j * LayerSize.x];

            if(Tile.TexturePos == NoTexturePos)
                continue;

            sf::Vertex Quad[4];
            sf::Vector2f QuadPosition = sf::Vector2f(static_cast< float >(i) * TileSize.x, 
                                                    static_cast< float >(j) * TileSize.y);
            
            Quad[0].position = QuadPosition;
            Quad[1].position = sf::Vector2f(QuadPosition.x + TileSize.x, QuadPosition.y);
            Quad[2].position = QuadPosition + TileSize;
            Quad[3].position = sf::Vector2f(QuadPosition.x, QuadPosition.y + TileSize.y);

            Quad[0].texCoords = Tile.TexturePos;
            Quad[1].texCoords = sf::Vector2f(Tile.TexturePos.x + TileSize.x, Tile.TexturePos.y);
            Quad[2].texCoords = Tile.TexturePos + TileSize;
            Quad[3].texCoords = sf::Vector2f(Tile.TexturePos.x, Tile.TexturePos.y + TileSize.y);

            if(!RotateTile(Quad, Tile.TileRotation))
            {
                std::cerr << "Rotation went wrong\nTileRotation: " 
                << static_cast< int >(Tile.TileRotation) << '\n';
                Vertices.clear();
                return false;
            }
            
            for(uint Index = 0; Index < 4; Index++)
                Vertices.append(Quad[Index]);
        }

    return true;
}