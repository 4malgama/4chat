#include "client.h"
#include "ui_client.h"
#include "account.h"
#include "classes.h"
#include "ui/uicontrol.h"
#include "widgets/message_widget.h"
#include <QMessageBox>
#include <QScrollArea>
#include <QLineEdit>
#include <QTextCodec>
#include <QFile>

#include <QComboBox>

#include <QDebug>

namespace client
{
    Client* w = nullptr;
    
    void close()
    {
        w = nullptr;
    }
    
    void show()
    {
        if (w == nullptr)
        {
            w = new Client();
            QObject::connect(w, &Client::event_close, close);
        }
        else
        {
            w->activateWindow();
        }
    }
    
    void login(const QString& login, const QString& password)
    {
        LoginData ld = { login, password };
        w->login(ld);
    }
    
    Client* get()
    {
        return w;
    }
    
    void initRooms(const QList<RoomItem*>& list)
    {
        w->initRooms(list);
    }
    
    void addRoom(RoomItem* room)
    {
        w->addRoom(room);
    }
    
    void createRoom(const QString& name, int maxCount, int minRank, int maxRank, bool vip, int cost)
    {
        w->createRoom(name, maxCount, minRank, maxRank, vip, cost);
    }
}

namespace createform
{
    void show();
}

namespace profile
{
    void show(const AccountData* accData);
}

Client::Client(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Client)
{
    ui->setupUi(this);    
    acc = new Account();
    control = new UIControl(this);
    
    btnEnter = control->makeButton("Войти");
    ui->frameLayout->addWidget(btnEnter);
    btnEnter->hide();
    
    connect(btnEnter, &QAbstractButton::clicked, this, [this] {
        acc->initRoom(currentRoom->id);
    });
    
    show();
    
    //qInfo() << QTextCodec::codecForLocale()->availableCodecs();
}

Client::~Client()
{
    delete acc;
    delete ui;
}

void Client::login(const LoginData& ld)
{
    acc->login(ld);
}

void Client::cacheAvatar(const QString& owner, const QByteArray& bytes)
{
    if (avatars.contains(owner))
        return;
    
    QPixmap p;
    p.loadFromData(bytes);
    avatars.insert(owner, p);
}

void Client::initRooms(const QList<RoomItem*> rooms)
{
    ui->treeRooms->clear();
    
    for (RoomItem* room : rooms)
    {
        addRoom(room);
    }
}

void Client::addRoom(RoomItem* room)
{
    QString count = QString::number(room->model.count);
    if (room->model.maxCount != 0)
        count.append("/" + QString::number(room->model.maxCount));
    
    room->setText(0, room->id);
    room->setText(1, room->model.name);
    room->setText(2, count);
    
    if (room->model.count >= room->model.maxCount && room->model.maxCount != 0)
    {        
        room->setDisabled(true);
    }
    
    AccountData* accData = acc->getData();
    
    if (room->model.minRank > accData->rank || accData->rank > room->model.maxRank)
    {
        room->setDisabled(true);
    }
    
    ui->treeRooms->addTopLevelItem(room);
}

void Client::createRoom(const QString& name, int maxCount, int minRank, int maxRank, bool vip, int cost)
{
    RoomModel rm;
    rm.name = name;
    rm.maxCount = maxCount;
    rm.minRank = minRank;
    rm.maxRank = maxRank;
    rm.cost = cost;
    rm.vip = vip;
    acc->createRoom(rm);
}

