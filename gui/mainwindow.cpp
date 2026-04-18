#include "mainwindow.h"
#include "LoadCycleWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <algorithm>
#include <limits>

#include <QFile>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), CommanWindowFunctionality()
{
    setWindowTitle("Battery Simulation Software");
    resize(1000, 1000);

    QVBoxLayout *mainLayout = new QVBoxLayout();

    QHBoxLayout *topBarHorizontalLayout = new QHBoxLayout();

    LoadCycleIcon = new QToolButton(this);
    LoadCycleIcon->setIcon(QIcon(":/icons/LoadCycleData.png"));
    LoadCycleIcon->setIconSize(QSize(64, 64));
    LoadCycleIcon->setToolTip("Open Load Cycle Settings");

    topBarHorizontalLayout->addWidget(LoadCycleIcon);

    mainLayout->addLayout(topBarHorizontalLayout);

    mainLayout->addWidget(ConsoleOutput);

    connect(LoadCycleIcon, &QPushButton::clicked, this, &MainWindow::openLoadCycleWindow);

    log("Application Ready");
}

MainWindow::~MainWindow()
{
    delete ParsedData;
}

void MainWindow::openLoadCycleWindow()
{
    LoadCycleWindow loadCycleWindow(this);
    loadCycleWindow.exec();
}