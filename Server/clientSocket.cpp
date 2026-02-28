#include "clientSocket.h"
#include "util.h"
#include "database.h"

#include <QFile>
#include <QTcpSocket>
#include <QJsonObject>

ClientSocket::ClientSocket(QObject* parent, QTcpSocket* socket)
{
	ID = -1;

	if (socket == nullptr)
		tcpSocket = new QTcpSocket(this);
	else
		tcpSocket = socket;

	connect(tcpSocket, &QTcpSocket::readyRead, this, &ClientSocket::sltReadyRead);
	connect(tcpSocket, &QTcpSocket::connected, this, &ClientSocket::sltConnected);
	connect(tcpSocket, &QTcpSocket::disconnected, this, &ClientSocket::sltDisconnected);
}

ClientSocket::~ClientSocket()
{
}

int ClientSocket::getUserID() const
{
	return ID;
}

void ClientSocket::close()
{
	tcpSocket->abort();
}
void ClientSocket::sltConnected()
{

}
void ClientSocket::sltDisconnected()
{

}

void ClientSocket::sltReadyRead()
{
	//读取socket数据
	QByteArray reply = tcpSocket->readAll();
	QJsonObject json = converToJson(reply);

	int msgType = json.value("type").toInt();
	int senderID = json.value("from").toInt();

	QJsonValue data = json.value("data");

	qDebug() << "收到" << senderID << "的消息：" << data;

	switch (msgType)
	{
	case Login:
	{
		parserLogin(data);
	}	break;
	default:
		break;
	}
}

void ClientSocket::parserLogin(const QJsonValue& data)
{
	if (data.isObject())
	{
		QJsonObject json = data.toObject();

		QString uid = json.value("uid").toString();
		QString passwd = json.value("passwd").toString();

		QJsonObject result = DataBase::getInstance()->Login(uid, passwd);
		if (result.value("status").toInt() == OK)
			ID = uid.toInt();

		sltSendMessage(result.value("type").toInt(), result);
	}
}

void ClientSocket::sltSendMessage(const quint8& type, const QJsonValue& json)
{
	if (!tcpSocket->isOpen())
		return;

	QJsonObject jsonObj;
	jsonObj.insert("type", type);
	jsonObj.insert("from", ID);
	jsonObj.insert("data", json);
	
	tcpSocket->write(converToByteArray(jsonObj));

	qDebug() << "服务器向用户" << ID << "发送消息：" << jsonObj;
}
