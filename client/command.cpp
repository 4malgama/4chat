#include "command.h"


Command::Command(const QString& data)
{
    source = data;
    args = data.split(';');
    name = args.takeFirst();
}
