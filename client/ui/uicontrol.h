#ifndef UICONTROL_H
#define UICONTROL_H

#include <QString>

class QPushButton;
class QToolButton;
class QSpacerItem;
class QWidget;

class UIControl
{
    QWidget* defaultParent;
    
public:
    UIControl(QWidget* parent = nullptr);
    
    QPushButton* makeButton(const QString& text);
    QToolButton* makeTool(const QString& iconName, const QString& toolTip = QString());
    QSpacerItem* makeSpacer(bool vertical);
};

#endif // UICONTROL_H
