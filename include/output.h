#ifndef OUTPUT_H
#define OUTPUT_H

class Output
{
private:
    int time;
    int objectId;
    double start;
    double end;

public:
    Output();
    Output(int time, int objectId, double start, double end);

    int getTime() const;
    int getObjectId() const;
    double getStart() const;
    double getEnd() const;

    void setTime(int newTime);
    void setObjectId(int newId);
    void setStart(double newInicio);
    void setEnd(double newFim);

    void print() const;
};

#endif // OUTPUT_H
