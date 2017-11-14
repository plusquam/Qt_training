#ifndef DIRVISUALISER_H
#define DIRVISUALISER_H

#include <QWidget>
#include <QPainter>

class DirVisualiser : public QWidget
{
    Q_OBJECT
public:
    explicit DirVisualiser(QWidget *parent = 0);

signals:

public slots:

private:
    QVector<qint64> m_sizeDataVect;


    // QWidget interface
protected:
    void paintEvent(QPaintEvent *);

    // QWidget interface
protected:
    void mouseDoubleClickEvent(QMouseEvent *e);
};

#endif // DIRVISUALISER_H
