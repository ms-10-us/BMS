#include "IconCreator.h"

IconCreator::IconCreator() = default;

QToolButton *IconCreator::CreateIcon(const QString iconPath, int iconSize, const QString iconDescription)
{
    QToolButton *toolButton = new QToolButton();
    toolButton->setIcon(QIcon(iconPath));
    toolButton->setIconSize(QSize(128, 128));
    toolButton->setFixedSize(128, 128);
    toolButton->setToolTip("Open Load Cycle Settings");
    toolButton->setFocusPolicy(Qt::NoFocus);
    toolButton->setAutoRaise(true);

    toolButton->setStyleSheet(
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

    return toolButton;
}