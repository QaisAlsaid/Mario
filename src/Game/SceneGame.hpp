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
    void sMovment(std::shared_ptr<Entity> e);
    void spawnPlayer();
    void sCollision();
    void showBoundingBox(const std::shared_ptr<Entity> entity);
    void sLifespan(){}
    void onEnd(){}
    void drawGrid();
    void movePlayer();
    Vec2 gridToPixel(const Vec2& grid_pos, std::shared_ptr<Entity> entity);
    void sRender()                       override;
    void sDoAction(const Action& action) override;
    void sAnimation()                    override;

private:
    PlayerConfig m_player_config;
    std::shared_ptr<Entity> m_player;
    sf::View     m_view;
    Vec2         m_grid             = {64, 64};
    Vec2         m_level            = {2000, 2000};
    bool         m_bounding_box_on  = false;
    bool         m_tux_on           = true;
};

