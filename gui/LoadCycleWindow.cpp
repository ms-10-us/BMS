#include <QFileDialog>
#include <QMessageBox>
#include <QDialog>
#include <QVBoxLayout>
#include "LoadCycleWindow.h"

LoadCycleWindow::LoadCycleWindow(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Load Cycle Window");
    this->setStyleSheet(
        "LoadCycleWindow {"
        "  background-color: #E0F2F7;" /* Light Blue */
        "  border: 2px solid #005577;" /* Darker blue border */
        "}");
    resize(1200, 750);
    setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);

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
        emit logMessage("Warning: Select a CSV file first.");
        return;
    }

    try
    {
        delete CycleData;
        CycleData = new DataParse(file.toStdString(), CheckHeader->isChecked());

        emit sendCycleData(CycleData);

        emit logMessage(QString("Parse %1 rows x %2 columns").arg(CycleData->getRowNumber()).arg(CycleData->getColNumber()));
    }
    catch (const std::exception &e)
    {
        emit logMessage("Error: " + QString::fromStdString(e.what()));
    }
}

LoadCycleWindow::~LoadCycleWindow()
{
    delete CycleData;
}