#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QWebView>
#include <QWebHistory>
#include <QSettings>
#include <QMessageBox>
#include <QVector>
#include <QDir>

#include "zoomdialog.h"
#include "historybrowser.h"

#define HOME_PAGE "http://google.pl"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *_parent = 0);
    ~MainWindow();

signals:
    void refreshPage();
    void stopPageLoad();
    void setUrlTitle(QString);

public slots:
    void urlInserted();
    void newUrl(QUrl _url);

    void startPageLoad();
    void finishPageLoad();
    void refreshClicked();
    void changeIcon();

    void zoomChanged(int _factor);

    void showContextMenu(const QPoint& _pos);

    void displayAboutMsg();
    void displayZoomSettings();
    void zoomDialogFinished(int _result);

    void displayHistoryWindow();
    void historyWindowFinished(int _result);

private:
    Ui::MainWindow *ui;
    bool pageLoading;
    ZoomDialog *zoomDial;
    HistoryBrowser *histBrowser;
};

#endif // MAINWINDOW_H
