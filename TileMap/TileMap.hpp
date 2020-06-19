#pragma once

#include <memory>

#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace TSLogic
{
    // Tile rotation angles
    enum class Rotation : short
    {
        Negative = -1, // Invalid
        QuadrantI, // 90 -> 270
        QuadrantII, // 180 -> same
        QuadrantIII, // 270 -> 90
        QuadrantIV // 360 -> 0
    };
    
    struct TileInfo
    {
        // Where is its texture
        sf::Vector2f TexturePos;
        // What rotation it has
        Rotation TileRotation;
        ///
        /// @brief Initialize the Tile
        ///
        /// @param TextureP - Where its texture is
        ///
        /// @param TileR - What rotation it has
        ///
        TileInfo(const sf::Vector2f& TextureP, const Rotation& TileR)
            : TexturePos(TextureP), TileRotation(TileR)
        {}
        ///
        /// @brief Generates an empty Tile
        ///
        TileInfo()
            : TexturePos({-1.f, -1.f}), TileRotation(Rotation::QuadrantI)
        {}
    };
    
    class TileMap : public sf::Drawable, public sf::Transformable
    {
    private:
        // How big it a tile is
        sf::Vector2f TileSize;
        // How many of them are
        sf::Vector2u LayerSize;
        // This where tiles are stored
        sf::VertexArray Vertices;
        // The tileset texture
        std::shared_ptr< sf::Texture > TileMapTexture;
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
        ///
        /// @brief It rotates the tile using a specified angle
        ///
        /// @param Tile - An array of sf::Vertex
        ///
        /// @param TileRotation - What angle do you want to rotate the tile
        ///
        /// @return A confirmation that everything is ok
        ///
        bool RotateTile(sf::Vertex* Tile, Rotation TileRotation);
        ///
        /// @brief Loads the texture from the tileset path
        ///
        /// @param Filename - Where the tileset is located
        ///
        /// @return A confirmation that everything is ok
        ///
        bool loadTexture(const std::string& Filename);
    public:
        ///
        /// @brief Sets the size for all tiles
        ///
        /// @param Size - How big you want the tile to be
        ///
        void setTileSize(const sf::Vector2f& Size);
        ///
        /// @brief Sets the size for all layers
        ///
        /// @param Size - How big you want the layer to be
        ///
        /// @note The size of the bounding box of that 
        /// layer it will be LayerSize * TileSize
        ///
        void setMapSize(const sf::Vector2u& Size);
        ///
        /// @brief Loads the information from TileInfo
        /// vector used then to create a layer
        ///
        /// @param TileSet - The path where its texture is
        ///
        /// @param Tiles - The information used for layer creation
        ///
        /// @note The structure for TileInfo vector is described in
        /// LevelParser/LevelParser.hpp::TSLogic::LevelParser::loadBackground
        /// in the note section at "Info" field
        ///
        /// @return A confirmation that everything is ok
        ///
        bool loadTileMap(const std::string& TileSet, const std::vector< TileInfo >& Tiles);
    };
}