#ifndef DATABASE_H
#define DATABASE_H



#include <QObject>
#include <QSqlDataBase>

class QSqlQuery;
class QSqlError;

class DataBase : public QObject
{
	Q_OBJECT

public:
	~DataBase();

	bool openDB();
	void closeDB();
	int getUserStatus(QString userID);


public:
	QJsonObject RegisterUser(QString nickname, QString passwd, QString avatarName);	//用户注册

	QJsonObject Login(QString uid, QString passwd);
	QJsonObject getUserInfo(QString uid);
	//QJsonObject SearchUser(QString value);

	static DataBase* getInstance();

private:
	QSqlDatabase db;
	explicit DataBase(QObject* parent = nullptr);
	static DataBase* instance;
};


#endif

