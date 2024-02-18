#include "byte_command.h"
#include <QDebug>


ByteCommand::ByteCommand(QByteArray* data)
{
	args = data->split(';');
	name = args.takeFirst();
}
