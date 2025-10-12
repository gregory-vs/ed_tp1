#include <iostream>
#include <fstream>
#include "object.h"
#include "movement.h"
#include "scene.h"
#include "output.h"
using namespace std;

#define MAX_OBJ 100
#define MAX_MOV 500

struct Interval
{
    double inicio, fim;
};

bool compareByY(const Object &a, const Object &b)
{
    return a.getY() < b.getY();
}

void mergeIntervals(Interval covered[], int &count)
{
    if (count <= 1)
        return;
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

double minValue(double a, double b)
{
    return (a < b) ? a : b;
}

void generateScene(Object obj_list[], int obj_count, Scene *scene)
{
    Interval covered[MAX_OBJ];
    int covered_count = 0;
    Output outputs[MAX_OBJ];
    int output_count = 0;

    // ordena por profundidade
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

        for (int j = 0; j < covered_count; j++)
        {
            double ci = covered[j].inicio;
            double cf = covered[j].fim;
            if (cf <= left)
                continue;
            if (ci >= right)
                break;
            if (ci > left)
                outputs[output_count++] = Output(scene->getTime(), obj_list[i].getId(), left, minValue(right, ci));
            if (cf > left)
                left = cf;
            if (left >= right)
                break;
        }

        if (left < right)
            outputs[output_count++] = Output(scene->getTime(), obj_list[i].getId(), left, right);

        covered[covered_count++] = {inicio, fim};
        mergeIntervals(covered, covered_count);
    }

    for (int i = 0; i < output_count - 1; i++)
    {
        for (int j = i + 1; j < output_count; j++)
        {
            if (outputs[i].getObjectId() > outputs[j].getObjectId())
            {
                Output tmp = outputs[i];
                outputs[i] = outputs[j];
                outputs[j] = tmp;
            }
        }
    }

    for (int i = 0; i < output_count; i++)
        outputs[i].print();
}

void applyMovements(Object obj_list[], int obj_count,
                    Movement move_list[], int move_count,
                    int scene_time)
{
    for (int i = 0; i < move_count; i++)
    {
        if (move_list[i].getTime() <= scene_time)
        {
            int id = move_list[i].getObject().getId();
            Object *obj = Object::findById(obj_list, obj_count, id);
            if (obj != nullptr)
            {
                obj->setPos(move_list[i].getX(), move_list[i].getY());
            }
        }
    }
}

int main(int argc, char *argv[])
{
    istream *input;
    ifstream file;

    if (argc >= 2)
    {
        file.open(argv[1]);
        if (!file.is_open())
        {
            cerr << "Erro: não foi possível abrir o arquivo " << argv[1] << endl;
            return 1;
        }
        input = &file;
    }
    else
    {
        input = &cin; // lê da entrada padrão
    }

    Object obj_list[MAX_OBJ];
    Movement move_list[MAX_MOV];
    int obj_count = 0, move_count = 0;
    char type;

    while (*input >> type)
    {
        if (type == 'O')
        {
            int id;
            double x, y, width;
            *input >> id >> x >> y >> width;
            obj_list[obj_count++] = Object(id, x, y, width);
        }
        else if (type == 'M')
        {
            int time, id;
            double x, y;
            *input >> time >> id >> x >> y;
            Object *obj_ref = Object::findById(obj_list, obj_count, id);
            if (obj_ref != nullptr)
                move_list[move_count++] = Movement(time, *obj_ref, x, y);
        }
        else if (type == 'C')
        {
            int scene_time;
            *input >> scene_time;
            Scene scene(scene_time);
            applyMovements(obj_list, obj_count, move_list, move_count, scene_time);
            generateScene(obj_list, obj_count, &scene);
        }
    }

    if (file.is_open())
        file.close();
    return 0;
}
