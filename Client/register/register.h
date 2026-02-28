#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>

class QPushButton;
class QLabel;
class QLineEdit;
class QVBoxLayout;
class Avatar;
class QGridLayout;
class AvatarPopup;
class QJsonValue;

class RegisterPage : public QDialog
{
	Q_OBJECT

public:
	explicit RegisterPage(QWidget* parent = nullptr);
	~RegisterPage();

private:

	Avatar* label_avatar;
	QPushButton* btn_chooseAvatar;
	QLineEdit* lineEdit_nickName;
	QLineEdit* lineEdit_passwd;
	QPushButton* btn_register;
	QVBoxLayout* layout_vertical;
	QPushButton* btn_showPasswd;
	AvatarPopup* avatar_popup;
	QString avatarPath;
	QLabel* label_LineEdit_1_warning;
	QLabel* label_LineEdit_2_warning;
	bool checked;
	
private:
	void InitWidget();
	void sendRegisterMsg();
	void registerResult(const QJsonObject& data);


signals:
	void signalRegister(const QJsonObject& data);

};

#endif

