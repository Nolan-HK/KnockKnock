#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "clientsocket.h"

#include <QObject>
#include<QList>
#include <QVector>

class QTcpServer;
class QTcpSocket;
class QJsonValue;


class TcpServer : public QObject
{
    Q_OBJECT

public:
    explicit TcpServer(QObject* parent = nullptr);
    ~TcpServer();


    bool startListen(int port = 65535);
    void closeListen();

signals:


protected:
    QTcpServer* tcpServer;

public slots:
    virtual void sltNewConnection() = 0;
    virtual void sltConnected() = 0;
    virtual void sltDisConnected() = 0;
};


class TcpMsgServer : public TcpServer
{
    Q_OBJECT
public:
    explicit TcpMsgServer(QObject* parent = nullptr);
    ~TcpMsgServer();

signals:
    void signalDownloadFile(const QJsonValue& json);

private:
    // 客户端管理
    QVector <ClientSocket*> clients;

public slots:
    //void sltTransFileToClient(const int& userId, const QJsonValue& json);

private slots:
    void sltNewConnection();
    void sltConnected();
    void sltDisConnected();
    void sltMsgToClient(const quint8& type, const int& id, const QJsonValue& json);
};




#endif // !TCPSERVER_H