#include "login/login.h"
#include "base_widget/MainWindow.h"
#include <QtWidgets/QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    LoginBase login;
    QQ mainwindow;
    login.show();
    QObject::connect(&login, &LoginBase::signalLoginSuccess, [&]() {
        login.close();
        mainwindow.show();
        });
    
    return app.exec();
}
