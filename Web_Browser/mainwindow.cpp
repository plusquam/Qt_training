#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *_parent) :
    QMainWindow(_parent),
    ui(new Ui::MainWindow),
    pageLoading(false)
{
    ui->setupUi(this);

    QUrl url = QUrl::fromUserInput(HOME_PAGE);

    ui->loadProgressBar->hide();
    ui->zoomSlider->setValue(100);

    connect(ui->webView, SIGNAL(loadStarted()), ui->loadProgressBar, SLOT(show()));
    connect(ui->webView, SIGNAL(loadStarted()), this, SLOT(startPageLoad()));

    connect(ui->webView, SIGNAL(urlChanged(QUrl)), this, SLOT(refreshUrlBar(QUrl)));
    connect(ui->webView, SIGNAL(loadProgress(int)), ui->loadProgressBar, SLOT(setValue(int)));

    connect(ui->webView, SIGNAL(loadFinished(bool)), ui->loadProgressBar, SLOT(hide()));
    connect(ui->webView, SIGNAL(loadFinished(bool)), this, SLOT(finishPageLoad()));

    connect(ui->adressBar, SIGNAL(returnPressed()), this, SLOT(urlInserted()));

    connect(ui->pageBackButton, SIGNAL(clicked(bool)), ui->webView, SLOT(back()));
    connect(ui->pageNextButton, SIGNAL(clicked(bool)), ui->webView, SLOT(forward()));

    connect(ui->refreshButton, SIGNAL(clicked(bool)), this, SLOT(refreshClicked()));
    connect(this, SIGNAL(stopPageLoad()), ui->webView, SLOT(stop()));
    connect(this, SIGNAL(refreshPage()), ui->webView, SLOT(reload()));

    connect(ui->zoomSlider, SIGNAL(valueChanged(int)), this, SLOT(zoomChanged(int)));

    ui->webView->load(url);
    ui->webView->show();
    ui->adressBar->setText(ui->webView->url().toString());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::urlInserted()
{
    QUrl url = QUrl::fromUserInput(ui->adressBar->text());

    if(url.toString() != ui->webView->url().toString())
        ui->webView->load(url);
}

void MainWindow::refreshUrlBar(QUrl _url)
{
    if(_url.toString() != "")
        ui->adressBar->setText(_url.toString());

    qDebug() << _url.toString();
}

void MainWindow::startPageLoad()
{
    this->pageLoading = true;
    ui->refreshButton->setText("X");
}

void MainWindow::finishPageLoad()
{
    this->pageLoading = false;
    ui->refreshButton->setText("R");
}

void MainWindow::refreshClicked()
{
    if(this->pageLoading)
        emit stopPageLoad();
    else
        emit refreshPage();
}

void MainWindow::zoomChanged(int _factor)
{
    ui->webView->setZoomFactor((qreal)((double)_factor/100.));
    ui->zoomValueLabel->setText(QString::number(_factor) + "%");
}


