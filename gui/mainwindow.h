#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolButton>
#include <QPlainTextEdit>
#include "../dataParser/DataParse.h"

class LoadCycleWindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QToolButton *LoadCycleIcon = nullptr;

    DataParse *ParsedData = nullptr;

    QPlainTextEdit *ConsoleOutput;

    void openLoadCycleWindow();

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    void log(const QString &msg);
};

#endif