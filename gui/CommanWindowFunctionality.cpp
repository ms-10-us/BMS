#include "CommanWindowFunctionality.h"
#include <QDateTime>
#include <QFont>
#include <QLabel>

CommanWindowFunctionality::CommanWindowFunctionality()
{
    new QLabel("Console:");
    ConsoleOutput = new QPlainTextEdit();
    ConsoleOutput->setReadOnly(true);
    ConsoleOutput->setMaximumHeight(180);
    QFont font("Monospace", 9);
    ConsoleOutput->setFont(font);
}

void CommanWindowFunctionality::log(const QString &msg)
{
    QString ts = QDateTime::currentDateTime().toString("hh:mm:ss");
    ConsoleOutput->appendPlainText("[" + ts + "]" + msg);
}
