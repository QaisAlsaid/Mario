#pragma once
#include "EntityManager.hpp"
#include "Engien/Assets.hpp"
#include "Engien/Actions.hpp"
#include <map>

class Engien;

class Scene
{
public:
    std::map<int, std::string> m_action_map;

public:
    Engien*               engien;
    EntityManager         entites;
    std::vector<Action>   actions;
    size_t                current_frame;
    bool                  has_ended;
    bool                  is_paused;
    virtual void update()                         = 0;
    virtual void sDoAction(const Action& action)  = 0;
    virtual void sRender()                        = 0;
    void simulate(int count);
    void doAction(const Action& action);
    void regesterAction(const Action& action);
    std::map<int, std::string> getActionMap();
};
