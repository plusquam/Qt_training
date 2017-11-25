#include "webbrowsermodel.h"

WebBrowserModel::WebBrowserModel(QWebHistory *_hist, QObject *_parent)
    : QAbstractTableModel(_parent),
      historyList(_hist->items())
{}

int WebBrowserModel::rowCount(const QModelIndex & /*parent*/) const
{
   return historyList.count();
}

int WebBrowserModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 3;
}

QVariant WebBrowserModel::data(const QModelIndex &_index, int _role) const
{
    if (_role == Qt::DisplayRole)
    {
        if(_index.column() == 0)
            return historyList.at(historyList.size() - _index.row() - 1).title();
        else if(_index.column() == 1)
            return historyList.at(historyList.size() - _index.row() - 1).url().toString();
        else if(_index.column() == 2)
            return historyList.at(historyList.size() - _index.row() - 1).lastVisited().toString();
    }
    return QVariant();
}

