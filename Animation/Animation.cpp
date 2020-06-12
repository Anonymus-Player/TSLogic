#include <SFML/Graphics/Image.hpp>
#include <iostream>

#include "Animation.hpp"
#include "../CentralStuff/TypeDefs.hpp"
#include "../ResourceManager/ResourceManager.hpp"

void Animation::Animate(sf::RectangleShape& EntityRect, const Actions& Action)
{
    sf::Vector2f FrameSize = EntityRect.getSize();
    
    if(Action == Actions::None || CurrentFrame == FrameLimit)
        CurrentFrame = 0;

    if(Action != Actions::None && Action != CurrentAction)
    {
        CurrentFrame = 0;
        CurrentAction = Action;
    }
    
    if(NeedsToLoad == true)
    {
        ResourceManager::RemoveOrphans();
        AnimTexture = ResourceManager::Acquire(Filename, 
        sf::IntRect(CurrentFrame * static_cast<int>(FrameSize.x), 
        static_cast<int>(CurrentAction) * static_cast<int>(FrameSize.y), 
        static_cast<int>(FrameSize.x), static_cast<int>(FrameSize.y)));
    }
    else
    {
        EntityRect.setTextureRect(sf::IntRect(CurrentFrame * static_cast<int>(FrameSize.x), 
        static_cast<int>(CurrentAction) * static_cast<int>(FrameSize.y), 
        static_cast<int>(FrameSize.x), static_cast<int>(FrameSize.y)));
    }
    
    CurrentFrame++;
}

void Animation::setFrameLimit(const std::string& TextureFilename, const int& HorizontalFrameSize)
{
    sf::Image Im;
    
    Im.loadFromFile(TextureFilename);
    sf::Vector2u TextureSize = Im.getSize();
    
    FrameLimit = static_cast<int>(TextureSize.x) / HorizontalFrameSize;
    if(TextureSize.x > TextureMinSize || TextureSize.y > TextureMinSize)
        std::cout << "Warning: Recommended size is exced.\nNote that texture won't be compatible with all GPUs\n";
    if(TextureSize.x > sf::Texture::getMaximumSize() || TextureSize.y > sf::Texture::getMaximumSize())
    {
        NeedsToLoad = true;
        Filename = TextureFilename;
    }
}