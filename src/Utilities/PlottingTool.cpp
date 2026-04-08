#include "../../include/Utilities/PlottingTool.h"
#include "matplotlibcpp.h"

#include <vector>
#include <string>
#include <iostream>

namespace plt = matplotlibcpp;

PlottingTool::PlottingTool(std::string xlabel, std::string ylabel, std::string title)
{
    Xlabel = xlabel;
    Ylabel = ylabel;
    Title = title;
}

void PlottingTool::addPoint(double x, double y)
{
    Xpoints.push_back(x);
    Ypoints.push_back(y);
}

void PlottingTool::plot() const
{
    if (Xpoints.empty() || Ypoints.empty())
    {
        std::cerr << "No Ploints available For Plotting";
    }
    else
    {
        plt::figure();
        plt::plot(Xpoints, Ypoints);
        plt::title(Title);
        plt::xlabel(Xlabel);
        plt::ylabel(Ylabel);
        plt::grid(true);
        plt::show();
    }
}

void PlottingTool::resetPlottingTool()
{
    Xpoints.clear();
    Ypoints.clear();
    Xlabel = "";
    Ylabel = "";
    Title = "";
}