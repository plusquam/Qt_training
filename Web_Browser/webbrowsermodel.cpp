/*!
  \date 25.11.2017r.
  \author Damian Świerk
  */

#include "webbrowsermodel.h"

/*!
 * \brief WebBrowserModel::WebBrowserModel
 * Konstruktor klasy.
 *
 * \param _hist - wskaźnik na obiekt historii przeglądarki
 * \param _parent - wskaźnik na widget nadrzędny
 */
WebBrowserModel::WebBrowserModel(QWebHistory *_hist, QObject *_parent)
    : QAbstractTableModel(_parent),
      historyList(_hist->items())
{}

/*!
 * \brief WebBrowserModel::rowCount
 * Metoda informująca o liczbie kolumn w tabeli.
 *
 * \param index modelu
 */
int WebBrowserModel::rowCount(const QModelIndex & /*parent*/) const
{
   return historyList.count();
}

/*!
 * \brief WebBrowserModel::columnCount
 * Metoda informująca o liczbie wierszy w tabeli.
 *
 * \param indeks modelu
 */
int WebBrowserModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 2;
}

/*!
 * \brief WebBrowserModel::data
 * Metoda informująca o zawartości tabeli.
 *
 * \param _index - indeks modelu
 * \param _role - wariant wywołania metody
 */
QVariant WebBrowserModel::data(const QModelIndex &_index, int _role) const
{
    if (_role == Qt::DisplayRole) {
        if(_index.column() == 0)
            return historyList.at(historyList.size() - _index.row() - 1).title();
        else if(_index.column() == 1)
            return historyList.at(historyList.size() - _index.row() - 1).url().toString();
    }
    return QVariant();
}

/*!
 * \brief WebBrowserModel::headerData
 * Metoda informująca o nagłówkach kolumn tabeli.
 *
 * \param _section - numer sekcji
 * \param _orientation - orientacja sekcji
 * \param _role - wariant wywołania metody
 */
QVariant WebBrowserModel::headerData(int _section, Qt::Orientation _orientation, int _role) const
{
    if (_role == Qt::DisplayRole) {
        if (_orientation == Qt::Horizontal) {
            switch (_section)
            {
            case 0:
                return QString("Title");
            case 1:
                return QString("Url");
            }
        }
    }
    return QVariant();
}

