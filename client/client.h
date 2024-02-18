#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Client; }
QT_END_NAMESPACE

class Account;
struct LoginData;
class RoomItem;
class QTreeWidgetItem;
class UIControl;
class QPushButton;
class MessageWidget;

class Chat;

class Client : public QMainWindow
{
    Q_OBJECT
    
    Account* acc;
    QHash<QString, QPixmap> avatars;
    QHash<QString, Chat*> chats;
    RoomItem* currentRoom;
    
public:
    Client(QWidget *parent = nullptr);
    ~Client();
    
    void login(const LoginData& ld);
    void cacheAvatar(const QString& owner, const QByteArray& bytes);
    void initRooms(const QList<RoomItem*> rooms);
    void addRoom(RoomItem* room);    
    void createRoom(const QString& name, int maxCount, int minRank, int maxRank, bool vip, int cost);    
    void appendRoom(const QString& roomName, const QString& roomId, const QList<MessageWidget*> messages);
    void appendMessage(const QString& roomId, MessageWidget* message);
    
    QPixmap avatar() const;
    QPixmap avatar(const QString& login) const;
    
signals:
    void event_close();
    
private slots:
    void on_actionConnect_to_server_triggered();
    
    void on_treeRooms_itemClicked(QTreeWidgetItem *item, int column);
    
    void on_btnCreate_clicked();
    
    void on_actionOpen_profile_triggered();
    
    void on_treeRooms_itemDoubleClicked(QTreeWidgetItem *item, int column);
    
private:
    Ui::Client *ui;
    UIControl* control;
    void putMessages(const QList<MessageWidget*>& messages, QLayout* layout, QWidget* parent = nullptr);
    void closeEvent(QCloseEvent*);
    QString parseMessage(const MessageWidget* message);
    
    /* control */
    
    QPushButton* btnEnter;
};

#endif // CLIENT_H
