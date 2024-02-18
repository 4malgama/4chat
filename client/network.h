#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>

class QTcpSocket;
class ByteCommand;

class Network : public QObject
{
    Q_OBJECT
    
    QByteArray dataStream;
    
    QTcpSocket* socket;
    QByteArray privateKey;
    int publicKey;
    bool connected;
    bool encrypted;
    
    virtual void readEvent(ByteCommand* data) = 0;
    virtual void disconnectEvent() = 0;
    
    void hello();
    
public:
    explicit Network(QObject *parent = nullptr);
    ~Network();
    
protected:
    void tryConnect(const QString& ip, quint16 port);
    void tryDisconnect();
    void send(const QByteArray& data);
    void sendCrypted(const QByteArray& data, int id = 0);
    
    void setPrivateKey(const QByteArray& key);
    
    bool isEncrypted() const;
    
private:
    void onReadEvent();
    void onStateChanged();
        
signals:
    
};

#endif // NETWORK_H
