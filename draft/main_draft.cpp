#include <iostream>
#include <algorithm>
#include "object.h"
#include "movement.h"
#include "scene.h"
#include "output.h"
using namespace std;

#define MAX_OBJ 100

struct Interval
{
    double inicio;
    double fim;
};

// compara profundidade (menor y = mais distante)
bool compareByY(const Object &a, const Object &b)
{
    return a.getY() < b.getY();
}

// funde intervalos sobrepostos (mantém lista ordenada e compacta)
void mergeIntervals(Interval covered[], int &count)
{
    if (count <= 1)
        return;

    // ordena por início
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if (covered[i].inicio > covered[j].inicio)
            {
                Interval tmp = covered[i];
                covered[i] = covered[j];
                covered[j] = tmp;
            }
        }
    }

    // faz a fusão
    int idx = 0;
    for (int i = 1; i < count; i++)
    {
        if (covered[i].inicio <= covered[idx].fim)
        {
            if (covered[i].fim > covered[idx].fim)
                covered[idx].fim = covered[i].fim;
        }
        else
        {
            idx++;
            covered[idx] = covered[i];
        }
    }
    count = idx + 1;
}

void generateScene(Object obj_list[], int obj_count, Scene *scene)
{
    Interval covered[MAX_OBJ];
    int covered_count = 0;

    for (int i = 0; i < obj_count - 1; i++)
    {
        for (int j = i + 1; j < obj_count; j++)
        {
            if (compareByY(obj_list[j], obj_list[i]))
            {
                Object tmp = obj_list[i];
                obj_list[i] = obj_list[j];
                obj_list[j] = tmp;
            }
        }
    }

    for (int i = 0; i < obj_count; i++)
    {
        double inicio = obj_list[i].getX() - obj_list[i].getWidth() / 2.0;
        double fim = obj_list[i].getX() + obj_list[i].getWidth() / 2.0;

        double left = inicio;
        double right = fim;

        // percorre intervalos cobertos
        for (int j = 0; j < covered_count; j++)
        {
            double ci = covered[j].inicio;
            double cf = covered[j].fim;

            // completamente à esquerda -> ignora
            if (cf <= left)
                continue;

            // completamente à direita -> não há mais sobreposição
            if (ci >= right)
                break;

            // há parte visível antes da cobertura
            if (ci > left)
            {
                Output out(scene->getTime(), obj_list[i].getId(), left, min(right, ci));
                out.print();
            }

            // atualiza limite esquerdo
            if (cf > left)
                left = cf;
            if (left >= right)
                break;
        }

        // parte final visível (após todas as coberturas)
        if (left < right)
        {
            Output out(scene->getTime(), obj_list[i].getId(), left, right);
            out.print();
        }

        // adiciona intervalo atual à lista de cobertos
        covered[covered_count].inicio = inicio;
        covered[covered_count].fim = fim;
        covered_count++;

        // funde sobreposições
        mergeIntervals(covered, covered_count);
    }
}

void defineObj(Object obj_list[])
{

    obj_list[0] = Object(1, 4, 2.5, 3);
    obj_list[1] = Object(2, 2.5, 5, 3);
    obj_list[2] = Object(3, 2, 3, 1);
    obj_list[3] = Object(4, 4, 2, 2);
    obj_list[4] = Object(5, 6, 3, 3);
    obj_list[5] = Object(6, 5, 4, 3);
}

void defineMov(Object *obj_list, Movement move_list[])
{
    Object *obj1 = Object::findById(obj_list, 6, 1);
    Object *obj2 = Object::findById(obj_list, 6, 2);
    Object *obj3 = Object::findById(obj_list, 6, 3);
    Object *obj4 = Object::findById(obj_list, 6, 4);
    Object *obj5 = Object::findById(obj_list, 6, 5);
    Object *obj6 = Object::findById(obj_list, 6, 6);
    // move_list[0] = Movement(5, obj2, 2.5, 5);
    // move_list[1] = Movement(6, obj1, 4.5, 2.5);
    // move_list[2] = Movement(6, obj3, 1.5, 4);
    // move_list[3] = Movement(7, obj6, 6.5, 4);
    // move_list[4] = Movement(7, obj5, 5.5, 2);
    // move_list[5] = Movement(7, obj4, 4, 1);
}

int main()
{
    char next_func = 'O';
    int count = 0, current_id, scene_time, current_time, current_obj_id;
    char current_func;
    double current_x, current_y, current_width;

    Object obj_list[6];
    Movement move_list[6];
    Scene *scene = new Scene();

    // while (next_func == 'O')
    // {
    //     cin >> current_func;
    //     next_func = current_func;
    //     if (next_func != 'O')
    //         break;

    //     cin >> current_id >> current_x >> current_y >> current_width;
    //     obj_list[count] = Object(current_id, current_x, current_y, current_width);
    //     ++count;
    // }

    // count = 0;
    // while (next_func == 'M')
    // {
    //     cin >> current_time >> current_obj_id >> current_x >> current_y;

    //     Object *obj_ref = Object::findById(obj_list, 6, current_obj_id);
    //     if (obj_ref != nullptr)
    //     {
    //         move_list[count] = Movement(current_time, obj_ref, current_x, current_y);
    //         obj_ref->setPos(current_x, current_y);
    //     }

    //     cin >> current_func;
    //     next_func = current_func;
    //     ++count;
    // }

    // cin >> scene_time;

    defineObj(obj_list);
    defineMov(obj_list, move_list);

    scene->setTime(scene_time);

    generateScene(obj_list, count, scene);

    delete scene;
    return 0;
}

/*while (func_object)
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
}*/