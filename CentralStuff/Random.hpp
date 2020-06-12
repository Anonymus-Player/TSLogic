#include <random>
#include "TypeDefs.hpp"

template< typename T >
class RandomGenerator
{
private:
    // Random generator engine (64-bit)
    static inline std::mt19937_64 randomEngine;
public:
    ///
    /// @brief Generates a number between a Min and a Max, so, a range-based generation
    ///
    /// @param Min - I don't know what to put here (I'm open to sugestions in regards)
    ///
    /// @param Max - Same as Min
    ///
    /// @return A random generated number
    ///
    static T getRandom(T Min, T Max)
    {
        if constexpr(std::is_integral< T >::value)
        {
            std::uniform_int_distribution< T > randomDistribution(Min, Max);
            return randomDistribution(randomEngine);
        }
        else if constexpr(std::is_floating_point< T >::value)
        {
            std::uniform_real_distribution< T > randomDistribution(Min, Max);
            return randomDistribution(randomEngine);
        }
    }
    ///
    /// @brief Generates a number between 0 and Max, so, a range-based generation (I suggest to not put negative numbers)
    ///
    /// @param Max - I don't know what to put here (I'm open to sugestions in regards)
    ///
    /// @return A random generated number
    ///
    static T getRandom(T Max)
    {
        if constexpr(std::is_integral< T >::value)
        {
            std::uniform_int_distribution< T > randomDistribution(0, Max);
            return randomDistribution(randomEngine);
        }
        else if constexpr(std::is_floating_point< T >::value)
        {
            std::uniform_real_distribution< T > randomDistribution(0, Max);
            return randomDistribution(randomEngine);
        }
    }
    ///
    /// @brief Idk, generates a random number
    ///
    /// @return A random generated number
    ///
    static T getRandom()
    {
        if constexpr(std::is_integral< T >::value)
        {
            std::uniform_int_distribution< T > randomDistribution;
            return randomDistribution(randomEngine);
        }
        else if constexpr(std::is_floating_point< T >::value)
        {
            std::uniform_real_distribution< T > randomDistribution;
            return randomDistribution(randomEngine);
        }
    }
};