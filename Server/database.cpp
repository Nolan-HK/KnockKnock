#include "database.h"
#include "util.h"

#include <QMessageBox>
#include <QMutex>
#include <QSqlQuery>
#include <QSqlError>

DataBase::DataBase(QObject* parent)
{
	
}

DataBase* DataBase::instance = nullptr;
DataBase* DataBase::getInstance()
{
	static QMutex mutex;
	if (instance == nullptr)
	{
		QMutexLocker locker(&mutex);

		if (!instance)
			instance = new DataBase;
	}
	return instance;
}

DataBase::~DataBase()
{
	if (db.isOpen())
		db.close();
}

bool DataBase::openDB()
{
	db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName("localhost");
	db.setPort(3306);
	db.setDatabaseName("server_for_qq9.9");
	db.setUserName("root");
	db.setPassword("123456");


	if (!db.open())
	{
		qDebug() << "连接失败：" << db.lastError().text();
		return false;
	}
	qDebug() << "数据库连接成功";
	return true;
}

void DataBase::closeDB()
{
	db.close();
}

int DataBase::getUserStatus(QString userID)
{
	QSqlQuery query;
	query.prepare("select status from contacts where uid=?");
	query.bindValue(0, userID);
	query.exec();
	if (query.next())
	{
		return query.value("status").toInt();
	}
	else
	{
		qDebug() << "查询失败：" << query.lastError().text();
		return -1;
	}
}

QJsonObject DataBase::RegisterUser(QString nickname, QString passwd, QString avatarName)
{
	QSqlQuery query;
	QString id;
	query.prepare("INSERT INTO userInfo (password, nickname, avatar) VALUES (:password, :nickname, :avatarName)");
	query.bindValue(":nickname", nickname);
	query.bindValue(":password", passwd);
	query.bindValue(":avatarName", avatarName);

	QJsonObject json;
	if (query.exec())
	{
		//插入成功后，获取自增主键UID
		QVariant lastId = query.lastInsertId();
		QString id = lastId.toString();

		json.insert("type", RegisterResult);
		json.insert("status", OK);
		json.insert("uid", id);
		qDebug() << "注册成功，用户 ID:" << id;
		return json;
	}
	else
	{
		qDebug() << "注册失败：" << query.lastError().text();
		json.insert("type", RegisterResult);
		json.insert("status", Failed);
		json.insert("msg", query.lastError().text());
		return json;
	}
}

QJsonObject DataBase::Login(QString uid, QString passwd)
{
	QSqlQuery query;
	query.prepare("SELECT uid, password FROM userInfo WHERE uid = :uid AND password = :password");
	query.bindValue(":uid", uid);
	query.bindValue(":password", passwd);
	query.exec();
	QJsonObject json;
	if (query.next())
	{
		
		json.insert("type", LoginResult);
		json.insert("status", OK);
		return json;
	}
	else
	{
		json.insert("type", LoginResult);
		json.insert("status", Failed);
		json.insert("msg", "账号或密码不正确");
		return json;
	}
}

QJsonObject DataBase::getUserInfo(QString uid)
{
	QSqlQuery query;
	query.prepare("SELECT uid,nickname,avatar FROM userInfo WHERE uid = :uid");
	query.bindValue(":uid", uid);
	query.exec();
	QJsonObject json;
	if (query.next())
	{
		QString uid = query.value("uid").toString();
		QString nickname = query.value("nickname").toString();
		QString avatar = query.value("avatar").toString();
		json.insert("type", returnUserInfo);
		json.insert("status", OK);
		json.insert("uid", uid);
		json.insert("nickname", nickname);
		json.insert("avatarName", avatar);
		return json;
	}
	else
	{
		json.insert("type", returnUserInfo);
		json.insert("status", Failed);
	}
	return QJsonObject();
}


//QJsonObject DataBase::SearchUser(QString value)
//{
//	QSqlQuery query;
//	query.prepare("SELECT avatar, nickname, uid FROM userInfo WHERE nickname LIKE :key OR uid LICK :key");
//	value = "%" + value + "%";
//	query.bindValue(":key", value);
//	query.exec();
//	QJsonObject json;
//	if (query.next())
//	{
//		
//	}
//	return QJsonObject();
//}
