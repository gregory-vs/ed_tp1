#ifndef OBJECT_H
#define OBJECT_H

class Object
{
private:
    double x, y, width;

public:
    Object();
    Object(double x, double y, double width);

    double getX() const;
    double getY() const;
    double getWidth() const;

    void setPos(double newX, double newY);
    void setWidth(double newWidth);

    // opcional: operador de atribuição explícito
    Object &operator=(const Object &other)
    {
        if (this != &other)
        {
            x = other.x;
            y = other.y;
            width = other.width;
        }
        return *this;
    }
};

#endif
