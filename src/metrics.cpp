#include "metrics.h"

using namespace std;

Metrics::Metrics()
{
    nObjects = 0;
    nMovements = 0;
    nScenes = 0;
    nReorders = 0;
    localInversions = 0;

    T_reorder_ms = 0;
    T_scene_ms = 0;
    T_total_ms = 0;
}

void Metrics::start()
{
    startTime = std::chrono::steady_clock::now();
}

void Metrics::stop()
{
    auto end = std::chrono::steady_clock::now();
    T_total_ms = chrono::duration<double, milli>(end - startTime).count();
}

void Metrics::printCSV() const
{
    std::cout << nObjects << ","
              << nMovements << ","
              << nScenes << ","
              << nReorders << ","
              << localInversions << ","
              << T_reorder_ms << ","
              << T_scene_ms << ","
              << T_total_ms
              << std::endl;
}
