#include <random>

namespace TSLogic
{
    template< typename Number >
    class RandomGenerator
    {
    private:
        // Random generator engine (64-bit)
        static inline std::mt19937_64 randomEngine;
    public:
        ///
        /// @brief Generates a number between a Minimum
        /// and a Maximum, so, a range-based generation
        ///
        /// @param Min - The smallest number that you want to generate
        ///
        /// @param Max - The biggest number that you want to generate
        ///
        /// @return A random generated number
        ///
        static Number getRandom(Number Min, Number Max)
        {
            if constexpr(std::is_integral< Number >::value)
            {
                std::uniform_int_distribution< Number > randomDistribution(Min, Max);
                return randomDistribution(randomEngine);
            }
            else if constexpr(std::is_floating_point< Number >::value)
            {
                std::uniform_real_distribution< Number > randomDistribution(Min, Max);
                return randomDistribution(randomEngine);
            }
        }
        ///
        /// @brief Generates a number between 0 and Max,
        /// so, a range-based generation
        ///
        /// @note This implementation does not account negative numbers
        ///
        /// @param Max - The biggest number that you want to generate
        ///
        /// @return A random generated number
        ///
        static Number getRandom(Number Max)
        {
            if constexpr(std::is_integral< Number >::value)
            {
                std::uniform_int_distribution< Number > randomDistribution(0, Max);
                return randomDistribution(randomEngine);
            }
            else if constexpr(std::is_floating_point< Number >::value)
            {
                std::uniform_real_distribution< Number > randomDistribution(0, Max);
                return randomDistribution(randomEngine);
            }
        }
        ///
        /// @brief Generates a random number
        ///
        /// @return A random generated number
        ///
        static Number getRandom()
        {
            if constexpr(std::is_integral< Number >::value)
            {
                std::uniform_int_distribution< Number > randomDistribution;
                return randomDistribution(randomEngine);
            }
            else if constexpr(std::is_floating_point< Number >::value)
            {
                // Explicitly using 0 and 1, because not, it will trigger an UB
                std::uniform_real_distribution< Number > randomDistribution(0, 1);
                return randomDistribution.operator()(randomEngine);
            }
        }
    };
}