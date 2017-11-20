#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *_parent) :
    QMainWindow(_parent),
    ui(new Ui::MainWindow),
    m_webNav(new WebNavigator)
{
    ui->setupUi(this);

    QUrl url = QUrl::fromUserInput("http://google.pl");

    ui->webView->load(url);
    ui->webView->show();
    ui->adressBar->setText(ui->webView->url().toString());
    qDebug() << ui->webView->url().toString();

    ui->loadProgressBar->hide();
    connect(ui->webView, SIGNAL(loadStarted()), ui->loadProgressBar, SLOT(show()));
    connect(ui->webView, SIGNAL(loadProgress(int)), ui->loadProgressBar, SLOT(setValue(int)));
    connect(ui->webView, SIGNAL(loadFinished(bool)), ui->loadProgressBar, SLOT(hide()));

    connect(ui->adressBar, SIGNAL(returnPressed()), this, SLOT(urlInserted()));
    connect(this, SIGNAL(urlInsertedSignal(QString)), ui->adressBar, SLOT(setText(QString)));
    connect(this, SIGNAL(urlInsertedSignal(QString)), m_webNav, SLOT(urlChanged(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::urlInserted()
{
    QUrl url = QUrl::fromUserInput(ui->adressBar->text());

    if(url.toString() != ui->webView->url().toString()) {
        ui->webView->load(url);
        qDebug() << ui->webView->url().toString();

        emit urlInsertedSignal(ui->webView->url().toString());
    }
}
