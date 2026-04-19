#include "mainwindow.h"
#include "LoadCycleWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <algorithm>
#include <limits>
#include <QDateTime>

#include <QFile>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Battery Simulation Software");
    resize(1000, 1000);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    QHBoxLayout *topBarHorizontalLayout = new QHBoxLayout();

    LoadCycleIcon = new QToolButton(this);
    LoadCycleIcon->setIcon(QIcon(":/icons/LoadCycleData.png"));
    LoadCycleIcon->setIconSize(QSize(128, 128));
    LoadCycleIcon->setFixedSize(128, 128);
    LoadCycleIcon->setToolTip("Open Load Cycle Settings");
    LoadCycleIcon->setFocusPolicy(Qt::NoFocus);
    LoadCycleIcon->setAutoRaise(true);

    LoadCycleIcon->setStyleSheet(
        "QToolButton {"
        "  border: none;"
        "  background: transparent;"
        "  padding: 0px;"
        "  margin: 0px;"
        "}"
        "QToolButton:hover, QToolButton:pressed {"
        "  background: transparent;"
        "  border: none;"
        "}");

    topBarHorizontalLayout->addWidget(LoadCycleIcon);
    topBarHorizontalLayout->addStretch(1);

    mainLayout->addLayout(topBarHorizontalLayout);
    mainLayout->addStretch(1);

    new QLabel("Console:");
    ConsoleOutput = new QPlainTextEdit();
    ConsoleOutput->setReadOnly(true);
    ConsoleOutput->setMaximumHeight(180);
    QFont font("Monospace", 9);
    ConsoleOutput->setFont(font);

    mainLayout->addWidget(ConsoleOutput);

    connect(LoadCycleIcon, &QPushButton::clicked, this, &MainWindow::openLoadCycleWindow);

    log("Application Ready");
}

void MainWindow::log(const QString &msg)
{
    QString ts = QDateTime::currentDateTime().toString("hh:mm:ss");
    ConsoleOutput->appendPlainText("[" + ts + "]" + msg);
}

MainWindow::~MainWindow()
{
    delete ParsedData;
}

void MainWindow::openLoadCycleWindow()
{
    LoadCycleWindow *loadCycleWindow = new LoadCycleWindow();

    connect(loadCycleWindow, &LoadCycleWindow::logMessage, this, &MainWindow::log);

    loadCycleWindow->exec();
}