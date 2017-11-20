#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

#include <webnavigator.h>

#define HOME_PAGE google;

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
    void urlInsertedSignal(QString);

public slots:
    void urlInserted();

private:
    Ui::MainWindow *ui;
    WebNavigator *m_webNav;

};

#endif // MAINWINDOW_H
