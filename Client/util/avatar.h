#ifndef AVATAR_H
#define AVATAR_H

#include <QLabel>
#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>

class Avatar : public QLabel
{
    Q_OBJECT
public:
    explicit Avatar(QWidget* parent = nullptr, QString imgPath=":/Image/resource/default.jpg", int w = 100, int h = 100) : QLabel(parent)
    {
        setFixedSize(w, h);
        setPixmap(QPixmap(imgPath));
        m_imgPath = imgPath;
    }

public:
    void setAvatar(QString imgPath)
    {
        setPixmap(QPixmap(imgPath));
    }

    void setAvatarFromBase64(const QByteArray& data)
    {
        QByteArray imgData = QByteArray::fromBase64(data);

        QPixmap pix;
        pix.loadFromData(imgData);
        setPixmap(pix);
    }

private:
    QString m_imgPath;

signals:
    //点击获取图片路径
    void clicked(const QString& m_imgPath);

protected:
    void mousePressEvent(QMouseEvent* event) override
    {
        if (event->button() == Qt::LeftButton)
            emit clicked(m_imgPath);
    }


    void paintEvent(QPaintEvent* event) override
    {
        Q_UNUSED(event);

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        const int borderWidth = 2;   // 白边宽度

        //外圈白色边框
        painter.setBrush(Qt::white);
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(rect());

        // 内圈裁剪区域
        QRect innerRect = rect().adjusted(
            borderWidth,
            borderWidth,
            -borderWidth,
            -borderWidth
        );

        QPainterPath clipPath;
        clipPath.addEllipse(innerRect);
        painter.setClipPath(clipPath);

        //画头像
        if (!pixmap().isNull())
        {
            painter.drawPixmap(innerRect, pixmap());
        }
        else
        {
            painter.setBrush(Qt::gray);
            painter.setPen(Qt::NoPen);
            painter.drawEllipse(innerRect);
        }
    }

};



#endif

