#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "network.h"

struct LoginData;
struct RoomModel;
struct AccountData;

class Account : public Network
{
    QString _login;
    QString roomId;
    AccountData* data;
    
    void readEvent(ByteCommand* cmd) override;
    void disconnectEvent() override;
    
public:
    Account(QObject *parent = nullptr);
    ~Account();
    void start();
    void login(const LoginData& loginData);
    void logout();
    void createRoom(const RoomModel& room);
    void initRoom(const QString& roomId);
    void sendMessage(const QString& roomId, const QString& message);
    
    bool open;
    AccountData* getData() const;
};

#endif // ACCOUNT_H
