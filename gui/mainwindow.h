#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolButton>
#include <QPlainTextEdit>
#include <QListWidget>
#include "../dataParser/DataParse.h"
#include "../include/Utilities/PlottingTool.h"

class LoadCycleWindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QPlainTextEdit *ConsoleOutput;

    QListWidget *VariableListWidget = nullptr;

    PlottingTool PlottingToolObject;

    DataParse *MainWindowData = nullptr;

    void openLoadCycleWindow();

    void onPlotSelected();

    void onRunSimulation();

public:
    MainWindow(QWidget *parent = nullptr);

    void log(const QString &msg);

    void loadCycleData(DataParse *data);
};

#endif