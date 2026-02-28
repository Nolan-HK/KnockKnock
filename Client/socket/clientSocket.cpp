#include "clientSocket.h"
#include "../util/util.h"

#include <QTcpSocket>
#include <QHostAddress>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonDocument>


ClientSocket::ClientSocket(QObject* parent) : QObject(parent)
{

    tcpSocket = new QTcpSocket(this);
    ID = -1;

    connect(tcpSocket, &QTcpSocket::readyRead, this, &ClientSocket::sltReadyRead);
    connect(tcpSocket, &QTcpSocket::connected, this, &ClientSocket::sltConnected);
    connect(tcpSocket, &QTcpSocket::disconnected, this, &ClientSocket::sltDisconnected);

}

ClientSocket::~ClientSocket()
{
}

void ClientSocket::setUserID(const int& uid)
{
    ID = uid;
}

int ClientSocket::getUserID() const
{
    return ID;
}


void ClientSocket::checkConnected()
{
    if (tcpSocket->state() != QTcpSocket::ConnectedState)
    {
        qDebug() << "连接服务器中。。";
        //TODO输出消息到日志

        //TODO改为自动获取
        tcpSocket->connectToHost("127.0.0.1", 65535);
    }
    qDebug() << "服务器已连接";

}

void ClientSocket::closeConnected()
{
    if (tcpSocket->isOpen())
        tcpSocket->abort(); //断开连接
}

void ClientSocket::connectedToHost(const QString& host, const int& port)
{
    if (tcpSocket->isOpen())
        tcpSocket->abort();
    tcpSocket->connectToHost(host, port);
}

void ClientSocket::connectedToHost(const QHostAddress& host, const int& port)
{
    if (tcpSocket->isOpen())
        tcpSocket->abort();
    tcpSocket->connectToHost(host, port);
}

void ClientSocket::sltSendMessage(const quint8& type, const QJsonValue& data)
{
    //连接服务器
    if (!tcpSocket->isOpen())
    {
        tcpSocket->connectToHost("127.0.0.1", 65535);   //TODO改为自动获取
        tcpSocket->waitForConnected(30000); //3s
    }

    //超时后
    if (!tcpSocket->isOpen())
        return;

    QJsonObject json;
    json.insert("type", type);
    json.insert("from", ID);
    json.insert("data", data);

    //转为QByteArray
    tcpSocket->write(converToByteArray(json));
    qDebug() << "向服务器发送消息：" << json;

}

void ClientSocket::sltConnected()
{

}
void ClientSocket::sltDisconnected()
{

}

//解析消息并处理
void ClientSocket::sltReadyRead()
{
    QByteArray data = tcpSocket->readAll();
    QJsonObject json = converToJson(data);
    qDebug() << "收到服务器消息：" << json;

    QJsonValue value = json.value("data");
    int msgType = json.value("type").toInt();

    switch (msgType)
    {
    case LoginResult:
    {
        
    }
    default:
        break;
    }

}

void ClientSocket::parseLogin(const QJsonValue& dataVal)
{

}

void ClientSocket::parseReister(const QJsonValue& dataVal)
{
}
