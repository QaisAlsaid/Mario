#include "Phisics.hpp"


Vec2 Phisics::getOverLap(std::shared_ptr<Entity> first, std::shared_ptr<Entity> second)
{
    const auto& f_p = first->getComponent<CTransform>().position;
    const auto& s_p = second->getComponent<CTransform>().position;
    const auto& f_c = first->getComponent<CBoundingBox>().half_size;
    const auto& s_c = second->getComponent<CBoundingBox>().half_size;
    const Vec2 delta = {abs(f_p.x - s_p.x), abs(f_p.y - s_p.y)};
    return Vec2(f_c + s_c - delta) * -1;

}


bool Phisics::isOverLap(std::shared_ptr<Entity> first, std::shared_ptr<Entity> second)
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


Vec2 Phisics::getPrevOverLap(std::shared_ptr<Entity> first, std::shared_ptr<Entity> second)
{
    const auto& f_p = first->getComponent<CTransform>().prev_position;
    const auto& s_p = second->getComponent<CTransform>().prev_position;
    const auto& f_c = first->getComponent<CBoundingBox>().half_size;
    const auto& s_c = second->getComponent<CBoundingBox>().half_size;
    const Vec2 delta = {abs(f_p.x - s_p.x), abs(f_p.y - s_p.y)};
    return Vec2(f_c + s_c - delta) * -1;
}


void Phisics::normalResolution(std::shared_ptr<Entity> moving, std::shared_ptr<Entity> stati_c)
{
    auto ol      = Phisics::getOverLap(moving, stati_c);
    auto prev_ol = Phisics::getPrevOverLap(moving, stati_c);
    const auto epsilon = 1.69;
    if(ol > 0)
    {
        if(ol.y > ol.x && ol.y - ol.x > epsilon)
        {
            if(moving->getComponent<CTransform>().prev_position.x > stati_c->getComponent<CTransform>().prev_position.x)
            {
                // => came from right
                moving->getComponent<CTransform>().position.x += ol.x;
            }
            else if(moving->getComponent<CTransform>().prev_position.x < stati_c->getComponent<CTransform>().prev_position.x)
            {
                // => came from left
                moving->getComponent<CTransform>().position.x += ol.x * -1;
            }
            return;
        }

        else if(ol.x > ol.y && ol.x - ol.y > epsilon)
        {
            if(moving->getComponent<CTransform>().prev_position.y > stati_c->getComponent<CTransform>().prev_position.y)
            {
                // => came from bottom
                moving->getComponent<CTransform>().position.y += ol.y;
            }
            else if(moving->getComponent<CTransform>().prev_position.y < stati_c->getComponent<CTransform>().prev_position.y)
            {
                // => came from top
                moving->getComponent<CTransform>().position.y += ol.y * -1;
            }
            return;
        }
        else if(prev_ol.x > prev_ol.y)
        {
            if(moving->getComponent<CTransform>().prev_position.y > stati_c->getComponent<CTransform>().prev_position.y)
            {
                // => came from bottom
                moving->getComponent<CTransform>().position.y += ol.y;
            }
            else if(moving->getComponent<CTransform>().prev_position.y < stati_c->getComponent<CTransform>().prev_position.y)
            {
                // => came from top
                moving->getComponent<CTransform>().position.y += ol.y * -1;
            }
            return;
        }
        else if(prev_ol.y > prev_ol.x)
        {
            if(moving->getComponent<CTransform>().prev_position.x > stati_c->getComponent<CTransform>().prev_position.x)
            {
                // => came from right
                moving->getComponent<CTransform>().position.x += ol.x;
            }
            else if(moving->getComponent<CTransform>().prev_position.x < stati_c->getComponent<CTransform>().prev_position.x)
            {
                // => came from left
                moving->getComponent<CTransform>().position.x += ol.x * -1;
            }
            return;
        }
        else
        {
            if(moving->getComponent<CTransform>().prev_position.x > stati_c->getComponent<CTransform>().prev_position.x)
            {
                // => came from right
                if(moving->getComponent<CTransform>().prev_position.y > stati_c->getComponent<CTransform>().prev_position.y)
                {
                    // => came from bottom
                    moving->getComponent<CTransform>().position.y += ol.y;
                }
                else if(moving->getComponent<CTransform>().prev_position.y < stati_c->getComponent<CTransform>().prev_position.y)
                {
                    // => came from top
                    moving->getComponent<CTransform>().position.y += ol.y * -1;
                }
                moving->getComponent<CTransform>().position.x += ol.x * -1;
            }
            else if(moving->getComponent<CTransform>().prev_position.x < stati_c->getComponent<CTransform>().prev_position.x)
            {
                // => came from left
                if(moving->getComponent<CTransform>().prev_position.y > stati_c->getComponent<CTransform>().prev_position.y)
                {
                    // => came from bottom
                    moving->getComponent<CTransform>().position.y += ol.y;
                }
                else if(moving->getComponent<CTransform>().prev_position.y < stati_c->getComponent<CTransform>().prev_position.y)
                {
                    // => came from top
                    moving->getComponent<CTransform>().position.y += ol.y * -1;
                }
                moving->getComponent<CTransform>().position.x += ol.x;
            }
        }
    }
}
