#include "dirvisualiser.h"
#include <QDebug>
#include <QMouseEvent>
#include <QPoint>
#include <QBrush>

DirVisualiser::DirVisualiser(QWidget *parent) :
    QWidget(parent)
{
    m_sizeDataVect << 2 << 13 << 12 << 55;
}

void DirVisualiser::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(Qt::blue);
    painter.setFont(QFont("Arial", 30));
    painter.drawText(rect(), Qt::AlignLeft, "Qt");

    QRect rect(0, 0, this->width()-1, this->height()-1);
    painter.drawRect(rect);
    if(rect.width() > rect.height())
        rect = QRect(rect.width()/2-rect.height()/2, 0, rect.height()-1, rect.height()-1);
    else
        rect = QRect(rect.width()/2-rect.height()/2, 0, rect.height()-1, rect.height()-1);

        painter.drawEllipse(rect);

        qint64 _sizeSum = 0;

        foreach(qint64 _size, m_sizeDataVect)
        {
            qDebug() << _size;
            _sizeSum += _size;
        }
        qDebug() << _sizeSum;

        QBrush _brush(Qt::SolidPattern);
        int _iter = 0;
        qint64 _actualAngle = 0;

        foreach(qint64 _size, m_sizeDataVect)
        {

        _brush.setColor(QColor(1*_iter/m_sizeDataVect.size()*255,
                               1*_iter/m_sizeDataVect.size()*255,
                               1*_iter/m_sizeDataVect.size()*255));

        painter.setBrush(_brush);
        painter.drawPie(rect, _actualAngle, _size * 16 * 360 / _sizeSum);
        _actualAngle += _size * 16 * 360 / _sizeSum;
        }
}

void DirVisualiser::mouseDoubleClickEvent(QMouseEvent *e)
{
    qDebug() << e->localPos();
    QPainter painter(this);
    painter.drawRect(e->localPos().x(), e->localPos().y(), 10, 10);
}
