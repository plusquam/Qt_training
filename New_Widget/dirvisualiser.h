/*!
  \date 15.11.2017r.
  \author Damian Świerk
  */

#ifndef DIRVISUALISER_H
#define DIRVISUALISER_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QPoint>
#include <QBrush>

#define DIR_SIZE_PREFIX "$S$"

/*!
 * \brief Klasa DirVisualiser
 * Klasa służy do przechowywania właściwości widgetu służącego za
 * graficzne przedstawienie danych w wybranym katalogu
 */
class DirVisualiser : public QWidget
{
    Q_OBJECT
public:
    explicit DirVisualiser(QWidget *parent = 0);            ///< Konstruktor
    void setDirMap(const QMultiMap<QString, QString> map);  ///< Metoda przypisująca wartość obiektowi m_map

private:
    QVector<qint64> m_sizeDataVect;         ///< Atrybut przechowujący rozmiary danych wyświetlanych na wykresie
    QMultiMap<QString, QString> m_map;      ///< Obiekt przechowujący mapę plików katalogu

    void drawPieDirMap(QPainter &painter);  ///< Metoda wyrysowująca mapę katalogu


    // QWidget interface
protected:
    void paintEvent(QPaintEvent *);             ///< Metoda wywoływana w chwili przerysowywania widgetu

    // QWidget interface
protected:
    void mouseDoubleClickEvent(QMouseEvent *e); ///< Metoda wywoływana w chwili podwójnego kliknięcia na widget
};

#endif // DIRVISUALISER_H
