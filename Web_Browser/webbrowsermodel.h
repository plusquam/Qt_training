/*!
  \date 25.11.2017r.
  \author Damian Świerk
  */

#ifndef WEBBROWSERMODEL_H
#define WEBBROWSERMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <QWebHistory>
#include <QList>

/*!
 * \brief Klasa WebBrowserModel
 * Model zawierający budowę tabeli z danymi o historii przeglądarki.
 */
class WebBrowserModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    WebBrowserModel(QWebHistory* _hist, QObject *_parent = 0);                          ///< Konstruktor
    int rowCount(const QModelIndex &_parent = QModelIndex()) const ;                    ///< Metoda informująca o liczbie kolumn w tabeli
    int columnCount(const QModelIndex &_parent = QModelIndex()) const;                  ///< Metoda informująca o liczbie wierszy w tabeli
    QVariant data(const QModelIndex &_index, int _role = Qt::DisplayRole) const;        ///< Metoda informująca o zawartości tabeli
    QVariant headerData(int _section, Qt::Orientation _orientation, int _role) const;   ///< Metoda informująca o nagłówkach kolumn tabeli

private:
    QList<QWebHistoryItem> historyList;     ///< Kontener przechowujący elementy historii
};

#endif // WEBBROWSERMODEL_H
