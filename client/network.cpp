#include "network.h"
#include "network_packer/network_packer.h"
#include "crypto/qaesencryption.h"
#include "crypto/simple_crypt.h"
#include "command/byte_command.h"
#include <QTcpSocket>
#include <QFile>

#include <QDebug>

void Network::hello()
{
	sendCrypted("auth;hello");
}

Network::Network(QObject *parent)
	: QObject{parent}
{
	socket = new QTcpSocket();
	publicKey = 2;
	encrypted = false;
	connected = false;
	connect(socket, &QAbstractSocket::stateChanged, this, &Network::onStateChanged);
	connect(socket, &QIODevice::readyRead, this, &Network::onReadEvent);
}

Network::~Network()
{
	if (socket->isOpen())
		socket->close();
	delete socket;
}

void Network::tryConnect(const QString& ip, quint16 port)
{
	socket->connectToHost(ip, port);
}

void Network::tryDisconnect()
{
	connected = false;
	socket->disconnectFromHost();
	socket->close();
}

void Network::send(const QByteArray& data)
{
	if (connected)
	{
		socket->write(NetworkPacker::pack(data, data.size(), 0));
		socket->flush();
	}
}

void Network::sendCrypted(const QByteArray& data, int id)
{
	if (connected)
	{
		if (this->encrypted)
		{
			QAESEncryption aes(QAESEncryption::AES_128, QAESEncryption::ECB, QAESEncryption::ZERO);
			QByteArray crypted = aes.encode(data + "#end~", privateKey);
			socket->write(NetworkPacker::pack(crypted.toBase64(), data.length(), id));
			socket->flush();
		}
		else
		{
			QByteArray crypted = SimpleCrypt::encode(data, publicKey);
			socket->write(NetworkPacker::pack(crypted, data.length(), id));
			socket->flush();
		}
	}
}

void Network::setPrivateKey(const QByteArray& key)
{
	privateKey = key;
	this->encrypted = true;
}

bool Network::isEncrypted() const
{
	return this->encrypted;
}

void Network::onReadEvent()
{
	//чтение данных и добавление во временный буфер
	dataStream.append(socket->readAll());

	for (;;)
	{
		//поиск разделителя пакетов
		int i = dataStream.indexOf("$end~");

		//если разделитель не был найден,
		//то продолжить ждать данных от сервера
		if (i == -1)
			break;

		//создание временного хранилища пакета
		//и передача указателя на буфер
		QByteArray p;
		p.setRawData(dataStream.constData(), i);

		int ln, id;

		//процесс распаковки полученного пакета JSON
		QByteArray crypted = NetworkPacker::unpack(p, &ln, &id);
		QByteArray decrypted; //объявление буфера для расшифрованного сообщения

		if (this->encrypted) //если AES-ключ уже получен
		{
			//создание объекта AESEncryption
			//и расшифровка данных с использованием privateKey
			//режим ECB
			QAESEncryption aes(QAESEncryption::AES_128, QAESEncryption::ECB, QAESEncryption::ZERO);
			decrypted = aes.decode(QByteArray::fromBase64(crypted), privateKey);

			{
				int i = decrypted.lastIndexOf("#end~");
				if (i != -1)
					//запись расшифрованных данных в буфер
					decrypted = decrypted.mid(0, i);
				else
					qInfo() << "i:" << i << decrypted;
			}
		}
		else
		{
			//расшифровка с помощью StringCodec
			decrypted = SimpleCrypt::decode(crypted, publicKey);
		}

		ByteCommand command(&decrypted);
		readEvent(&command); //вызов виртуального метода-события с полученным пакетом данных

		dataStream.remove(0, i + 5); //очистка обработанной области данных в буфере

		if (dataStream.isEmpty())
			break;
	}
}

void Network::onStateChanged()
{
	switch (socket->state())
	{
		case QTcpSocket::BoundState:
			break;
		case QTcpSocket::HostLookupState:
			break;
		case QTcpSocket::ClosingState:
			break;
		case QTcpSocket::ConnectedState:
		{
			connected = true;
			hello();
			break;
		}
		case QTcpSocket::ConnectingState:
			break;
		case QTcpSocket::ListeningState:
			break;
		case QTcpSocket::UnconnectedState:
		{
			if (connected)
			{
				disconnectEvent();
				connected = false;
			}
			break;
		}
		default:
			break;
	}
}
