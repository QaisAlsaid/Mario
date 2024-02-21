#pragma once
#include "EntityManager.hpp"
#include "Engien/Assets.hpp"
#include "Engien/Actions.hpp"
#include <map>

class Engien;

class Scene
{
    std::map<int, std::string> m_action_map;
public:
    Engien*               engien;
    EntityManager         entites;
    size_t                current_frame;
    bool                  has_ended;
    bool                  is_paused;
    virtual void update(float delta)                = 0;
    virtual void sDoAction(const Action& action)    = 0;
    virtual void sRender(const std::shared_ptr<Entity>& e) = 0;
    virtual void sAnimation(const std::shared_ptr<Entity>& e) {}
    virtual void handelResize(float aspect_ratio) {}
    void simulate(int count);
    void doAction(const Action& action);
    void regesterAction(int action_code,const std::string& action_name);
    std::map<int, std::string> getActionMap();
    float m_delta = 0;
};
