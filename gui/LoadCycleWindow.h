#ifndef LOADCYCLEWINDOW_H
#define LOADCYCLEWINDOW_H

#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include "../dataParser/DataParse.h"
#include "mainwindow.h"

class LoadCycleWindow : public QDialog
{
    Q_OBJECT
private:
    QLineEdit *FilePathEdit = nullptr;
    QPushButton *BtnImport = nullptr;
    QPushButton *BtnParse = nullptr;
    QCheckBox *CheckHeader = nullptr;

    DataParse *CycleData = nullptr;

    void onImportClicked();

    void onParseClicked();

public:
    LoadCycleWindow(QWidget *parent = nullptr);

    ~LoadCycleWindow();

signals:
    void logMessage(const QString &message);

    void sendCycleData(const DataParse *data);
};

#endif