#include "Scene.hpp"

void Scene::regesterAction(int action_code, const std::string& action_name)
{
    m_action_map[action_code] = action_name;
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
