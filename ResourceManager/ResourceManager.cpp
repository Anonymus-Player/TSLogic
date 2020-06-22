#include "ResourceManager.hpp"
#include "../CentralStuff/CoreFunctions.hpp"
#include "../CentralStuff/TypeDefs.hpp"

#include <iostream>

std::shared_ptr< sf::Texture > TSLogic::ResourceManager::Acquire(const std::string& TextureFilename, const sf::IntRect& TextureArea)
{
    std::string TextureKey;
    if(TextureArea != sf::IntRect())
        TextureKey = getName(TextureFilename) + " " + RectToString(TextureArea);
    else
        TextureKey = getName(TextureFilename);
        
    TextureMapIter = TextureMap.find(TextureKey);

    if(TextureMapIter != TextureMap.end())
        return TextureMapIter->second;
    else
    {
        CheckSize(TextureFilename, TextureArea);
        std::shared_ptr< sf::Texture > PtrTexture = std::make_shared< sf::Texture >();
        if(!PtrTexture->loadFromFile(TextureFilename, TextureArea))
        {
            throw std::runtime_error("File not found");
            return nullptr;
        }
        else
        {
            TextureMap.insert({TextureKey, PtrTexture});
            return PtrTexture;
        }
    }
}

void TSLogic::ResourceManager::CheckSize(const std::string& Filename, const sf::IntRect& Area)
{
    sf::Image Image;
    Image.loadFromFile(Filename);
    sf::Vector2u ImageSize = Image.getSize();

    constexpr auto TooBigToBeSupported = "The image "
    "is bigger than the minimal size for all GPUs.\n"
    "Consider disabling the mod that you loaded.\n";
    
    constexpr auto TooBigCompToStdSize = "Warning:\n"
    "The image is bigger than the minimal size for all GPUs.\n"
    "Please use TileSets with the maximum resolution of 512x512,\n"
    "but if it is an animation, use the Area argument,\n"
    "but to be max 512x512.\n"
    "To ensure maximum compatibility.\n";

    if(Area == sf::IntRect())
    {
        if(CompareToMax(ImageSize.x) || CompareToMax(ImageSize.y))
        {
            throw std::runtime_error(Filename + ": " + TooBigToBeSupported);
        }
        else if(CompareToMin(ImageSize.x) || CompareToMin(ImageSize.y))
        {
            std::cerr << Filename + ": " + TooBigCompToStdSize;
        }
    }
    else
    {
        if(CompareToMax(Area.width) || CompareToMax(Area.height))
        {
            throw std::runtime_error(Filename + ": " + TooBigToBeSupported);
        }
        else if(CompareToMin(Area.width) || CompareToMin(Area.height))
        {
            std::cerr << Filename + ": " + TooBigCompToStdSize;
        }
    }
}

void TSLogic::ResourceManager::RemoveOrphans()
{
    for(TextureMapIter = TextureMap.begin(); TextureMapIter != TextureMap.end();)
    {
        if(TextureMapIter->second.use_count() == 1)
        {
            TextureMapIter = TextureMap.erase(TextureMapIter);
        }
        else
        {
            TextureMapIter++;
        }
    }
}

void TSLogic::ResourceManager::Clear()
{
    TextureMap.clear();
}