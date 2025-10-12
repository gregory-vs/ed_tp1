#include "output.h"
#include <iostream>
#include <iomanip>

Output::Output()
{
    time = 0;
    objectId = -1;
    start = end = 0.0;
}

Output::Output(int time, int objectId, double inicio, double fim)
{
    this->time = time;
    this->objectId = objectId;
    this->start = inicio;
    this->end = fim;
}

int Output::getTime() const { return time; }
int Output::getObjectId() const { return objectId; }
double Output::getStart() const { return start; }
double Output::getEnd() const { return end; }

void Output::setTime(int newTime) { time = newTime; }
void Output::setObjectId(int newId) { objectId = newId; }
void Output::setStart(double newStart) { start = newStart; }
void Output::setEnd(double newEnd) { end = newEnd; }

void Output::print() const
{
    std::cout << std::fixed << std::setprecision(2); // 🔹 fixa 2 casas decimais
    std::cout << "S " << time << " " << objectId << " "
              << start << " " << end << std::endl;
}
