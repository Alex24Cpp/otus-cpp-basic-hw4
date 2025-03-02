#pragma once
#include "Ball.hpp"
#include "Dust.hpp"
#include <vector>

class Physics {
  public:
    Physics(double timePerTick = 0.001);
    void setWorldBox(const Point& topLeft, const Point& bottomRight);
    void update(std::vector<Ball>& balls, std::vector<Ball>& dusts, size_t ticks, bool stopDusts);

  private:
    void collideBalls(std::vector<Ball>& balls, std::vector<Ball>& dusts);
    void collideWithBox(std::vector<Ball>& balls) const;
    void move(std::vector<Ball>& balls) const;
    void processCollision(Ball& a, Ball& b,
                          double distanceBetweenCenters2) const;
    void creatDusts(std::vector<Ball>& dusts, const Point& center) const;

  private:
    Point topLeft;
    Point bottomRight;
    double timePerTick;
};
