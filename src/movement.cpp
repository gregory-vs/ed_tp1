#include "movement.h"

Movement::Movement()
{
    time = 0;
    x = y = 0.0;
}

Movement::Movement(int time, const Object &objeto, double x, double y)
{
    this->time = time;
    this->objeto = objeto;
    this->x = x;
    this->y = y;
}

int Movement::getTime() const { return time; }
Object Movement::getObject() const { return objeto; }
double Movement::getX() const { return x; }
double Movement::getY() const { return y; }

void Movement::setTime(int newTime) { time = newTime; }
void Movement::setObject(const Object &newObject) { objeto = newObject; }
void Movement::setX(double newX) { x = newX; }
void Movement::setY(double newY) { y = newY; }
