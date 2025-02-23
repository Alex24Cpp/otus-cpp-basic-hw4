#include "Ball.hpp"
#include <cmath>
#include <fstream>

Ball::Ball(Point center, double radius, Velocity velocity, Color color)
    : m_center{center}, m_radius{radius}, m_velocity{velocity}, m_color{color} {}

/**
 * Задает скорость объекта
 * @param velocity новое значение скорости
 */
void Ball::setVelocity(const Velocity& velocity) {
    // TODO: место для доработки
    m_velocity = velocity;
}

/**
 * @return скорость объекта
 */
Velocity Ball::getVelocity() const {
    // TODO: место для доработки
    return m_velocity;
}

/**
 * @brief Выполняет отрисовку объекта
 * @details объект Ball абстрагирован от конкретного
 * способа отображения пикселей на экране. Он "знаком"
 * лишь с интерфейсом, который предоставляет Painter
 * Рисование выполняется путем вызова painter.draw(...)
 * @param painter контекст отрисовки
 */
void Ball::draw(Painter& painter) const {
    // TODO: место для доработки
    painter.draw(m_center, m_radius, m_color);
}

/**
 * Задает координаты центра объекта
 * @param center новый центр объекта
 */
void Ball::setCenter(const Point& center) {
    // TODO: место для доработки
    m_center = center;
}

/**
 * @return центр объекта
 */
Point Ball::getCenter() const {
    // TODO: место для доработки
    return m_center;
}

/**
 * @brief Возвращает радиус объекта
 * @details обратите внимание, что метод setRadius()
 * не требуется
 */
double Ball::getRadius() const {
    // TODO: место для доработки
    return m_radius;
}

/**
 * Задает радиус объекта
 * @param radius радиус объекта
 */

void Ball::setRadius(const double& radius){
    m_radius = radius;
}

/**
 * @brief Возвращает массу объекта
 * @details В нашем приложении считаем, что все шары
 * состоят из одинакового материала с фиксированной
 * плотностью. В этом случае масса в условных единицах
 * эквивалентна объему: PI * radius^3 * 4. / 3.
 */
double Ball::getMass() const {
    // TODO: место для доработки
    return M_1_PI * pow(m_radius, 3) * 4. / 3.;
}

/**
 * Задает цвет объекта
 * @param color цвет объекта
 */

 void Ball::setColor(const Color& color) {
    m_color = color;
}

/**
 * @brief Переопределение операции ввода >> 
 */
std::istream& operator>>(std::istream &stream, Ball& ball) {
    double x ,y, z;
    // Читаем и задаем координаты центра шара
    stream >> x >> y;
    ball.setCenter(Point{x, y}); 
    //Читаем и задаем вектор скорости шара
    stream >> x >> y;
    ball.setVelocity(Point{x, y});
    // Читаем три составляющие цвета шара (red, green, blue) и задаем цвет шара
    stream >> x >> y >> z;
    ball.setColor(Color{x, y, z});
    // Читаем и задаем радиус шара
    stream >> z;
    ball.setRadius(z);
    return stream;
}
