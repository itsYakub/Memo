#pragma once

#include "raylib.h"

class Timer {
private:
    float m_Time;

public:
    Timer() = default;
    Timer(float time) { m_Time = time; }
    inline void Reset(float time) { m_Time = time; }
    inline float GetTimeF() { return m_Time; }
    inline int GetTimeI() { return (int) m_Time; }
    inline void Process() { m_Time -= GetFrameTime(); }
    inline bool Finished() { return m_Time <= 0; }
};