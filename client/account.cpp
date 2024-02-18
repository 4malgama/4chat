#include "account.h"
#include "client.h"
#include "classes.h"
#include "include/json.h"
#include "command.h"
#include "command/byte_command.h"
#include "network_id.h"
#include "widgets/message_widget.h"
#include <QMessageBox>
#include <QFile>

#include <QDebug>

/*
 * Packages ID System:
 *
 * Auth ID range: [ 1; 999 ]
 * System ID range: [ 1000; 2999 ]
 * Lobby ID range: [ 3000; 4999 ]
 * Room ID range: [ 5000; 9999 ]
 * Profile ID range: [ 10000; 10999 ]
*/

namespace authform
{
	void show();
	void hide();
	void block();
	void unblock();
}

namespace client
{
	Client* get();
	void initRooms(const QList<RoomItem*>&);
	void addRoom(RoomItem* room);
}

void Account::readEvent(ByteCommand* cmd)
{
	//ByteCommand cmd(data);

	if (cmd->args.isEmpty())
		return;

	QByteArray command = cmd->args.at(0);

	Client* cl = client::get();

	if (cmd->name == "auth")
	{
		if (command == "set_key")
		{
			if (cmd->args.length() < 2)
				return;

			setPrivateKey(QByteArray::fromBase64(cmd->args.at(1)));
			sendCrypted("system;get_auth_form", GET_AUTH_FORM_ID);
		}
	}
	else if (cmd->name == "system")
	{
		if (command == "set_auth_form")
		{
			authform::show();
		}
		else if (command == "auth_accept")
		{
			authform::hide();
			sendCrypted("system;get_account_data", GET_ACCOUNT_DATA_ID);
		}
		else if (command == "auth_reject")
		{
			if (cmd->args.length() < 2)
				return;

			QJsonDocument doc = QJsonDocument::fromJson(cmd->args.at(1));
			QJsonObject json = doc.object();

			int errorCode = json.value("code").toInt();
			QString message = json.value("message").toString();

			QMessageBox(QMessageBox::Critical, "Ошибка " + QString::number(errorCode), message, QMessageBox::Ok).exec();
			authform::unblock();
		}
		else if (command == "set_account_data")
		{
			if (cmd->args.length() < 2)
				return;

			QJsonDocument doc = QJsonDocument::fromJson(cmd->args.at(1));
			QJsonObject json = doc.object();
			this->data->money = json.value("money").toInt();
			this->data->gold = json.value("gold").toInt();
			this->data->rank = json.value("rank").toInt();
			this->data->score = json.value("score").toInt();
			this->data->nextScore = json.value("nextScore").toInt();
			this->data->displayName = json.value("displayName").toString();
			open = true;

			sendCrypted("system;get_avatar_data", GET_AVATAR_DATA_ID);
		}
		else if (command == "set_avatar_data")
		{
			if (cmd->args.length() < 2)
				return;

			QJsonDocument doc = QJsonDocument::fromJson(cmd->args.at(1));
			QJsonArray bytes = doc.array();

			QByteArray avatarData;
			for (const auto& byte : bytes)
			{
				avatarData.append((quint8)byte.toInt());
			}

//            QFile f("C:/avav.jpg");
//            f.open(QIODevice::WriteOnly);
//            f.write(avatarData);
//            f.close();

			client::get()->cacheAvatar(this->data->login, avatarData);

			sendCrypted("lobby;get_init_rooms", GET_INIT_ROOMS_ID);
		}
	}
	else if (cmd->name == "lobby")
	{
		if (command == "init_rooms")
		{
			if (cmd->args.length() < 2)
				return;

			QJsonDocument doc = QJsonDocument::fromJson(cmd->args.at(1));
			QJsonArray rooms = doc.array();

			QList<RoomItem*> list;

			for (const auto& room : rooms)
			{
				QJsonObject o = room.toObject();

				RoomItem* item = new RoomItem();
				item->id = o.value("id").toString();
				item->model.name = o.value("name").toString();
				item->model.count = o.value("count").toInt();
				item->model.maxCount = o.value("maxCount").toInt();
				item->model.minRank = o.value("minRank").toInt();
				item->model.maxRank = o.value("maxRank").toInt();
				item->model.cost = o.value("cost").toInt();

				list.append(item);
			}

			client::initRooms(list);
		}
		else if (command == "add_room")
		{
			if (cmd->args.length() < 2)
				return;

			QJsonDocument doc = QJsonDocument::fromJson(cmd->args.at(1));
			QJsonObject json = doc.object();

			RoomItem* item = new RoomItem();
			item->id = json.value("id").toString();
			item->model.name = json.value("name").toString();
			item->model.count = json.value("count").toInt();
			item->model.maxCount = json.value("maxCount").toInt();
			item->model.minRank = json.value("minRank").toInt();
			item->model.maxRank = json.value("maxRank").toInt();
			item->model.cost = json.value("cost").toInt();
			item->model.vip = json.value("vip").toBool();

			client::addRoom(item);
		}
	}
	else if (cmd->name == "room")
	{
		if (command == "init_room_messages")
		{
			if (cmd->args.length() < 2)
				return;

			QJsonDocument doc = QJsonDocument::fromJson(cmd->args.at(1));
			QJsonObject json = doc.object();

			QString roomId = json.value("roomId").toString();
			QString roomName = json.value("roomName").toString();
			QJsonArray messages = json.value("messages").toArray();

			QList<MessageWidget*> list;
			for (const QJsonValueRef message : messages)
			{
				QJsonObject obj = message.toObject();
				QString author = obj.value("author").toString();
				QString text = obj.value("text").toString();

				MessageWidget* msg = new MessageWidget(cl->avatar(author), author, text);
				list.append(msg);
			}

			cl->appendRoom(roomName, roomId, list);
		}
		else if (command == "init_room_avatars")
		{
			if (cmd->args.length() < 2)
				return;

			QJsonDocument doc = QJsonDocument::fromJson(cmd->args.at(1));
			QJsonArray json = doc.array();

			for (const QJsonValueRef member : json)
			{
				QJsonObject obj = member.toObject();
				QString id = obj.value("id").toString();

				QByteArray imageData;
				for (const auto b : obj.value("data").toArray())
					imageData.append((quint8)b.toInt());

				cl->cacheAvatar(id, imageData);
			}

			sendCrypted("room;get_init_room_messages;" + roomId.toLocal8Bit(), GET_INIT_ROOM_MESSAGES_ID);
		}
		else if (command == "message")
		{
			if (cmd->args.length() < 3)
				return;

			QString roomId = cmd->args.at(1);

			QJsonDocument doc = QJsonDocument::fromJson(cmd->args.at(2));
			QJsonObject json = doc.object();

			QString author = json.value("author").toString();
			QString text = json.value("text").toString();

			MessageWidget* msg = new MessageWidget(cl->avatar(author), author, text);
			cl->appendMessage(roomId, msg);
		}
		else if (command == "init_user")
		{
			if (cmd->args.length() < 3)
				return;

			QString login = cmd->args.at(1);
			if (login == this->data->login)
				return;

			QJsonDocument doc = QJsonDocument::fromJson(cmd->args.at(2));
			QJsonObject json = doc.object();

			QByteArray imageData;
			for (auto&& b : json.value("avatar").toArray())
				imageData.append((quint8)b.toInt());

			cl->cacheAvatar(login, imageData);
		}
	}
	else if (cmd->name == "profile")
	{
		if (command == "add_score")
		{
			if (cmd->args.length() < 2)
				return;

			this->data->score += cmd->args.at(1).toInt();
		}
		else if (command == "rank_up")
		{
			this->data->rank++;
		}
		else if (command == "add_money")
		{
			if (cmd->args.length() < 2)
				return;

			this->data->money += cmd->args.at(1).toInt();
		}
	}
}

