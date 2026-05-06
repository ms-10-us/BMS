#ifndef SIMULATIONWORKER_H
#define SIMULATIONWORKER_H

#include <QObject>
#include "Simulation.h"

class SimulationWorker : public QObject
{
    Q_OBJECT

public:
    SimulationWorker();

signals:
    void progress(int step);
    void finished();

public slots:
    void process(Simulation *simulation);
};

#endif