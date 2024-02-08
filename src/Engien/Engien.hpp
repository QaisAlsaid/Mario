#pragma once
#include "Scene.hpp"
#include "Assets.hpp"
#include "Actions.hpp"
#include <map>
#include <memory>

class Engien
{
private:

    std::map<std::string, std::shared_ptr<Scene>> m_scenes;
    sf::RenderWindow             m_window;
    Assets                       m_assets;
    std::string                  m_current_scene;
    bool                         m_is_running      = true;
    sf::Clock                    m_clock;
    float                        m_delta;
    size_t                       m_frames          = 0;
    short                        m_fps             = 0;
    size_t                       m_last_delta      = 0;

private:
    void              init(const std::string& file_name, std::string main_scene);
    void              update();
    void              sUserInput();
    void              sEvent();

public:
    Engien(const std::string& file_name, std::string main_scene);
    void              run();
    void              quit();
    Assets&           getAssets();
    std::shared_ptr<Scene> currentScene();
    std::shared_ptr<Scene> getScene(const std::string& name);
    sf::RenderWindow& getWindow(){return m_window;};
    void              changeScene(const std::string& scene_name, std::shared_ptr<Scene> scene);
};
