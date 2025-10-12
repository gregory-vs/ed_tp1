#ifndef OBJECT_H
#define OBJECT_H

class Object
{
private:
    int id;
    double x, y, width;

public:
    Object();
    Object(int id, double x, double y, double width);

    int getId() const;
    double getX() const;
    double getY() const;
    double getWidth() const;

    void setPos(double newX, double newY);
    void setWidth(double newWidth);

    // opcional: operador de atribuição explícito
    Object& operator=(const Object& other);

    static Object* findById(Object* objects, int size, int id);
};

#endif
