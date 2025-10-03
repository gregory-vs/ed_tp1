#include "object.h"

Object::Object() {
    x = y = 0;
    width = 0;
}

Object::Object(double x, double y, double width) {
    this->x = x;
    this->y = y;
    this->width = width;
}

double Object::getX() const { return x; }
double Object::getY() const { return y; }
double Object::getWidth() const { return width; }

void Object::setPos(double newX, double newY) {
    this->x = newX;
    this->y = newY;
}

void Object::setWidth(double newWidth) {
    this->width = newWidth;
}
