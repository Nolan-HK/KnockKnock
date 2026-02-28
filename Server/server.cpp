#include "server.h"
#include "clientSocket.h"

#include <QDateTime>

#define window_h 512
#define window_w 980


Server::Server(QWidget *parent) : QWidget(parent)
{
	this->setGeometry(200, 200, window_w, window_h);
	InitWidget();
	
	
}

Server::~Server()
{}

QString Server::getLocalIP()
{
	QString hostName = QHostInfo::localHostName();	//本机主机名
	QHostInfo hostInfo = QHostInfo::fromName(hostName);
	QString localIP = "";
	QList<QHostAddress> addrList = hostInfo.addresses();	//本机Ip地址列表
	if (addrList.isEmpty()) return localIP;
	foreach (QHostAddress aHost, addrList)
	{
		if (QAbstractSocket::IPv4Protocol == aHost.protocol())
		{
			localIP = aHost.toString();
			break;
		}
	}
	return localIP;
}

void Server::InitWidget()
{
	textEdit = new QTextEdit(this);
	textEdit->setReadOnly(true);
	textEdit->setFont(QFont("Consolas", 12));
	textEdit->setStyleSheet(
		"QTextEdit {"
		" background-color: #000000;"
		" color: #00ff00;"
		" border: none;"
		"}"
	);
	textEdit->setCursorWidth(10);
	print("服务器已启动");


	vlayout = new QVBoxLayout;
	vlayout->addWidget(textEdit);
	vlayout->setContentsMargins(0, 0, 0, 0);
	vlayout->setSpacing(0);
	this->setLayout(vlayout);
}

void Server::print(QString Input)
{
	QString dateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
	QString s = QString("Server(%1)> %2").arg(dateTime).arg(Input);
	textEdit->append(s);
}

