#include "mainwindow.h"
#include "LoadCycleWindow.h"
#include "IconCreator.h"
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

    // --- Left Area (where your plot will go) ---
    QWidget *leftArea = new QWidget(this);
    QVBoxLayout *leftLayout = new QVBoxLayout(leftArea);
    leftLayout->setContentsMargins(0, 0, 0, 0);

    QLabel *plotPlaceholder = new QLabel(
        "Plot Area\n\n"
        "• Load a CSV file\n"
        "• Select variables on the right\n"
        "• Click 'Plot Selected'",
        this);
    plotPlaceholder->setAlignment(Qt::AlignCenter);
    plotPlaceholder->setStyleSheet(
        "background-color: #f8f9fa; "
        "border: 2px dashed #aaa; "
        "font-size: 15px; color: #555; padding: 40px;");
    leftLayout->addWidget(plotPlaceholder, 1);

    // Right Panel
    QWidget *rightPanel = new QWidget(this);
    QVBoxLayout *rightPanelLayout = new QVBoxLayout(rightPanel);
    rightPanelLayout->setContentsMargins(10, 10, 10, 10);
    rightPanelLayout->setSpacing(8);

    QLabel *rightPanelLabel = new QLabel("Parsed Variables", rightPanel);
    rightPanelLabel->setStyleSheet({"font-weight: bold; padding: 8px;"});

    VariableListWidget = new QListWidget(rightPanel);
    VariableListWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);

    rightPanelLayout->addWidget(rightPanelLabel);
    rightPanelLayout->addWidget(VariableListWidget, 1);

    splitter->addWidget(leftArea);
    splitter->addWidget(rightPanel);

    splitter->setStretchFactor(0, 5);
    splitter->setSizes({820, 280});

    mainLayout->addWidget(splitter, 1);

    // Console
    new QLabel("Console:");
    ConsoleOutput = new QPlainTextEdit(this);
    ConsoleOutput->setReadOnly(true);
    ConsoleOutput->setMaximumHeight(180);
    QFont font("Monospace", 9);
    ConsoleOutput->setFont(font);
    mainLayout->addWidget(ConsoleOutput);

    connect(LoadCycleIcon, &QPushButton::clicked, this, &MainWindow::openLoadCycleWindow);

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

void MainWindow::loadCycleData(const DataParse *data)
{
    VariableListWidget->clear();

    const std::vector<std::string> &colNames = data->getColumnNames();
    for (const auto &colName : colNames)
    {
        VariableListWidget->addItem(QString::fromStdString(colName));
    }
}

void MainWindow::onPlotSelected()
{
    QList<QListWidgetItem *> selectedVaraiables = VariableListWidget->selectedItems();
    if (selectedVaraiables.size() < 2)
    {
        QMessageBox::warning(this, "Selection", "Please select at least two variables (X and Y).");
        return;
    }
}