#ifndef COMMANWINDOWFUNCTIONALITY_H
#define COMMANWINDOWFUNCTIONALITY_H

#include <QString>
#include <QPlainTextEdit>

class CommanWindowFunctionality
{
public:
    QPlainTextEdit *ConsoleOutput;

    CommanWindowFunctionality();

    void log(const QString &msg);
};

#endif