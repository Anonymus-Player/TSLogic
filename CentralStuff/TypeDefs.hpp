#pragma once

// Used for defining the uint type, typically define for Linux already (Cross compilling reasons)
typedef unsigned int uint;
// Used for defining the ulong type, typically define for Linux already (Cross compilling reasons)
typedef unsigned long ulong;
// Standard size of a texture, bc it needs to run on all hw
#define TextureMinSize 512u
// Self-explanatory
#define MovingSpeed 300.f
// Standard size of a tile
#define TileSize sf::Vector2f(32.f, 32.f)
// Camera scalling reference
#define DefaultSize sf::Vector2f(480.f, 270.f)
// Used for collisions
#define PseudoLineMultiplier 2.f