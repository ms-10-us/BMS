#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolButton>
#include "../dataParser/DataParse.h"
#include "CommanWindowFunctionality.h"

class MainWindow : public QMainWindow, CommanWindowFunctionality
{
    Q_OBJECT

private:
    QToolButton *LoadCycleIcon = nullptr;

    DataParse *ParsedData = nullptr;

    void openLoadCycleWindow();

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();
};

#endif