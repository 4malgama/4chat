#include "network_packer.h"
#include "../include/json.h"


QByteArray NetworkPacker::pack(const QByteArray& cryptedData, int length, int id)
{
    QJsonObject json;
    json.insert("data", QString(cryptedData));
    json.insert("ln", length);
    json.insert("id", id);
    return QJsonDocument(json).toJson(QJsonDocument::Compact);
}

QByteArray NetworkPacker::unpack(const QByteArray& package, int* ln, int* id)
{
    QJsonDocument doc = QJsonDocument::fromJson(package);
    QJsonObject json = doc.object();
    QString data = json.value("data").toString();
    *ln = json.value("ln").toInt();
    *id = json.value("id").toInt();
    return data.toLocal8Bit();
}