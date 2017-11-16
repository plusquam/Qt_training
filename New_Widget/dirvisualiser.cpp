#include "dirvisualiser.h"
#include <QDebug>

/*!
 * \brief DirVisualiser::DirVisualiser
 * Konstruktor klasy.
 *
 * \param parent - wskaźnik na widget nadrzędny
 */
DirVisualiser::DirVisualiser(QWidget *parent) :
    QWidget(parent)
{
    m_sizeDataVect << 2 << 13 << 12 << 55 << 100 << 20;
}

/*!
 * \brief DirVisualiser::setDirMap
 * Metoda ustawia właściwości atrybutu m_map.
 *
 * \param map - mapa wybranego katalogu
 */
void DirVisualiser::setDirMap(const QMultiMap<QString, QString> map)
{
    this->m_map = map;
}

/*!
 * \brief DirVisualiser::drawPieDirMap
 * Metoda służąca do rysowania graficznego przedstawienia zawartości katalogu
 * w formie wycinków koła.
 *
 * \param painter - obiekt klasy QPainter służący do rysowania graficznego
 * przedstawienia zawartości katalogu.
 */
void DirVisualiser::drawPieDirMap(QPainter &painter)
{
    int _windowWidth = this->width()-20, _windowHeight = this->height()-20;

    qint64 _totalSize;

    foreach(QString _value, m_map.values("~"))
        if(_value.contains(DIR_SIZE_PREFIX))
        {
            _value.remove(DIR_SIZE_PREFIX);
            _totalSize = _value.toLongLong();
            break;
        }
    qDebug() << _totalSize;

    QVector< QVector<QString> > _dirs;
    QVector< QVector<qint64> > _sizes;
    int _maxRow = 0;

    // Wyznaczanie sekwencji rysowania bloczków


    QMapIterator<QString, QString> _iter(m_map);

    while (_iter.hasNext())
    {
        _iter.next();

        if(_iter.key().count("/") > _maxRow)
           _maxRow = _iter.key().count("/");
    }
    qDebug() << "maxRows " << _maxRow;

    QVector<int> _cols;

    for(int _r = 0; _r <= _maxRow; _r++ )
    {
        _cols.push_back(0);

        while (_iter.hasNext())
        {
            _iter.next();

            if(_iter.key().count("/") == _r)
                if(!_iter.key().contains("DIR_SIZE_PREFIX"))
                    _cols[_r]++;
        }
        _iter.toFront();
    }
    qDebug() << "cols " << _cols;

    int _row = 0, _col = 0;

    for(int _r = 0; _r <= _maxRow; _r++)
        for(int _c = 0; _c <= _cols[_r]; _c++)
        {
            while (_iter.hasNext())
            {
                _iter.next();
                QString _dirName = _iter.key();
                QString _subDirName = _iter.value();

                _row = _dirName.count("/");
            }
        }


}

/*!
 * \brief DirVisualiser::paintEvent
 * Metoda odpowiadajaca za przerysowywanie kontrolki.
 *
 * \param * - wskaźnik na wydarzenie QPaintEvent
 */
void DirVisualiser::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setPen(Qt::blue);
    painter.setFont(QFont("Arial", 16));
    painter.drawText(rect(), Qt::AlignLeft, "Directory visualisation");

    QRect rect(0, 0, this->width()-1, this->height()-1);

    if(rect.width() > rect.height())
        rect = QRect(rect.width()/2-rect.height()/2, 0, rect.height()-1, rect.height()-1);
    else
        rect = QRect(rect.width()/2-rect.height()/2, 0, rect.height()-1, rect.height()-1);

    qint64 _sizeSum = 0;

    foreach(qint64 _size, m_sizeDataVect)
    {
        qDebug() << _size;
        _sizeSum += _size;
    }
    qDebug() << _sizeSum;

    QBrush _brush(Qt::SolidPattern);
    int _iter = 1;
    qint64 _actualAngle = 0;

    foreach(qint64 _size, m_sizeDataVect)
    {

        _brush.setColor(QColor(_iter*255/m_sizeDataVect.size(),
                               _iter*255/m_sizeDataVect.size(),
                               _iter*255/m_sizeDataVect.size()));

        painter.setBrush(_brush);
        painter.drawPie(rect, _actualAngle, _size * 16 * 360 / _sizeSum);
        _actualAngle += _size * 16 * 360 / _sizeSum;
        _iter++;
    }
}

/*!
 * \brief DirVisualiser::mouseDoubleClickEvent
 * Metoda odpowiadajaca za wykonanie działań po podwójnym kliknięciu myszy na kontrolce.
 *
 * \param *e - wskaźnik na wydarzenie QMouseEvent
 */
void DirVisualiser::mouseDoubleClickEvent(QMouseEvent *e)
{
    qDebug() << e->localPos();
    QPainter painter(this);
    painter.drawRect(e->localPos().x(), e->localPos().y(), 10, 10);

    drawPieDirMap(painter);
}