void Account::disconnectEvent()
{
	authform::hide();
	QMessageBox::critical(0, "Ошибка подключения", "Нет соединения.", QMessageBox::Ok);
}

Account::Account(QObject *parent)
	: Network(parent)
{
	data = new AccountData();
	data->rank = 0;
	data->money = 0;
	data->gold = 0;
	data->score = 0;
	data->nextScore = 100;
	open = false;
}

Account::~Account()
{
	delete data;
}

void Account::start()
{
	tryConnect("127.0.0.1", 1337);
}

void Account::login(const LoginData& loginData)
{
	this->_login = loginData.login;
	QJsonObject json;
	json.insert("login", loginData.login);
	json.insert("password", loginData.password);
	data->login = loginData.login;
	data->password = loginData.password;
	QJsonDocument doc(json);
	QByteArray data = doc.toJson(QJsonDocument::Compact);
	authform::block();
	sendCrypted("system;login;" + data, LOGIN_ID);
}

void Account::logout()
{
	sendCrypted("system;c01", C01_ID);
	tryDisconnect();
}

void Account::createRoom(const RoomModel& room)
{
	QJsonObject json;
	json.insert("name", room.name);
	json.insert("maxCount", room.maxCount);
	json.insert("minRank", room.minRank);
	json.insert("maxRank", room.maxRank);
	json.insert("vip", room.vip);
	json.insert("cost", room.cost);
	QJsonDocument doc(json);
	QByteArray data = doc.toJson(QJsonDocument::Compact);
	sendCrypted("lobby;create_room;" + data, CREATE_ROOM_ID);
}

void Account::initRoom(const QString& roomId)
{
	this->roomId = roomId;
	sendCrypted("lobby;enter_room;" + roomId.toLocal8Bit());
}

void Account::sendMessage(const QString& roomId, const QString& message)
{
	sendCrypted("room;send_message;" + roomId.toLocal8Bit() + ";" + message.toUtf8());
}

AccountData* Account::getData() const
{
	return data;
}

