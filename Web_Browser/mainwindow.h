#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QWebView>
#include <QWebHistory>


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

public slots:
    void urlInserted();
    void refreshUrlBar(QUrl _url);

    void startPageLoad();
    void finishPageLoad();

    void refreshClicked();

    void zoomChanged(int _factor);

private:
    Ui::MainWindow *ui;
    bool pageLoading;

};

#endif // MAINWINDOW_H
