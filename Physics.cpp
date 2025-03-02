#include "Physics.hpp"
#include <cmath>

double dot(const Point& lhs, const Point& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

Physics::Physics(double timePerTick) : timePerTick{timePerTick} {}

void Physics::setWorldBox(const Point& topLeft, const Point& bottomRight) {
    this->topLeft = topLeft;
    this->bottomRight = bottomRight;
}

void Physics::update(std::vector<Ball>& balls, std::vector<Ball>& dusts, const size_t ticks, bool stopDusts) {

    for (size_t i = 0; i < ticks; ++i) {
        move(balls);
        collideWithBox(balls);
        collideBalls(balls, dusts);
        if (stopDusts)
            dusts.clear();
        if (!dusts.empty()) {
            int index{0};
            for (Ball& dust : dusts) {
                int currentLiveTime = static_cast<Dust*>(&dust)->getLiveTime();
                if (currentLiveTime == 0) {
                    dusts.erase(dusts.begin() + index);
                }
                else {
                    static_cast<Dust*>(&dust)->setLiveTime(--currentLiveTime);
                }
                index++;
            }
            move(dusts);
        }
    }
}

void Physics::collideBalls(std::vector<Ball>& balls, std::vector<Ball>& dusts) {
    for (auto a = balls.begin(); a != balls.end(); ++a) {
        if (!a->getIsCollidable()) continue;
        for (auto b = std::next(a); b != balls.end(); ++b) {
            if (!b->getIsCollidable()) continue;
            const double distanceBetweenCenters2 =
                distance2(a->getCenter(), b->getCenter());
            const double collisionDistance = a->getRadius() + b->getRadius();
            const double collisionDistance2 =
                collisionDistance * collisionDistance;

            if (distanceBetweenCenters2 < collisionDistance2) {
                processCollision(*a, *b, distanceBetweenCenters2);
                creatDusts(dusts, a->getCenter()); // centr == a->getCenter() для упрощения. Визуально не влияет
            }
        }
    }
}

void Physics::collideWithBox(std::vector<Ball>& balls) const {
    for (Ball& ball : balls) {
        if (!ball.getIsCollidable()) continue;
        const Point p = ball.getCenter();
        const double r = ball.getRadius();
        // определяет, находится ли v в диапазоне (lo, hi) (не включая границы)
        auto isOutOfRange = [](double v, double lo, double hi) {
            return v < lo || v > hi;
        };

        if (isOutOfRange(p.x, topLeft.x + r, bottomRight.x - r)) {
            Point vector = ball.getVelocity().vector();
            vector.x = -vector.x;
            ball.setVelocity(vector);
        } else if (isOutOfRange(p.y, topLeft.y + r, bottomRight.y - r)) {
            Point vector = ball.getVelocity().vector();
            vector.y = -vector.y;
            ball.setVelocity(vector);
        }
    }
}

void Physics::move(std::vector<Ball>& balls) const {
    for (Ball& ball : balls) {
        Point newPos =
            ball.getCenter() + ball.getVelocity().vector() * timePerTick;
        ball.setCenter(newPos);
    }
}

void Physics::processCollision(Ball& a, Ball& b,
                               double distanceBetweenCenters2) const {
    // нормированный вектор столкновения
    const Point normal =
        (b.getCenter() - a.getCenter()) / std::sqrt(distanceBetweenCenters2);

    // получаем скорость в векторном виде
    const Point aV = a.getVelocity().vector();
    const Point bV = b.getVelocity().vector();

    // коэффициент p учитывает скорость обоих мячей
    const double p =
        2 * (dot(aV, normal) - dot(bV, normal)) / (a.getMass() + b.getMass());

    // задаем новые скорости мячей после столкновения
    a.setVelocity(Velocity(aV - normal * p * a.getMass()));
    b.setVelocity(Velocity(bV + normal * p * b.getMass()));
}

void Physics::creatDusts(std::vector<Ball>& dusts, const Point& center) const {
    for (int i = 0; i < 8; i++) {
        Dust dust = Dust(center, Velocity(500., (M_PI / 4) * i));
        dusts.push_back(dust);
    }
}

