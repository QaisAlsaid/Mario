#include "Scene.hpp"

void Scene::regesterAction(const Action& action)
{
    actions.push_back(action);
}


void Scene::simulate(int count)
{
    for(int i = 0; i < count; i++)
    {
        update();
    }
}


void Scene::doAction(const Action& action)
{
    sDoAction(action);
}


std::map<int, std::string> Scene::getActionMap()
{
    return m_action_map;
}
