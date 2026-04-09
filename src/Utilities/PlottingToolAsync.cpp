#include "PlottingToolAsync.h"
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

PlottingToolAsync::PlottingToolAsync(std::vector<std::shared_ptr<PlottingTool>> plottingToolsVector)
{
    PlottingToolsVectorSize = plottingToolsVector.size();
    for (int i = 0; i < PlottingToolsVectorSize; i++)
    {
        PlottingToolsSharedPtrVector.push_back(plottingToolsVector[i]);
    }
}

void PlottingToolAsync::PlotMultiplePlotsAsync()
{

    syncPoint = std::make_unique<std::barrier<>>(PlottingToolsVectorSize);

    for (int i = 0; i < PlottingToolsVectorSize; i++)
    {
        PlottingToolAsyncThreads.emplace_back(&PlottingTool::runPlot, PlottingToolsSharedPtrVector[i], std::ref(*syncPoint));
    }

    for (auto &threadObj : PlottingToolAsyncThreads)
    {
        threadObj.join();
    }

    for (auto &plottingTool : PlottingToolsSharedPtrVector)
    {
        plottingTool->plot();
    }

    plt::show();
}

PlottingToolAsync::~PlottingToolAsync()
{
    PlottingToolsSharedPtrVector.clear();
    PlottingToolAsyncThreads.clear();
    PlottingToolsVectorSize = 0;
}