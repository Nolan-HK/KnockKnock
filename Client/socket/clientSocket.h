#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QObject>

class QHostAddress;
class QTcpSocket;

class ClientSocket : public QObject
{
	Q_OBJECT
public:
	explicit ClientSocket(QObject* parent = nullptr);
	~ClientSocket();

    void setUserID(const int& uid);
    int getUserID() const;

	void checkConnected();
	void closeConnected();

	//连接服务器
	void connectedToHost(const QString& host, const int& port);
	void connectedToHost(const QHostAddress& host, const int& port);


signals:
    void signalMessage(const quint8& type, const QJsonValue& dataVal);
    //void signalStatus(const quint8& state);
    //void signalRegisterOk(const QJsonValue& dataVal);
    //void signalChangePwdReply(const QJsonValue& dataVal);
    //void signalFindFriendReply(const QJsonValue& dataVal);
    //void signalGetOfflineMsg(const QJsonValue& dataVal);

public slots:
    // socket消息发送封装
    void sltSendMessage(const quint8& type, const QJsonValue& dataVal);
    // 发送上线通知
    //void sltSendOnline();
    // 发送下线通知
    //void sltSendOffline();

private slots:
    // 与服务器断开链接
    void sltDisconnected();
    // 链接上服务器
    void sltConnected();
    // tcp消息处理
    void sltReadyRead();


private:
    // tcpsocket
    QTcpSocket* tcpSocket;
    int ID;

private:
    // 解析登陆返回信息
    void parseLogin(const QJsonValue& dataVal);
    // 解析注册返回信息
    void parseReister(const QJsonValue& dataVal);
};


#endif // !CLIENTSOCKET_H