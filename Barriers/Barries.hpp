#include "../Entity/Entity.hpp"

namespace TSLogic
{
    class Barriers
    {
    private:
        // Defined important variables for Barriers
        using BarrierCore = std::pair< SmartRect, SmartRect::CollisionTypes >;
        // Used for defining barriers
        std::vector< BarrierCore > BarrierRects;
    public:
        // Defined important information for barriers
        using BarrierInfo = std::pair< sf::FloatRect, SmartRect::CollisionTypes >;
        ///
        /// @brief Loads Barriers form the bounds vector
        ///
        /// @param BarrierBounds - This where all
        /// important information like: where it
        /// is, how big it is are stored and what
        /// type of collision needs to be performed
        ///
        /// @see SmartRect/SmartRect.hpp::TSLogic::SmartRect::CollisionTypes
        ///
        void loadBarriers(const std::vector< BarrierInfo >& BarrierBounds);
        ///
        /// @brief Checks collision between entity and each Rect
        ///
        /// @param Person - The entity that is going to be checked
        ///
        void CheckCollision(Entity& Person);
        ///
        /// @brief It clears everything inside it
        ///
        void clear();
    };
}