void Client::appendRoom(const QString& roomName, const QString& roomId, const QList<MessageWidget*> messages)
{
    QWidget* tab = new QWidget(this);
    tab->setObjectName("chat");
    
    QScrollArea* chatArea = new QScrollArea(tab);
    chatArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    chatArea->setWidgetResizable(true);
    chatArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    chatArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    
    QWidget* scrollWgt = new QWidget(chatArea);
    scrollWgt->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    chatArea->setWidget(scrollWgt);
    
    QVBoxLayout* chatLayout = new QVBoxLayout(scrollWgt);
    chatLayout->addSpacerItem(new QSpacerItem(0, 1, QSizePolicy::Minimum, QSizePolicy::Expanding));
    
    putMessages(messages, chatLayout, tab);
    
    QLineEdit* leMessage = new QLineEdit(tab);
    leMessage->setPlaceholderText("Начни вводить сообщение...");
    leMessage->setMinimumHeight(30);
    leMessage->setMaximumHeight(30);
    leMessage->setFont(QFont("Roboto", 10));
    connect(leMessage, &QLineEdit::returnPressed, this, [this, roomId, leMessage] {
        acc->sendMessage(roomId, leMessage->text());
        leMessage->clear();
    });
    
    tab->setLayout(new QVBoxLayout(tab));
    tab->layout()->addWidget(chatArea);
    tab->layout()->addWidget(leMessage);
    
    Chat* chat = new Chat(tab);
    chat->tab = tab;
    chat->area = chatArea;
    chat->scrollWgt = scrollWgt;
    chat->layout = chatLayout;
    chat->le = leMessage;
    
    chats.insert(roomId, chat);
    
    ui->pages->addTab(tab, roomName);
    ui->pages->setCurrentWidget(tab);
}

void Client::appendMessage(const QString& roomId, MessageWidget* message)
{
    Chat* chat = chats.value(roomId);
    
    if (message->parent() == nullptr)
        message->setParent(chat->tab);
    
    QString text = parseMessage(message);
    message->setText(text);
    chat->layout->addWidget(message);
}

QPixmap Client::avatar() const
{
    return avatars.value(acc->getData()->login);
}

QPixmap Client::avatar(const QString& login) const
{
    return avatars.value(login);
}

void Client::on_actionConnect_to_server_triggered()
{
    acc->start();
}

void Client::closeEvent(QCloseEvent*)
{
    acc->logout();
    emit event_close();
    delete this;
}

QString Client::parseMessage(const MessageWidget* message)
{
    QString text = message->getText();
    QRegExp e("(\\{[A-z0-9]+\\})");
    int pos = 0;
    
    while ((pos = e.indexIn(text, pos)) != -1)
    {
        int len = e.matchedLength();
        QString smileId = e.cap(1);
        text.replace(pos, len, "<img alt=\"\" src=\"cache/images/emoji/" + smileId.remove(QRegExp("([{}])")) + ".png\" width=\"24\" style=\"vertical-align: middle;\">");
        pos += len;
    }
    
    return text;
}

void Client::on_treeRooms_itemClicked(QTreeWidgetItem *item, int column)
{
    (void)column;       
    currentRoom = (RoomItem*) item;
    
    if (currentRoom->model.maxCount != 0 && currentRoom->model.count >= currentRoom->model.maxCount)
        btnEnter->setDisabled(true);
    
    btnEnter->show();
}

void Client::on_btnCreate_clicked()
{
    createform::show();
}

void Client::on_actionOpen_profile_triggered()
{
    if (acc->open)
        profile::show(acc->getData());
}

void Client::putMessages(const QList<MessageWidget*>& messages, QLayout* layout, QWidget* parent)
{
    for (MessageWidget* message : messages)
    {
        if (message->parent() == nullptr && parent != nullptr)
            message->setParent(parent);
        
//        QString text = message->getText();
//        QRegExp e("(\\{[A-z0-9]+\\})");
//        int pos = 0;
        
//        while ((pos = e.indexIn(text, pos)) != -1)
//        {
//            int len = e.matchedLength();
//            QString smileId = e.cap(1);
//            text.replace(pos, len, "<img alt=\"\" src=\"cache/images/emoji/" + smileId.remove(QRegExp("([{}])")) + ".png\" width=\"24\" style=\"vertical-align: middle;\">");
//            pos += len;
//        }
        
        QString text = parseMessage(message);
        
        message->setText(text);
        
        layout->addWidget(message);
    }
}


void Client::on_treeRooms_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    (void)column;
    currentRoom = (RoomItem*) item;
    acc->initRoom(currentRoom->id);
}

