#ifndef CLASSES_H
#define CLASSES_H

#include <QString>
#include <QTreeWidgetItem>

class QScrollArea;
class QVBoxLayout;

struct AccountData
{
    QByteArray avatarData;
    QString login;
    QString password;
    QString displayName;
    int rank;
    int score;
    int nextScore;
    int money;
    int gold;
};

struct LoginData
{
    QString login;
    QString password;
};

struct RoomModel
{
    QString name;
    int count;
    int maxCount;
    int minRank;
    int maxRank;
    int cost;
    bool vip;
};

class RoomItem : public QTreeWidgetItem
{
public:
    QString id;
    RoomModel model;
};

struct Chat : public QObject
{
    QWidget* tab;
    QWidget* scrollWgt;
    QScrollArea* area;
    QVBoxLayout* layout;
    QLineEdit* le;
    
    inline Chat(QObject* parent = nullptr) : QObject(parent) {}
};

#endif // CLASSES_H
