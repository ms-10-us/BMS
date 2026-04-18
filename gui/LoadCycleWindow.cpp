#include "LoadCycleWindow.h"
#include "mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

LoadCycleWindow::LoadCycleWindow(QWidget *parent) : QDialog(parent), CommanWindowFunctionality()
{
    setWindowTitle("Load Cycle Window");
    resize(1200, 750);

    QVBoxLayout *loadCycleLayout = new QVBoxLayout(this);
    FilePathEdit = new QLineEdit();
    FilePathEdit->setReadOnly(true);
    FilePathEdit->setPlaceholderText("No File Selected");

    BtnImport = new QPushButton("Browse CSV Files");
    CheckHeader = new QCheckBox("Has Header");
    CheckHeader->setChecked(true);
    BtnParse = new QPushButton("Parse & Load");

    loadCycleLayout->addWidget(FilePathEdit, 1);
    loadCycleLayout->addWidget(BtnImport);
    loadCycleLayout->addWidget(CheckHeader);
    loadCycleLayout->addWidget(BtnParse);

    connect(BtnImport, &QPushButton::clicked, this, &LoadCycleWindow::onImportClicked);
    connect(BtnParse, &QPushButton::clicked, this, &LoadCycleWindow::onParseClicked);
}

void LoadCycleWindow::onImportClicked()
{
    QString file = QFileDialog::getOpenFileName(this, "Open CSV", "data/", "CSV (*.csv)");
    if (!file.isEmpty())
    {
        FilePathEdit->setText(file);
    }
}

void LoadCycleWindow::onParseClicked()
{
    QString file = FilePathEdit->text();
    if (file.isEmpty())
    {
        QMessageBox::warning(this, "Warning", "Select a CSV file first.");
        log(QString("Warning: Select a CSV file first."));
        return;
    }

    try
    {
        delete CycleData;
        CycleData = new DataParse(file.toStdString(), CheckHeader->isChecked());

        log(QString("Parse %1 rows x %2 columns").arg(CycleData->getRowNumber()).arg(CycleData->getColNumber()));
    }
    catch (const std::exception &e)
    {
        log("Error: " + QString::fromStdString(e.what()));
    }
}

LoadCycleWindow::~LoadCycleWindow()
{
    delete CycleData;
}