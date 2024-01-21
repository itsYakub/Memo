#pragma once

#include "raylib.h"

class Timer {
private:
    float m_Time;

public:
    Timer() = default;
    Timer(float time) { m_Time = time; }
    inline void TimerProcess() { m_Time -= GetFrameTime(); }
    inline bool TimerFinished() { return m_Time <= 0; }
};