#ifndef COMMAND_H
#define COMMAND_H

#include <QList>

class Command
{
public:
    QString name;
    QString source;
    QStringList args;

    Command(const QString& data);
};

#endif // COMMAND_H
