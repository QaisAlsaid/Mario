#ifndef PHISICS_HPP
#define PHISICS_HPP
#include "comman/Vec2.hpp"
#include "Entity.hpp"
#include <memory>
#include <cmath>

class Phisics
{
public:
    static Vec2 getOverLap(std::shared_ptr<Entity> first, std::shared_ptr<Entity> second);
    static Vec2 getPrevOverLap(std::shared_ptr<Entity> first, std::shared_ptr<Entity> second);
    static bool isOverLap(std::shared_ptr<Entity> first, std::shared_ptr<Entity> second);
    static void normalResolution(std::shared_ptr<Entity> moving, std::shared_ptr<Entity> stati_c);
};

#endif // PHISICS_HPP
