#pragma once

#include <SFML/Graphics/Texture.hpp>

#include <unordered_map>
#include <memory>

// Used for sharing resoources, thus using less memory
class ResourceManager
{
public:
    ///
    /// @brief Used for loading a Texture and stores it in Textures map if the Texture is bigger that what gpu supports (used for background)
    ///
    /// @return A smart pointer to the Texture object it is already there
    ///
    /// @param TextureFileName - The path to the texture and its name but its without extension
    ///
    /// @param TextureArea - The size and the position of the Texture
    ///
    static std::shared_ptr< sf::Texture > Acquire(const std::string& TextureFileName, const sf::IntRect& TextureArea = sf::IntRect());
    ///
    /// @brief If an Texture isn't used anywere it will be deleted
    ///
    static void RemoveOrphans();
    ///
    /// @brief Destroyes the Texture map because it is a static object and the default destructor isn't applied anymore 
    ///
    static void Clear();
private:
    ///
    /// @brief Checks if Texture size is exceeding the recomended size, if it does, it will
    /// print a warning and if it exceeds the maximum size supported by the gpu it will
    /// throw an exeption
    ///
    /// @param FileName - Path to the texture to be verified
    ///
    /// @param Area - How much of the texture will be loaded/seen, this parameter will
    /// be used in size verification process
    ///
    static void CheckSize(const std::string& FileName, const sf::IntRect& Area = sf::IntRect());
    // Where all Textures (smart pointers) will be stored 
    static inline std::unordered_map< std::string, std::shared_ptr< sf::Texture > > TextureMap;
    // The iterator for it (Declared here because it's faster)
    static inline std::unordered_map< std::string, std::shared_ptr< sf::Texture > >::iterator TextureMapIter;
};