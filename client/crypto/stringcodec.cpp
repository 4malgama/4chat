#include "stringcodec.h"
#include <QString>

#include <QDebug>

QByteArray StringCodec::encode(QByteArray data, QByteArray key)
{
    for (int i = 0; i < data.length(); i++)
    {
        char c = (data[i] + key[i % key.length()]) % 0xFF;
        data[i] = c;
    }
    return data;
}

QByteArray StringCodec::decode(QByteArray data, QByteArray key)
{
    for (int i = 0; i < data.length(); i++)
    {
        char c = std::abs((data[i] % 0xFF) - key[i % key.length()]);
        data[i] = c;
    }
    return data;
}

QByteArray StringCodec::encode2(const QString& data, const QString& key)
{
    QString result;
    result.resize(data.length());
    
    quint32 klen = key.length();
    
    const wchar_t* d = (const wchar_t*) data.utf16();
    const wchar_t* k = (const wchar_t*) key.utf16();
    wchar_t *o = (wchar_t*)result.utf16();
    
    for (int i = 0; i < result.length(); i++, d++, o++)
        (*o) = ((*d) + (*(k + i % klen))) % 0xFF;
    
    return result.toUtf8();
}

QByteArray StringCodec::decode2(const QString& data, const QString& key)
{
    QString result;
    result.resize(data.length());
    
    quint32 klen = key.length();
    
    const wchar_t* in = (const wchar_t*) data.utf16();
    const wchar_t* k = (const wchar_t*) key.utf16();
    wchar_t *out = (wchar_t*)result.utf16();
    
    for (int i = 0; i < result.length(); i++, in++, out++)
        (*out) = std::abs(((*in) % 0xFF) - (*(k + i % klen)));
    
    return result.toUtf8();
}

QByteArray StringCodec::encode3(QByteArray data, QByteArray key)
{
    for (int i = 0; i < data.length(); i++)
        data[i] = (data[i] + key[i % key.length()]);
    
    return data;
}

QByteArray StringCodec::decode3(QByteArray data, QByteArray key)
{
    for (int i = 0; i < data.length(); i++)
        data[i] = (data[i]) - key[i % key.length()];
    
    return data;
}