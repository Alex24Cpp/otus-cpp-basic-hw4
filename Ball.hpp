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
    void setRadius(const double& radius);
    double getRadius() const;
    double getMass() const;
    void setColor(const Color& color);
    void setIsCollidable(const bool& isCollidable);
    bool getIsCollidable() const;
protected:
    Point m_center;
    double m_radius;
    Velocity m_velocity;
    Color m_color;
    bool m_isCollidable;
};

std::istream& operator>>(std::istream& stream, Ball& ball);

