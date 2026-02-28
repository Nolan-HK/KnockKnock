#ifndef TITLE_H
#define TITLE_H

#include <QLabel>
#include <QPainter>


class Title : public QLabel
{
    Q_OBJECT
public:
    using QLabel::QLabel;

protected:
    void paintEvent(QPaintEvent*) override
    {
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);

        QLinearGradient g(0, 0, width(), 0);
        g.setColorAt(0.0, QColor("#7fe0ff"));
        g.setColorAt(0.5, QColor("#90b7ff"));
        g.setColorAt(1.0, QColor("#dcaaff"));


        QPen pen(QBrush(g), 3);
        p.setPen(pen);
        p.setFont(font());
        p.drawText(rect(), alignment(), text());
    }
};


#endif // !TITLE_H

