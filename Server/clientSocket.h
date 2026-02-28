#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include "util.h"

#include <QTcpSocket>

class QObject;
class QTcpSocket;
class QByteArray;
class QFile;
class FileReceiver;

class ClientSocket : public QObject
{
    Q_OBJECT
public:
    explicit ClientSocket(QObject* parent = nullptr, QTcpSocket* tcpSocket = nullptr);
    ~ClientSocket();

    int getUserID() const;
    void close();
    QString getClientInfo() {
        return QString("") + "ip:" + QHostAddress(tcpSocket->peerAddress().toIPv4Address()).toString()
            + " port:" + QString::number(tcpSocket->peerPort());
    }

signals:
    void signalConnected();
    void signalDisConnected();
    void signalDownloadFile(const QJsonValue& json);
    void signalMsgToClient(const quint8& type, const int& reveicerID, const QJsonValue& dataVal);

private:
    QTcpSocket* tcpSocket;
    int ID;

public slots:
    //消息回发
    void sltSendMessage(const quint8& type, const QJsonValue& json);

private slots:
    void sltConnected();
    void sltDisconnected();
    void sltReadyRead();

private:
    // 消息解析和转发处理
    void parserLogin(const QJsonValue& dataVal);


};

#endif
