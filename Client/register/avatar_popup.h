#ifndef AVATAR_POPUP_H
#define AVATAR_POPUP_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QImageReader>
#include <QMessageBox>

#include "../util/avatar.h"

class AvatarPopup : public QWidget
{
	Q_OBJECT

public:
	explicit AvatarPopup(QWidget* parent = nullptr)
	{
		setWindowFlags(Qt::Popup | Qt::FramelessWindowHint);
		setAttribute(Qt::WA_TranslucentBackground);
		//弹窗背景板
		QWidget* content = new QWidget(this);
		content->setFixedSize(300, 300);
		content->setObjectName("content");
		content->setStyleSheet(
			"QWidget#content{"
			"background-color:#ffffff;"
			"border-radius:15px;"
			"}"
		);
		QGridLayout* grid_layout = new QGridLayout(content);
		grid_layout->setSpacing(8);
		grid_layout->setContentsMargins(10, 10, 10, 10);
		for (int i = 0; i < 9; i++)
		{
			//弹窗内容
			Avatar* avatar = new Avatar(nullptr, ":/Image/resource/avatar" + QString::number(i) + ".png", 80, 80);
			avatar->setStyleSheet("QLabel::hover{background-color:#dcdcdc;}");
			grid_layout->addWidget(avatar, i / 3, i % 3);
			//avatar被点击发送图片路径
			connect(avatar, &Avatar::clicked, this, [=](const QString& imgPath) {
				emit avatarSelected(imgPath);
				});
		}
		QPushButton* btn_updateAvatar = new QPushButton("上传头像",content);
		btn_updateAvatar->setStyleSheet("border:none;font: 10pt Microsoft YaHei UI;color:#2d77e5;");
		btn_updateAvatar->setCursor(Qt::PointingHandCursor);
		connect(btn_updateAvatar, &QPushButton::clicked, this, &AvatarPopup::selectFile);
		grid_layout->addWidget(btn_updateAvatar, 3, 1);
	};
private:
	void selectFile() {
		QString fileName = QFileDialog::getOpenFileName(
			nullptr,
			tr("选择头像图片"),
			QString(),
			tr("图片文件 (*.png *.jpg *.jpeg *.bmp)")
		);

		if (fileName.isEmpty())
			return;

		QImageReader reader(fileName);
		if (!reader.canRead()) {
			QMessageBox::warning(this, tr("错误"), tr("请选择有效的图片文件"));
			return;
		}
		emit avatarSelected(fileName);
	}
signals:
	void avatarSelected(const QString& imgPath);
};


#endif
