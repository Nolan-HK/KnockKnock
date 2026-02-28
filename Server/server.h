#ifndef SERVER_H
#define SERVER_H
//#include "tcpServer.h"

#include <QtWidgets/QWidget>
#include <QTcpServer>
#include <QHostInfo>
#include <QTextEdit>
#include <QVBoxLayout>


class Server : public QWidget
{
    Q_OBJECT

public:
    Server(QWidget *parent = nullptr);
    ~Server();

    QString getLocalIP();


private:
    QTcpServer server;
    //TcpServer tcpServer;

//widget
private:
    QTextEdit* textEdit;
    QVBoxLayout* vlayout;

//function
private:
    void InitWidget();
    void print(QString Input);

};


#endif