#pragma once
#include "Engien/Scene.hpp"
#include "Engien.hpp"
#include "UIButton.hpp"
#include <fstream>

struct PlayerConfig
{
    int Gx = 0,Gy = 0;
    float Cw, Ch, S, Ms, Js;
    std::string Ba, anim;
};


class SceneGame : public Scene
{
public:
    SceneGame(Engien* engien);
    void update(float delta) override;
private:
    void init();
    void loadLevel(const std::string& path);
    void sMovment(const std::shared_ptr<Entity>& e);
    void spawnPlayer();
    void sCollision(const std::shared_ptr<Entity>& e);
    void showBoundingBox(const std::shared_ptr<Entity>& entity);
    void sLifespan(const std::shared_ptr<Entity>& e);
    void spawnBullet();
    void onEnd(){}
    void handelButton();
    void drawGrid();
    void movePlayer();
    void playerState();
    void spawnCoin(const std::shared_ptr<Entity>& e);
    void showFps();
    Vec2 gridToPixel(const Vec2& grid_pos, const std::shared_ptr<Entity>& e);
    void sRender(const std::shared_ptr<Entity>& e)    override;
    void sDoAction(const Action& action)              override;
    void sAnimation(const std::shared_ptr<Entity>& e) override;

private:
    PlayerConfig m_player_config;
    std::shared_ptr<Entity> m_player;
    sf::View     m_view;
    sf::Text     m_text;
    Vec2         m_grid             = {64, 64};
    bool         m_bounding_box_on  = false;
    bool         m_grid_on          = false;
    bool         m_same_frame       = false;
    bool         m_tux_on           = true;
    bool         m_fps_on           = false;
    short        m_drawn            = 0;
};

