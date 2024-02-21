#ifndef PHYSICS_HPP
#define PHYSICS_HPP
#include "comman/Vec2.hpp"
#include "Entity.hpp"
#include <memory>
#include <cmath>

class Physics
{
public:
    static Vec2 getOverLap(std::shared_ptr<Entity> first, std::shared_ptr<Entity> second);
    static Vec2 getPrevOverLap(std::shared_ptr<Entity> first, std::shared_ptr<Entity> second);
    static bool isOverLap(std::shared_ptr<Entity> first, std::shared_ptr<Entity> second);
    static inline bool pointInAABB(const Vec2& point, const Vec2& aabb_size, const Vec2& aabb_center)
    {
        return(point.x - 32 < aabb_center.x + aabb_size.x/2 && point.x + 32> aabb_center.x - aabb_size.x/2
            && point.y - 32 < aabb_center.y + aabb_size.y/2 && point.y + 32 > aabb_center.y - aabb_size.y/2);
    }
    static void normalResolution(std::shared_ptr<Entity> moving, std::shared_ptr<Entity> stati_c, float delta);
    static float movetowards(float current, float wanted, float delta)
    {
        if(wanted - current > delta) return current + delta;
        if(wanted - current < -delta) return current - delta;
        return wanted;
    }
};

#endif // PHYSICS_HPP
