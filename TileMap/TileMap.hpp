#pragma once

#include <memory>

#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

//
enum class Rotation : short
{
    Negative = -1,
    QuadrantI,
    QuadrantII,
    QuadrantIII,
    QuadrantIV
};

struct TileInfo
{
    //
    sf::Vector2f TexturePos;
    //
    Rotation TileRotation;
    ///
    ///
    ///
    TileInfo(const sf::Vector2f& TextureP, const Rotation& TileR)
        : TexturePos(TextureP), TileRotation(TileR)
    {}

    TileInfo()
        : TexturePos({-1.f, -1.f}), TileRotation(Rotation::QuadrantI)
    {}
};

class TileMap : public sf::Drawable, public sf::Transformable
{
private:
    //
    sf::Vector2f TileSize;
    //
    sf::Vector2u MapSize;
    //
    sf::VertexArray Vertices;
    //
    std::shared_ptr< sf::Texture > TileMapTexture;
    ///
    ///
    ///
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    ///
    ///
    ///
    bool RotateTile(sf::Vertex* Tile, Rotation TileRotation);
    ///
    ///
    ///
    bool loadTexture(const std::string& FileName);
public:
    ///
    ///
    ///
    void setTileSize(const sf::Vector2f& Size);
    ///
    ///
    ///
    void setMapSize(const sf::Vector2u& Size);
    ///
    ///
    ///
    bool loadTileMap(const std::string& TileSet , const std::vector< TileInfo >& Tiles);
};