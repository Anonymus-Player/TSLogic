#include <SFML/Graphics/Image.hpp>
#include <iostream>

#include "Animation.hpp"
#include "../CentralStuff/CoreFunctions.hpp"
#include "../ResourceManager/ResourceManager.hpp"

void TSLogic::Animation::Animate(sf::RectangleShape& EntityRect, const Actions& Action)
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
        // Loads a new frame
        sf::IntRect(CurrentFrame * static_cast<int>(FrameSize.x), 
        static_cast<int>(CurrentAction) * static_cast<int>(FrameSize.y), 
        static_cast<int>(FrameSize.x), static_cast<int>(FrameSize.y)));
    }
    else
    {
        // Changes the current frames
        EntityRect.setTextureRect(sf::IntRect(CurrentFrame * static_cast<int>(FrameSize.x), 
        static_cast<int>(CurrentAction) * static_cast<int>(FrameSize.y), 
        static_cast<int>(FrameSize.x), static_cast<int>(FrameSize.y)));
    }
    
    CurrentFrame++;
}

void TSLogic::Animation::setFrameLimit(const std::string& TextureFilename, const int& HorizontalFrameSize)
{
    sf::Image Image;
    Image.loadFromFile(TextureFilename);

    sf::Vector2u TextureSize = Image.getSize();
    FrameLimit = static_cast<int>(TextureSize.x) / HorizontalFrameSize;

    if(CompareToMin(TextureSize.x) || CompareToMin(TextureSize.y))
    {
        constexpr auto Warning = "Warning: Recommended size is exced."
            "\nNote that texture won't be compatible with all GPUs\n";
        std::cerr << Warning;
    }
    else if(CompareToMax(TextureSize.x) || CompareToMax(TextureSize.y))
    {
        NeedsToLoad = true;
        Filename = TextureFilename;
    }
}