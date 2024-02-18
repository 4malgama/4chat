#include "simple_crypt.h"

QByteArray SimpleCrypt::encode(QByteArray data, int key)
{
    for (int i = 0; i < data.length(); i++)
        data[i] = data[i] + key;
    
    return data;
}

QByteArray SimpleCrypt::decode(QByteArray data, int key)
{
    for (int i = 0; i < data.length(); i++)
        data[i] = data[i] - key;
    
    return data;
}
