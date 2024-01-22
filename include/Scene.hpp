#pragma once

#include "Window.hpp"

class Scene {
public:
    virtual void Init(Window* window) = 0;
    virtual void Destroy() = 0;

    virtual void Update() = 0; /* Function called every frame: only for updating functionality */
    virtual void Render() = 0; /* Function called every frame: only for rendering functionality */
};