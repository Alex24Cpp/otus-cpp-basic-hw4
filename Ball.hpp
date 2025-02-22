#pragma once
#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"

class Ball {
public:
    inline Ball() = default;
    Ball(Point center, double radius, Velocity velocity, Color color);

    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void setCenter(const Point& center);
    Point getCenter() const;
    double getRadius() const;
    double getMass() const;
private:
    int random_value(int max_value);

    Point m_center;
    double m_radius;
    Velocity m_velocity;
    Color m_color;
};
