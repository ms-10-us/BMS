#include "mainwindow.h"
#include "LoadCycleWindow.h"
#include "IconCreator.h"
#include "../3DModeling/CADWidget.h"
#include "../3DModeling/BatteryCADModel.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <algorithm>
#include <limits>
#include <QDateTime>
#include <QSplitter>
#include <QMessageBox>

#include <QFile>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Battery Simulation Software");
    resize(1000, 1000);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(4);

    // Top Horizontal Icons
    QHBoxLayout *topBarHorizontalLayout = new QHBoxLayout();
    IconCreator iconCreator = IconCreator();

    QToolButton *LoadCycleIcon = iconCreator.CreateIcon(":/icons/LoadCycleData.png", 64, "Open Load Cycle Settings");
    QToolButton *PlotDataIcon = iconCreator.CreateIcon(":/icons/PlotData.png", 64, "Plot Data");

    topBarHorizontalLayout->addWidget(LoadCycleIcon);
    topBarHorizontalLayout->addWidget(PlotDataIcon);
    topBarHorizontalLayout->addStretch();

    mainLayout->addLayout(topBarHorizontalLayout);

    // Splitter
    QSplitter *splitter = new QSplitter(Qt::Horizontal, this);
    splitter->setHandleWidth(6);

    // --- Left Area (CAD Widget) ---
    QWidget *leftContainer = new QWidget(this);
    QVBoxLayout *leftLayout = new QVBoxLayout(leftContainer);
    leftLayout->setContentsMargins(0, 0, 0, 0);

    QLabel *leftPanelLabel = new QLabel("Battery CAD Model", leftContainer);
    leftPanelLabel->setStyleSheet({"font-weight: bold; padding: 8px;"});
    leftLayout->addWidget(leftPanelLabel);

    CADWidget *cadWidget = new CADWidget(leftContainer);
    BatteryCADModel batteryCADModel = BatteryCADModel();
    batteryCADModel.generateBatteryCADModel("battery_pack.step");
    cadWidget->loadStep("battery_pack.step");
    leftLayout->addWidget(cadWidget, 1);
    // QLabel *plotPlaceholder = new QLabel(
    //     "Plot Area\n\n"
    //     "• Load a CSV file\n"
    //     "• Select variables on the right\n"
    //     "• Click 'Plot Selected'",
    //     this);
    // plotPlaceholder->setAlignment(Qt::AlignCenter);
    // plotPlaceholder->setStyleSheet(
    //     "background-color: #f8f9fa; "
    //     "border: 2px dashed #aaa; "
    //     "font-size: 15px; color: #555; padding: 40px;");
    // leftLayout->addWidget(plotPlaceholder, 1);

    // Right Panel
    QWidget *rightPanel = new QWidget(this);
    QVBoxLayout *rightPanelLayout = new QVBoxLayout(rightPanel);
    rightPanelLayout->setContentsMargins(0, 0, 0, 0);
    // rightPanelLayout->setSpacing(8);

    QLabel *rightPanelLabel = new QLabel("Parsed Variables", rightPanel);
    rightPanelLabel->setStyleSheet({"font-weight: bold; padding: 8px;"});

    VariableListWidget = new QListWidget(rightPanel);
    VariableListWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);

    rightPanelLayout->addWidget(rightPanelLabel);
    rightPanelLayout->addWidget(VariableListWidget, 1);

    splitter->addWidget(leftContainer);
    splitter->addWidget(rightPanel);

    splitter->setStretchFactor(0, 5);
    splitter->setSizes({820, 280});

    mainLayout->addWidget(splitter, 10);

    // Console
    new QLabel("Console:");
    ConsoleOutput = new QPlainTextEdit(this);
    ConsoleOutput->setReadOnly(true);
    ConsoleOutput->setMaximumHeight(180);
    QFont font("Monospace", 9);
    ConsoleOutput->setFont(font);
    mainLayout->addWidget(ConsoleOutput, 1);

    connect(LoadCycleIcon, &QPushButton::clicked, this, &MainWindow::openLoadCycleWindow);
    connect(PlotDataIcon, &QPushButton::clicked, this, &MainWindow::onPlotSelected);

    log("Application Ready");
}

void MainWindow::openLoadCycleWindow()
{
    LoadCycleWindow *loadCycleWindow = new LoadCycleWindow();

    connect(loadCycleWindow, &LoadCycleWindow::sendCycleData, this, &MainWindow::loadCycleData);

    connect(loadCycleWindow, &LoadCycleWindow::logMessage, this, &MainWindow::log);

    loadCycleWindow->exec();
}

void MainWindow::log(const QString &msg)
{
    QString ts = QDateTime::currentDateTime().toString("hh:mm:ss");
    ConsoleOutput->appendPlainText("[" + ts + "]" + msg);
}

void MainWindow::loadCycleData(DataParse *data)
{
    MainWindowData = data;
    VariableListWidget->clear();

    const std::vector<std::string> &colNames = data->getColumnNames();
    for (const auto &colName : colNames)
    {
        VariableListWidget->addItem(QString::fromStdString(colName));
    }
}

void MainWindow::onPlotSelected()
{
    PlottingToolObject.resetPlottingTool();

    QList<QListWidgetItem *> selectedVaraiables = VariableListWidget->selectedItems();
    if (selectedVaraiables.size() < 2)
    {
        QMessageBox::warning(this, "Selection", "Please select at least two variables (X and Y).");
        log("Please select at least two variables (X and Y).");
        return;
    }

    std::string xName = selectedVaraiables[0]->text().toStdString();
    std::string yName = selectedVaraiables[1]->text().toStdString();

    const std::vector<double> xIdx = MainWindowData->getColumn(xName);
    const std::vector<double> yIdx = MainWindowData->getColumn(yName);

    PlottingToolObject = PlottingTool(xName, yName, yName + " vs " + xName, "b-", 1);

    for (int i = 0; i < MainWindowData->getRowNumber(); i++)
    {
        PlottingToolObject.addPoint(xIdx[i], yIdx[i]);
    }
    PlottingToolObject.plot();
}