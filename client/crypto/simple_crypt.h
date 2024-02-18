#ifndef SIMPLECRYPT_H
#define SIMPLECRYPT_H

#include <QByteArray>

class SimpleCrypt
{
public:
    static QByteArray encode(QByteArray data, int key);
    static QByteArray decode(QByteArray data, int key);
};

#endif // SIMPLECRYPT_H
