#pragma once
#include "comman/Vec2.hpp"
#include "Engien/Animation.hpp"

using namespace kr::math;


class Component
{
public:
    Component () {}
    bool has = false;
};


class CTransform : public Component
{
public:
    Vec2 position      = {0, 0};
    Vec2 prev_position = {0, 0};
    Vec2 velocity      = {0, 0};
    Vec2 scale         = {1, 1};
    float angle        = 0;
    CTransform() {}
    CTransform(const Vec2& pos) : position(pos) {}
    CTransform(const Vec2& pos, const Vec2& scale, const Vec2& velocity)
     : position(pos), scale(scale), velocity(velocity) {}

};


class CLifespan : public Component
{
public:
    size_t life_span      = 0;
    size_t creation_frame = 0;
    CLifespan() {}
    CLifespan(size_t duration, size_t frame)
        : life_span(duration), creation_frame(frame) {}

};


class CInput : public Component
{
public:
    bool up        = false;
    bool down      = false;
    bool left      = false;
    bool right     = false;
    bool jump      = false;
    bool shoot     = false;
    bool can_shoot = false;
    bool can_jump  = false;
    CInput() {}
};


class CBoundingBox : public Component
{
public:
    Vec2 size;
    Vec2 half_size;
    CBoundingBox() {}
    CBoundingBox (const Vec2& size)
    : size(size), half_size(size/2) {}
};


class CAnimation : public Component
{
public:
    Animation animation;
    bool repeat = false;
    CAnimation() {}
    CAnimation(const Animation& animation, bool repeat) : animation(animation), repeat(repeat)
    {}
};


class CGravity : public Component
{
public:
    float gravity = 0;
    CGravity() {}
    CGravity(float gravity) : gravity(gravity) {}
};


class CState : public Component
{
    std::string state = "idle";
    CState() {}
    CState(const std::string& state) : state(state) {}
};
