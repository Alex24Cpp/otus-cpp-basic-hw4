#pragma once
#include "Ball.hpp"

class Dust : public Ball  {
public:
    inline Dust() = default;
    Dust(Point center, Velocity velocity);
    inline int getLiveTime() {return m_liveTime;}
    inline void setLiveTime(const int& liveTime) {m_liveTime = liveTime;}
private:
    int m_liveTime;
};
