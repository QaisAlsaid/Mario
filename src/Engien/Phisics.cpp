#include "Phisics.hpp"


Vec2 Physics::getOverLap(std::shared_ptr<Entity> first, std::shared_ptr<Entity> second)
{
if(!(first->hasComponent<CBoundingBox>()) || !(second->hasComponent<CBoundingBox>()) ||
    !(second->hasComponent<CTransform>()) || !(second->hasComponent<CTransform>())) return Vec2(-1);
    const auto& f_p = first->getComponent<CTransform>().position;
    const auto& s_p = second->getComponent<CTransform>().position;
    const auto& f_c = first->getComponent<CBoundingBox>().half_size;
    const auto& s_c = second->getComponent<CBoundingBox>().half_size;
    const Vec2 delta = {abs(f_p.x - s_p.x), abs(f_p.y - s_p.y)};
    return Vec2(f_c + s_c - delta) * -1;

}


bool Physics::isOverLap(std::shared_ptr<Entity> first, std::shared_ptr<Entity> second)
{
    const auto& f_p = first->getComponent<CTransform>().position;
    const auto& s_p = second->getComponent<CTransform>().position;
    const auto& f_c = first->getComponent<CBoundingBox>().half_size;
    const auto& s_c = second->getComponent<CBoundingBox>().half_size;
    if(f_p.y + f_c.y >= s_p.y - s_c.y && f_p.y - f_c.y <= s_p.y + s_c.y
    && f_p.x + f_c.x >= s_p.x - s_c.x && f_p.x - f_c.x <= s_p.x + s_c.x)
        return true;
    return false;
}


Vec2 Physics::getPrevOverLap(std::shared_ptr<Entity> first, std::shared_ptr<Entity> second)
{
    if(!(first->hasComponent<CBoundingBox>()) || !(second->hasComponent<CBoundingBox>()) ||
    !(second->hasComponent<CTransform>()) || !(second->hasComponent<CTransform>())) return Vec2(-1);
    const auto& f_p = first->getComponent<CTransform>().prev_position;
    const auto& s_p = second->getComponent<CTransform>().prev_position;
    const auto& f_c = first->getComponent<CBoundingBox>().half_size;
    const auto& s_c = second->getComponent<CBoundingBox>().half_size;
    const Vec2 delta = {abs(f_p.x - s_p.x), abs(f_p.y - s_p.y)};
    return Vec2(f_c + s_c - delta) * -1;
}


void Physics::normalResolution(std::shared_ptr<Entity> moving, std::shared_ptr<Entity> stati_c, float delta)
{
    auto ol      = Physics::getOverLap(moving, stati_c);
    auto prev_ol = Physics::getPrevOverLap(moving, stati_c);
    const auto epsilon = 0;
    if(ol > 0)
    {
        if(prev_ol.y > 0)
        {
            if(moving->getComponent<CTransform>().position.x > stati_c->getComponent<CTransform>().position.x)
            {
                // => came from right
                moving->getComponent<CTransform>().position.x += ol.x;
                //moving->getComponent<CTransform>().velocity.x *= -1;
            }
            else if(moving->getComponent<CTransform>().position.x < stati_c->getComponent<CTransform>().position.x)
            {
                // => came from left
                moving->getComponent<CTransform>().position.x -= ol.x;
                //moving->getComponent<CTransform>().velocity.x *= -1;
            }
            return;
        }
        if(prev_ol.x >= 0)
        {
            if(moving->getComponent<CTransform>().position.y < stati_c->getComponent<CTransform>().position.y)
            {
                // => came from top
                moving->getComponent<CTransform>().position.y = stati_c->getComponent<CTransform>().position.y - stati_c->getComponent<CBoundingBox>().half_size.y- moving->getComponent<CBoundingBox>().half_size.y;
                //(ol.y + moving->getComponent<CTransform>().velocity.y*delta);
               // moving->getComponent<CTransform>().velocity.y *= -1;

            }
            if(moving->getComponent<CTransform>().position.y > stati_c->getComponent<CTransform>().position.y)
            {
                // => came from bottom
                moving->getComponent<CTransform>().position.y += ol.y;
                //moving->getComponent<CTransform>().velocity.y *= -1 ;
            }moving->getComponent<CTransform>().velocity.y = 0;
            return;
        }

    }
}

