#include <iostream>
#include <fstream>
#include <string>
#include "object.h"
#include "movement.h"
#include "scene.h"
#include "output.h"
#include "metrics.h"

using namespace std;

#define MAX_OBJ 100
#define MAX_MOV 500

struct Interval
{
    double inicio, fim;
};

void reorderObjects(Object obj_list[], int obj_count, Metrics &metrics) {
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < obj_count - 1; i++) {
        for (int j = i + 1; j < obj_count; j++) {
            if (obj_list[j].getY() < obj_list[i].getY()) {
                Object tmp = obj_list[i];
                obj_list[i] = obj_list[j];
                obj_list[j] = tmp;
            }
        }
    }

    auto end = chrono::high_resolution_clock::now();
    double elapsed = chrono::duration<double, milli>(end - start).count();
    metrics.T_reorder_ms += elapsed;
    metrics.nReorders++;
}

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

void generateScene(Object obj_list[], int obj_count, Scene *scene, Metrics &metrics)
{
    auto start = chrono::high_resolution_clock::now();
    Interval covered[MAX_OBJ];
    int covered_count = 0;
    Output outputs[MAX_OBJ];
    int output_count = 0;

    // ordena por profundidade
    reorderObjects(obj_list, obj_count, metrics);

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

    // for (int i = 0; i < output_count; i++)
    //     outputs[i].print();

    auto end = chrono::high_resolution_clock::now();
    metrics.T_scene_ms += chrono::duration<double, milli>(end - start).count();
    metrics.nScenes++;
}

// void applyMovements(Object obj_list[], int obj_count,
//                     Movement move_list[], int move_count,
//                     int scene_time)
// {
//     for (int i = 0; i < move_count; i++)
//     {
//         if (move_list[i].getTime() <= scene_time)
//         {
//             int id = move_list[i].getObject().getId();
//             Object *obj = Object::findById(obj_list, obj_count, id);
//             if (obj != nullptr)
//             {
//                 obj->setPos(move_list[i].getX(), move_list[i].getY());
//             }
//         }
//     }
// }

void applyMovements(Object obj_list[], int obj_count,
                    Movement move_list[], int move_count,
                    int scene_time, int threshold, Metrics &metrics)
{
    static int disorder_score = 0;
    static bool sorted_flag = true;

    for (int i = 0; i < move_count; i++) {
        if (move_list[i].getTime() <= scene_time) {
            int id = move_list[i].getObject().getId();
            Object* obj = Object::findById(obj_list, obj_count, id);
            if (obj != nullptr) {
                int idxUpdated = obj - obj_list; // índice do objeto

                obj->setPos(move_list[i].getX(), move_list[i].getY());

                // verifica inversões locais
                int local_inv = 0;
                if (idxUpdated > 0 && obj_list[idxUpdated - 1].getY() > obj_list[idxUpdated].getY())
                    local_inv++;
                if (idxUpdated < obj_count - 1 && obj_list[idxUpdated].getY() > obj_list[idxUpdated + 1].getY())
                    local_inv++;

                if (local_inv > 0) {
                    disorder_score += local_inv;
                    metrics.localInversions += local_inv;
                    sorted_flag = false;
                }

                // se passou do limiar, reordena
                if (disorder_score >= threshold) {
                    auto t0 = std::chrono::high_resolution_clock::now();
                    reorderObjects(obj_list, obj_count, metrics);
                    auto t1 = std::chrono::high_resolution_clock::now();
                    metrics.T_reorder_ms += std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
                    metrics.nReorders++;
                    disorder_score = 0;
                    sorted_flag = true;
                }
            }
        }
    }

    // garante ordenação antes da cena
    if (!sorted_flag) {
        auto t0 = std::chrono::high_resolution_clock::now();
        reorderObjects(obj_list, obj_count, metrics);
        auto t1 = std::chrono::high_resolution_clock::now();
        metrics.T_reorder_ms += std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
        metrics.nReorders++;
        disorder_score = 0;
        sorted_flag = true;
    }
}

int main(int argc, char *argv[])
{
    string inputFile = argv[1];
    int threshold = stoi(argv[2]); // segundo argumento (ex: 0, 10, 100...)

    ifstream input(inputFile);
    if (!input.is_open())
    {
        cerr << "Erro ao abrir arquivo: " << inputFile << endl;
        return 1;
    }


    Metrics metrics;
    metrics.start();

    Object obj_list[MAX_OBJ];
    Movement move_list[MAX_MOV];
    int obj_count = 0, move_count = 0;
    char type;

    while (input >> type)
    {
        if (type == 'O')
        {
            int id;
            double x, y, width;
            input >> id >> x >> y >> width;
            obj_list[obj_count++] = Object(id, x, y, width);
            metrics.nObjects++;
        }
        else if (type == 'M')
        {
            int time, id;
            double x, y;
            input >> time >> id >> x >> y;
            Object *obj_ref = Object::findById(obj_list, obj_count, id);
            if (obj_ref != nullptr)
                move_list[move_count++] = Movement(time, *obj_ref, x, y);
            metrics.nMovements++;
        }
        else if (type == 'C')
        {
            int scene_time;
            input >> scene_time;
            Scene scene(scene_time);
            applyMovements(obj_list, obj_count, move_list, move_count, scene_time, threshold, metrics);

            auto t2 = std::chrono::high_resolution_clock::now();
            generateScene(obj_list, obj_count, &scene, metrics);
            auto t3 = std::chrono::high_resolution_clock::now();
            metrics.T_scene_ms += std::chrono::duration_cast<std::chrono::milliseconds>(t3 - t2).count();
            metrics.nScenes++;
        }
    }

    metrics.stop();
    metrics.printCSV();

    return 0;
}
