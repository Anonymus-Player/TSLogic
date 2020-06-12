#pragma once

#include <string>
#include <cmath>

#include <SFML/Graphics/Rect.hpp>

///
/// @brief Transforms a sf::IntRect into a std::string. Ex: RectToString(sf::IntRect()) -> "(0, 0, 0, 0)"
///
/// @param Rect - A SFML rectangle to be transformed
///
/// @return A string according with "(Rect.left, Rect.top, Rect.width, Rect.height)"
///
template< typename T >
std::string RectToString(const sf::Rect< T >& Rect)
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
template< typename T >
sf::Vector2< T > operator*(const sf::Vector2< T >& Right, const sf::Vector2< T >& Left)
{
    return sf::Vector2< T >(Right.x * Left.x, Right.y * Left.y);
}
///
///
///
template< typename T >
sf::Vector2< T > RotateAround(sf::Vector2< T > Point, sf::Vector2< T > Origin, float RadAngle) 
{
    sf::Vector2< T > PointAtZero = Point - Origin;
    return Origin + sf::Vector2< T >(PointAtZero.x * std::cos(RadAngle) - PointAtZero.y * std::sin(RadAngle), 
                                    PointAtZero.x * std::sin(RadAngle) + PointAtZero.y * std::cos(RadAngle));
}
///
/// @brief Strippts the extension of the file
///
/// @param FileName - This simple to understand, you want more explanation put it yourself
///
/// @return A string, nothing more harder to understand
///
std::string getName(const std::string& FileName);