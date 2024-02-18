#ifndef STRINGCODEC_H
#define STRINGCODEC_H

#include <QByteArray>

class StringCodec
{
public:
    static QByteArray encode(QByteArray data, QByteArray key);
    static QByteArray decode(QByteArray data, QByteArray key);
    
    static QByteArray encode2(const QString& data, const QString& key);
    static QByteArray decode2(const QString& data, const QString& key);
    
    static QByteArray encode3(QByteArray data, QByteArray key);
    static QByteArray decode3(QByteArray data, QByteArray key);
};

#endif // STRINGCODEC_H
