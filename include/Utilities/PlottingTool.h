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
    std::string LineStyle;
    int FigureNumber;

public:
    PlottingTool();

    PlottingTool(std::string xlabel, std::string ylabel, std::string title, std::string lineStyle, int figureNumber);

    void addPoint(double x, double y);

    void plot() const;

    void runPlot(std::barrier<> &syncWait);

    void resetPlottingTool();
};

#endif