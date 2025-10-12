#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "object.h"

class Movement {
private:
    int time;
    Object objeto;
    double x, y;

public:
    Movement();
    Movement(int time, const Object& objeto, double x, double y);

    int getTime() const;
    Object getObject() const;
    double getX() const;
    double getY() const;

    void setTime(int newTime);
    void setObject(const Object& newObject);
    void setX(double newX);
    void setY(double newY);
};

#endif // MOVEMENT_H
