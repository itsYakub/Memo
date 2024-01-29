#pragma once

#include "Window.hpp"

class Scene {
public:
    Scene() = default;
    virtual ~Scene() { Destroy(); };

    virtual void Init() { };
    virtual void Destroy() { };

    virtual void Update() { } /* Function called every frame: only for updating functionality */
    virtual void Render() { } /* Function called every frame: only for rendering functionality */
};