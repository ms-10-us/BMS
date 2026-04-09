#ifndef PLOTTINGTOOLASYNC_H
#define PLOTTINGTOOLASYNC_H

#include "PlottingTool.h"

#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <chrono>
#include <barrier>
#include <iostream>

class PlottingToolAsync
{
private:
    std::vector<std::shared_ptr<PlottingTool>> PlottingToolsSharedPtrVector;

    int PlottingToolsVectorSize = 0;

    std::vector<std::thread> PlottingToolAsyncThreads;

    std::unique_ptr<std::barrier<>> syncPoint;

public:
    PlottingToolAsync(std::vector<std::shared_ptr<PlottingTool>> plottingToolsVector);

    void PlotMultiplePlotsAsync();

    ~PlottingToolAsync();
};

#endif