#include "SimulationWorker.h"
#include <QThread>

SimulationWorker::SimulationWorker() = default;

void SimulationWorker::process(Simulation *simulation)
{
    simulation->RunSimulation([this](int step)
                              {
                                emit progress(step);

                                QThread::msleep(100); });

    emit finished();
}