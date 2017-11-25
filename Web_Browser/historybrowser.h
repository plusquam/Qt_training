#ifndef HISTORYBROWSER_H
#define HISTORYBROWSER_H

#include <QDialog>
#include <QStringList>
#include <QWebHistory>
#include <QUrl>
#include <webbrowsermodel.h>

namespace Ui {
class HistoryBrowser;
}

class HistoryBrowser : public QDialog
{
    Q_OBJECT

public:
    explicit HistoryBrowser(QWebHistory* _history ,QWidget *_parent = 0);
    ~HistoryBrowser();
    QUrl getChosenUrl();

private slots:
    void on_histTableView_clicked(const QModelIndex &index);

    void on_histTableView_doubleClicked(const QModelIndex &index);

signals:
    void doubleClicked();

private:
    Ui::HistoryBrowser *ui;
    QUrl chosenUrl;
    QWebHistory *history;
    WebBrowserModel histModel;
};

#endif // HISTORYBROWSER_H
