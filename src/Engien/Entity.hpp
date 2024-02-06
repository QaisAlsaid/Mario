#pragma once

#include "components.hpp"
#include <tuple>
#include <string>

class EntityManager;

typedef std::tuple<CTransform,
                    CBoundingBox,
                    CInput,
                    CGravity,
                    CAnimation,
                    CState,
                    CLifespan> ComponentTuple();


class Entity
{
    friend class EntityManager;

    ComponentTuple m_components;
    bool           m_active     = true;
    size_t         m_id         = 0;
    std::string    m_tag        = "Entity";
    Entity(const size_t& id, const std::string& tag){}

public:

    void destroy(){m_active = false;}
    size_t id() const {return m_id;}
    bool isActive() const {return m_active;}
    const std::string& tag() const {return m_tag;}


    // templated methods to deal with tuple component not a big deal
    template<typename T>
    bool hasComponent() const
    {
        return getComponent<T>().has;
    }

    template<typename T, typename... TArgs>
    T& addComponent(TArgs&&... mArgs)
    {
        auto& component = getComponent<T>();
        component = T(std::forward<TArgs>(mArgs)...);
        component.has = true;
        return component;
    }

    template<typename T>
    T& getComponent()
    {
        return std::get<T>(m_components);
    }

    template<typename T>
    const T& getComponent() const
    {
        return std::get<T>(m_components);
    }

    template<typename T>
    void removeComponent()
    {
        getComponent<T> = T();
    }
};
