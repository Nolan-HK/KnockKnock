#include "server.h"
#include "database.h"
#include "clientSocket.h"
#include "tcpServer.h"

#include <QtWidgets/QApplication>
#include <QMessageBox>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    if (!DataBase::getInstance()->openDB())
    {
        QMessageBox::warning(nullptr, "错误", "数据库连接失败", QMessageBox::Ok);
        return -1;
    }

    TcpMsgServer* tcpMsgServer = new TcpMsgServer;
    bool status = tcpMsgServer->startListen();
    if (status)
        qDebug() << "开始监听";
    else
        qDebug() << "监听失败";
    Server window;
    window.show();
    return app.exec();
}
