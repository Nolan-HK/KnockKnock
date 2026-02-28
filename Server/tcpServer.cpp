#include "tcpServer.h"
#include "clientSocket.h"

#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonObject>
#include <QSqlQuery>

TcpServer::TcpServer(QObject* parent)
{
	tcpServer = new QTcpServer(this);
	connect(tcpServer, &QTcpServer::newConnection, this, &TcpServer::sltNewConnection);


}

TcpServer::~TcpServer()
{
	if (tcpServer->isListening())
		tcpServer->close();
}

bool TcpServer::startListen(int port)
{
	if (tcpServer->isListening())
		tcpServer->close();

	return tcpServer->listen(QHostAddress::Any, quint16(port));
}

void TcpServer::closeListen()
{
	tcpServer->close();
}


TcpMsgServer::TcpMsgServer(QObject* parent) : TcpServer(parent)
{

}

TcpMsgServer::~TcpMsgServer()
{
	foreach (ClientSocket* client, clients)
	{
		clients.removeOne(client);
		client->close();
	}
}

void TcpMsgServer::sltNewConnection()
{
	ClientSocket* client = new ClientSocket(this, tcpServer->nextPendingConnection());
	qDebug() << "新连接客户端：" << client->getClientInfo();

	connect(client, &ClientSocket::signalConnected, this, &TcpMsgServer::sltConnected);
	connect(client, &ClientSocket::signalDisConnected, this, &TcpMsgServer::sltDisConnected);
}


void TcpMsgServer::sltConnected()
{
	ClientSocket* client = static_cast<ClientSocket*>(this->sender());
	if (client == nullptr)
		return;

	connect(client, &ClientSocket::signalMsgToClient, this, &TcpMsgServer::sltMsgToClient);
	connect(client, &ClientSocket::signalDownloadFile, this, &TcpMsgServer::signalDownloadFile);

	clients.push_back(client);
}

void TcpMsgServer::sltDisConnected()
{
	ClientSocket* client = static_cast<ClientSocket*>(this->sender());
	if (client == nullptr) return;

	for (int i = 0; i < clients.size(); i++) {
		if (client == clients.at(i)) {
			clients.remove(i);
			/*Q_EMIT signalUserStatus(QString("用户 [%1] 下线").
				arg(DataBase::Instance()->getUserName(client->getUserID())));*/

			return;
		}
	}

	disconnect(client, &ClientSocket::signalConnected, this, &TcpMsgServer::sltConnected);
	disconnect(client, &ClientSocket::signalDisConnected, this, &TcpMsgServer::sltDisConnected);
	disconnect(client, &ClientSocket::signalMsgToClient,this, &TcpMsgServer::sltMsgToClient);
	disconnect(client, &ClientSocket::signalDownloadFile,this, &TcpMsgServer::signalDownloadFile);
}

void TcpMsgServer::sltMsgToClient(const quint8& type, const int& receiverID, const QJsonValue& jsonVal)
{
	// 查找要发送过去的id
	for (int i = 0; i < clients.size(); i++) {
		if (receiverID == clients.at(i)->getUserID()) {
			clients.at(i)->sltSendMessage(type, jsonVal);
			return;
		}
	}

	//服务器端没有查询到该消息对应的接受者，说明该用户当前不在线，需要先把数据记录在服务器，等到用户上线后再发送
	//if (jsonVal.isObject()) {
	//	QJsonObject json = jsonVal.toObject();
	//	int senderID = json.value("id").toInt();
	//	qint64 time = json.value("time").toInt();
	//	QString msg = json.value("msg").toString();
	//	int tag = json.value("tag").toInt();
	//	int groupID = 0;
	//	if (tag == 1)
	//		groupID = json.value("group").toInt();
	//	qint64 fileSize = json.value("fileSize").toInt();

	//	QSqlQuery query;
	//	query.prepare("INSERT INTO UnreadMsg (senderID, receiverID, groupID, type, time, msg, tag, fileSize) "
	//		"VALUES (?, ?, ?, ?, ?, ?, ?, ?);");
	//	query.bindValue(0, senderID);
	//	query.bindValue(1, receiverID);
	//	query.bindValue(2, tag == 0 ? 0 : groupID);//如果为私聊消息，该字段无效，设为0即可
	//	query.bindValue(3, type);
	//	query.bindValue(4, time);
	//	query.bindValue(5, msg);
	//	query.bindValue(6, tag);
	//	query.bindValue(7, fileSize);

	//	query.exec();
	//	qDebug() << "lastError:" << query.lastError().text();
	//}


}
