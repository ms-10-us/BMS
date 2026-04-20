#ifndef ICONCREATOR_H
#define ICONCREATOR_H

#include <QString>
#include <QToolButton>

class IconCreator
{
public:
    IconCreator();

    QToolButton *CreateIcon(const QString iconPath, int iconSize, const QString iconDescription);
};
#endif