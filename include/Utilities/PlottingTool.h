#ifndef PLOTTINGTOOL_H
#define PLOTTINGTOOL_H

#include <vector>
#include <string>
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
    PlottingTool(std::string xlabel, std::string ylabel, std::string title);

    void addPoint(double x, double y);

    void plot() const;

    // void savePlot() const;

    void resetPlottingTool();
};

#endif