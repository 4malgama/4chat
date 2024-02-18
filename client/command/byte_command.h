#ifndef BYTECOMMAND_H
#define BYTECOMMAND_H

#include <QList>
#include <QByteArray>

class ByteCommand
{
public:
	QByteArray name;
	QList<QByteArray> args;

	ByteCommand(QByteArray* data);
};

#endif // BYTECOMMAND_H
