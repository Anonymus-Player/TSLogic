#pragma once

#include <string>
#include <cmath>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "TypeDefs.hpp"

namespace TSLogic
{
    ///
    /// @brief Transforms a sf::IntRect into a std::string. 
    /// Ex: RectToString(sf::IntRect()) -> "(0, 0, 0, 0)"
    ///
    /// @param Rect - A SFML rectangle to be transformed
    ///
    /// @return A string according with:
    /// "(Rect.left, Rect.top, Rect.width, Rect.height)"
    ///
    template< typename Number >
    static std::string RectToString(const sf::Rect< Number >& Rect)
    {
        return "(" + std::to_string(Rect.left) + ", " + std::to_string(Rect.top) + ", " 
        + std::to_string(Rect.width) + ", " + std::to_string(Rect.height) + ")";
    }

    ///
    /// @brief Multiplies two sf::Vector2's
    ///
    /// @param Right - Right operand (a sf::Vector2) 
    ///
    /// @param Left - Left operand (a sf::Vector2)
    ///
    /// @return A multliplied sf::Vector2
    ///
    template< typename Number >
    static sf::Vector2< Number > operator*(const sf::Vector2< Number >& Right, const sf::Vector2< Number >& Left)
    {
        return sf::Vector2< Number >(Right.x * Left.x, Right.y * Left.y);
    }
    
    ///
    /// @brief It roates a point using a center
    /// position by using a relative coordonate
    /// which is the difference between the Point
    /// and the Origin using the angle (in radians)
    ///
    /// @param Point - The point coordonates
    /// that needs to be rotated (a vector)
    ///
    /// @param Origin - The center point relative to Point
    ///
    /// @param RadAngle - The angle that the
    /// Point needs to be rotated (in radinas)
    ///
    /// @return A new roated point
    ///
    template< typename Number >
    static sf::Vector2< Number > RotateAround(sf::Vector2< Number > Point, sf::Vector2< Number > Origin, float RadAngle) 
    {
        sf::Vector2< Number > PointAtZero = Point - Origin;
        return Origin + sf::Vector2< Number >(PointAtZero.x * std::cos(RadAngle) - PointAtZero.y * std::sin(RadAngle), 
                                            PointAtZero.x * std::sin(RadAngle) + PointAtZero.y * std::cos(RadAngle));
    }

    ///
    /// @brief Strippts the extension of the file
    ///
    /// @param FileName - This simple to understand, you want more explanation put it yourself
    ///
    /// @return A string, nothing more harder to understand
    ///
    static std::string getName(const std::string& FileName)
    {
        const std::size_t FileNamePos = FileName.find_last_of('.');
        constexpr std::size_t StringStart = 0;
        return FileName.substr(StringStart, FileNamePos);
    }

    ///
    /// @brief Comapres a value to the indicated
    /// minimum size of a sf::Texture, which is 512
    ///
    /// @param Value - The value that is comparated
    ///
    /// @return The evaluation of that comparison
    ///
    template < typename ValType >
    static bool CompareToMin(ValType Value)
    {
        return static_cast< unsigned >(Value) > TextureMinSize;
    }
        
    ///
    /// @brief Comapres a value to the indicated
    /// maximum size of a sf::Texure, which is
    /// returned by sf::Texture::getMaximumSize()
    ///
    /// @param Value - The value that is comparated
    ///
    /// @return The evaluation of that comparison
    ///
    template < typename ValType >
    static bool CompareToMax(ValType Value)
    {
        return static_cast< unsigned >(Value) > sf::Texture::getMaximumSize();
    }
}