#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <memory>

// Different actions used for animating purposes, but they can have other usages
enum class Actions
{
    None = -1,
    MoveUp,
    MoveDown,
    MoveLeft,
    MoveRight,
    JumpLeft,
    JumpRight,
    Attack,
    Pair,
};

class Animation
{
private:
    // How many frames animation has
    int FrameLimit = 0;
    // Represents on what frame animation is at the moment
    int CurrentFrame = 0;
    // Represents what action is animating right now
    Actions CurrentAction = Actions::MoveDown;
    // This is used to indicate thst it needs  
    bool NeedsToLoad = false;
    // This is used for loading purposes
    std::string Filename;
public:
    // This is wehere texture lives
    std::shared_ptr< sf::Texture > AnimTexture;
    ///
    /// @brief Here is where the loading happens and frame limit will be set and
    /// this is where the function will decide if it needs to switch textures or not, 
    /// that is achived by verifying if the size of the whole texture is exceeding the recomended size 
    ///
    /// @param TextureFilename - Path of the image to be loaded
    ///
    /// @param HorizontalFrameSize - The size of the object/entity on the Y axis
    ///
    void setFrameLimit(const std::string& TextureFilename, const int& HorizontalFrameSize);
    ///
    /// @brief Animates an object/entity depending on the action
    ///
    /// @param EnityRect - Used to modify just some parametres radrading: tectxture rect or loading a texture
    ///
    /// @param Action - Action to animate
    ///
    void Animate(sf::RectangleShape& EntityRect, const Actions& Action);
};
