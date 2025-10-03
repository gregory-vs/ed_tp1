#include <iostream>
#include "object.h"
using namespace std;

// funcao: objeto, movimento e cena

int main()
{
    char next_func = 'O';
    bool func_object = true;
    int count = 1;
    char current_func;
    double current_x, current_y, current_width;
    Object previous_obj_list[1];
    cin >> current_func >> current_x >> current_y >> current_width;
    previous_obj_list[0] = Object(current_x, current_y, current_width);

    while (func_object)
    {
        Object *dynamic_obj_list = new Object[count];
        for (int i = 0; i <= count; ++i)
        {
            dynamic_obj_list[i] = Object(previous_obj_list[i].getX(), previous_obj_list[i].getY(), previous_obj_list[i].getWidth());
        }
        cin >> next_func;

        if (next_func == 'O')
        {
            Object *aux_object_list = new Object[count];
            for (int i = 0; i <= count; ++i)
            {
                previous_obj_list[i] = Object(dynamic_obj_list->getX(), dynamic_obj_list->getY(), dynamic_obj_list->getWidth());
            }
            cin >> current_x >> current_y >> current_width;
            ++count;
        }
        else
        {
            func_object = false;
        }
    }

    return 0;
}
