#ifndef METRICS_H
#define METRICS_H

#include <chrono>
#include <iostream>

class Metrics
{
private:
    std::chrono::steady_clock::time_point startTime;

public:
    int nObjects;
    int nMovements;
    int nScenes;
    int nReorders;
    int localInversions;

    long long T_reorder_ms;
    long long T_scene_ms;
    long long T_total_ms;

    Metrics();

    void start();
    void stop();
    void printCSV() const;
};

#endif // METRICS_H
