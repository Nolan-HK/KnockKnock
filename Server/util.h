#ifndef UTIL_H
#define UTIL_H

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>

//客户端发送的消息类型
typedef enum {
	Register = 0x10,	//注册
	RegisterResult,
	Login,				//登录
	LoginResult,
	searchUserInfo,
	returnUserInfo,
	OK,					//用于返回各查询结果的状态
	Failed,
	noFile,				//默认为Json消息
} msg_type;

QJsonObject converToJson(const QByteArray& data);

QByteArray converToByteArray(const QJsonObject& data);


#endif // !UTIL_H

