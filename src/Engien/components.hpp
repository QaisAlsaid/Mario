#pragma once
#include "comman/Vec2.hpp"
#include "Engien/Animation.hpp"

using namespace kr;


class Component
{
public:
    Component () = default;
    bool has = false;
};


class CTransform : public Component
{
public:
    Vec2 position      = {0, 0};
    Vec2 prev_position = {0, 0};
    Vec2 scale         = {1, 1};
    Vec2 velocity      = {0, 0};
    float angle        = 0;
    bool  isRight      = true;
    CTransform() {};
    CTransform(const Vec2& pos) : position(pos) {}
    CTransform(const Vec2& pos, const Vec2& scale, const Vec2& velocity)
     : position(pos), scale(scale), velocity(velocity) {}

};


class CLifespan : public Component
{
public:
    float life_span = 0;
    float remaining = 0;
    CLifespan() {}
    CLifespan(float duration)
        : life_span(duration), remaining(duration) {}

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
    {this->animation.setRepeated(repeat);}
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
public:
    bool        changed = false;
    std::string state   = "idle";
    CState() {}
    CState(const std::string& state) : state(state) {}
};
