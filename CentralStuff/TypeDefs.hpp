#pragma once

// Used for defining the uint type,
// typically define for Linux already
// (Cross compilling reasons)
typedef unsigned int uint;
// Used for defining the ulong type,
// typically define for Linux already
// (Cross compilling reasons)
typedef unsigned long ulong;
// Standard size of a texture,
// bc it needs to run on all hardware
constexpr uint TextureMinSize = 512u;
// The most reasonable speed value
constexpr float MovingSpeed = 300.f;
// Used for collisions
constexpr float PseudoLineMultiplier = 2.f;
// Camera scaling reference
#define DefaultSize sf::Vector2f(480.f, 270.f)