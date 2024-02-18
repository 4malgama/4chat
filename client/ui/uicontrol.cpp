#include "uicontrol.h"
#include <QPushButton>
#include <QToolButton>
#include <QSpacerItem>


UIControl::UIControl(QWidget* parent)
{
    defaultParent = parent;
}

QPushButton* UIControl::makeButton(const QString& text)
{
    QPushButton* button = new QPushButton(defaultParent);
    button->setText(text);
    button->setMinimumHeight(30);
    button->setCursor(Qt::PointingHandCursor);
    return button;
}

QToolButton* UIControl::makeTool(const QString& iconName, const QString& toolTip)
{
    QToolButton* button = new QToolButton(defaultParent);
    button->setIcon(QIcon(iconName));
    button->setIconSize({24, 24});
    button->setToolTip(toolTip);
    button->setCursor(Qt::PointingHandCursor);
    return button;
}

QSpacerItem* UIControl::makeSpacer(bool vertical)
{
    if (vertical)
        return new QSpacerItem(0, 1, QSizePolicy::Minimum, QSizePolicy::Expanding);
    return new QSpacerItem(1, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
}
