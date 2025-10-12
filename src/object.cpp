#include "object.h"

Object::Object() {
    x = y = 0;
    width = 0;
}

Object::Object(int id, double x, double y, double width) {
    this->id = id;
    this->x = x;
    this->y = y;
    this->width = width;
}

int Object::getId() const { return id; }
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

Object& Object::operator=(const Object& other) {
    if (this != &other) {
        this->id = other.id;
        this->x = other.x;
        this->y = other.y;
        this->width = other.width;
    }
    return *this;
}

Object* Object::findById(Object* objects, int size, int id) {
    for (int i = 0; i < size; i++) {
        if (objects[i].getId() == id) {
            return &objects[i];
        }
    }
    return nullptr;
}