#include "ResourceManager.hpp"
#include "../CentralStuff/CoreFunctions.hpp"
#include "../CentralStuff/TypeDefs.hpp"

#include <iostream>

#define TooBigToBeSupported "The image is bigger than the minimal size for all GPUs. \n\
Consider disabling the mod that you loaded.\n"

#define TooBigCompToStdSize "Warning: \n\
The image is bigger than the minimal size for all GPUs. \n\
Please use TileSets with the maximum resolution of 512x512, \n\
but if it is an animation, use the Area argument, \n\
but to be max 512x512. \n\
To ensure maximum compatibility.\n"

std::shared_ptr< sf::Texture > ResourceManager::Acquire(const std::string& TextureFileName, const sf::IntRect& TextureArea)
{
    std::string TextureKey;
    if(TextureArea != sf::IntRect())
        TextureKey = getName(TextureFileName) + " " + RectToString(TextureArea);
    else
        TextureKey = getName(TextureFileName);
        
    TextureMapIter = TextureMap.find(TextureKey);

    if(TextureMapIter != TextureMap.end())
        return TextureMapIter->second;
    else
    {
        CheckSize(TextureFileName, TextureArea);
        std::shared_ptr< sf::Texture > PtrTexture = std::make_shared< sf::Texture >();
        if(!PtrTexture->loadFromFile(TextureFileName, TextureArea))
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

void ResourceManager::CheckSize(const std::string& FileName, const sf::IntRect& Area)
{
    sf::Image Im;
    Im.loadFromFile(FileName);
    if(Area == sf::IntRect())
    {
        if(Im.getSize().x > sf::Texture::getMaximumSize() || Im.getSize().y > sf::Texture::getMaximumSize())
            std::runtime_error(FileName + ": " + TooBigToBeSupported);
        else if((Im.getSize().x > TextureMinSize || Im.getSize().y > TextureMinSize))
            std::cerr << FileName + ": " + TooBigCompToStdSize;
    }
    else
    {
        if(static_cast< uint >(Area.width) > sf::Texture::getMaximumSize() || static_cast< uint >(Area.height) > sf::Texture::getMaximumSize())
            std::runtime_error(FileName + ": " + TooBigToBeSupported);
        else if(static_cast< uint >(Area.width) > TextureMinSize || static_cast< uint >(Area.height) > TextureMinSize)
            std::cerr << FileName + ": " + TooBigCompToStdSize;
    }
}

void ResourceManager::RemoveOrphans()
{
    for(TextureMapIter = TextureMap.begin(); TextureMapIter != TextureMap.end();)
    {
        if(TextureMapIter->second.use_count() == 1)
            TextureMapIter = TextureMap.erase(TextureMapIter);
        else
            TextureMapIter++;
    }
}

void ResourceManager::Clear()
{
    TextureMap.clear();
}