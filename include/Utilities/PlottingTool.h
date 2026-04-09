#ifndef PLOTTINGTOOL_H
#define PLOTTINGTOOL_H

#include "GlobalVariables.h"

#include <vector>
#include <string>
#include <barrier>
#include <mutex>
#include <thread>
#include <chrono>
#include <iostream>

class PlottingTool
{
private:
    std::vector<double> Xpoints;
    std::vector<double> Ypoints;
    std::string Xlabel;
    std::string Ylabel;
    std::string Title;

public:
    PlottingTool();

    PlottingTool(std::string xlabel, std::string ylabel, std::string title);

    void addPoint(double x, double y);

    void plot() const;

    void runPlot(std::barrier<> &syncWait);

    void resetPlottingTool();
};

#endif