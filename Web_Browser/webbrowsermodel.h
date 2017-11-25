#ifndef WEBBROWSERMODEL_H
#define WEBBROWSERMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <QWebHistory>
#include <QList>

class WebBrowserModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    WebBrowserModel(QWebHistory* _hist, QObject *_parent = 0);
    int rowCount(const QModelIndex &_parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &_parent = QModelIndex()) const;
    QVariant data(const QModelIndex &_index, int _role = Qt::DisplayRole) const;

private:
    QList<QWebHistoryItem> historyList;
};

#endif // WEBBROWSERMODEL_H
