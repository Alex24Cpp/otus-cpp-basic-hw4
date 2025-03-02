#include "Dust.hpp"

Dust::Dust(Point center, Velocity velocity) :
    Ball(center, 7, velocity, Color{1, 0, 0}), m_liveTime{500} {
        m_isCollidable = false;
}
