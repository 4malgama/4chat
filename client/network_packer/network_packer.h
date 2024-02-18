#ifndef NETWORKPACKER_H
#define NETWORKPACKER_H

#include <QByteArray>


class NetworkPacker
{
public:
    static QByteArray pack(const QByteArray& cryptedData, int length, int id);
    static QByteArray unpack(const QByteArray& package, int* ln, int* id);
};

#endif // NETWORKPACKER_H
