#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *_parent) :
    QMainWindow(_parent),
    ui(new Ui::MainWindow),
    pageLoading(false)
{
    ui->setupUi(this);
    this->setWindowTitle("Web Browser");

    QSettings settings ("Damian_Swierk", "Web_Browser");
    settings.beginGroup("MainWindow");
    resize(settings.value("size",QSize (700,700)).toSize());
    move(settings.value("pos",QPoint(200,200)).toPoint());

    QUrl url = QUrl::fromUserInput(settings.value("url", HOME_PAGE).toString());
    ui->webView->settings()->setIconDatabasePath(QDir::tempPath());

    ui->loadProgressBar->hide();

    connect(ui->webView, SIGNAL(loadStarted()), ui->loadProgressBar, SLOT(show()));
    connect(ui->webView, SIGNAL(loadStarted()), this, SLOT(startPageLoad()));

    connect(ui->webView, SIGNAL(loadProgress(int)), ui->loadProgressBar, SLOT(setValue(int)));

    connect(ui->webView, SIGNAL(loadFinished(bool)), ui->loadProgressBar, SLOT(hide()));
    connect(ui->webView, SIGNAL(loadFinished(bool)), this, SLOT(finishPageLoad()));
    connect(this, SIGNAL(setUrlTitle(QString)), ui->titleLabel, SLOT(setText(QString)));
    connect(ui->webView, SIGNAL(urlChanged(QUrl)), this, SLOT(newUrl(QUrl)));
    connect(ui->webView, SIGNAL(iconChanged()), this, SLOT(changeIcon()));

    connect(ui->adressBar, SIGNAL(returnPressed()), this, SLOT(urlInserted()));

    connect(ui->pageBackButton, SIGNAL(clicked(bool)), ui->webView, SLOT(back()));
    connect(ui->pageNextButton, SIGNAL(clicked(bool)), ui->webView, SLOT(forward()));

    connect(ui->refreshButton, SIGNAL(clicked(bool)), this, SLOT(refreshClicked()));
    connect(this, SIGNAL(stopPageLoad()), ui->webView, SLOT(stop()));
    connect(this, SIGNAL(refreshPage()), ui->webView, SLOT(reload()));

    connect(ui->zoomSlider, SIGNAL(valueChanged(int)), this, SLOT(zoomChanged(int)));

    connect(ui->actionAbout_Qt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(displayAboutMsg()));

    connect(ui->webView->page(), SIGNAL(linkHovered(QString,QString,QString)),
            ui->statusBar, SLOT(showMessage(QString)));

    connect(ui->actionZoom, SIGNAL(triggered()), this, SLOT(displayZoomSettings()));
    connect(ui->actionHistory, SIGNAL(triggered()), this, SLOT(displayHistoryWindow()));

    ui->zoomSlider->setValue(settings.value("zoom", 100).toInt());
    settings.endGroup();


    this->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(showContextMenu(const QPoint &)));


    ui->webView->load(url);
    ui->webView->show();
    ui->adressBar->setText(ui->webView->url().toString());
}

MainWindow::~MainWindow()
{
    QSettings settings ("Damian_Swierk", "Web_Browser");
    settings.beginGroup("MainWindow");
    settings.setValue("size", size());
    settings.setValue("pos", pos());
    settings.setValue("url", ui->webView->url().toString());
    settings.setValue("zoom", ui->zoomSlider->value());
    settings.endGroup();

    delete ui;
    delete zoomDial;
}

void MainWindow::urlInserted()
{
    QUrl url = QUrl::fromUserInput(ui->adressBar->text());

    if(url.toString() != ui->webView->url().toString())
        ui->webView->load(url);
}

void MainWindow::newUrl(QUrl _url)
{
    if(_url.toString() != "")
        ui->adressBar->setText(_url.toString());

    qDebug() << ui->webView->url().toString();
    qDebug() << QDateTime::currentDateTime().toString();
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

    if(ui->webView->history()->canGoBack())
        ui->pageBackButton->setEnabled(true);
    else
        ui->pageBackButton->setEnabled(false);

    if(ui->webView->history()->canGoForward())
        ui->pageNextButton->setEnabled(true);
    else
        ui->pageNextButton->setEnabled(false);

    emit setUrlTitle(ui->webView->title());

    qDebug() << ui->webView->title();
}

void MainWindow::refreshClicked()
{
    if(this->pageLoading)
        emit stopPageLoad();
    else
        emit refreshPage();
}

void MainWindow::changeIcon()
{
    ui->pageIcon->setIcon(ui->webView->icon());
    qDebug() << "Icon changed";
}

void MainWindow::zoomChanged(int _factor)
{
    ui->webView->setZoomFactor((qreal)((double)_factor/100.));
    ui->zoomValueLabel->setText(QString::number(_factor) + "%");
}

void MainWindow::showContextMenu(const QPoint &_pos)
{
    QMenu contextMenu(tr("Navigation menu"), this);

    QAction backAction("Go Back", this);
    QAction forwardAction("Go Forward", this);
    QAction refreshAction("Reload/Stop", this);

    connect(&refreshAction, SIGNAL(triggered()), this, SLOT(refreshClicked()));
    contextMenu.addAction(&refreshAction);

    connect(&backAction, SIGNAL(triggered()), ui->webView, SLOT(back()));
    contextMenu.addAction(&backAction);

    connect(&forwardAction, SIGNAL(triggered()), ui->webView, SLOT(forward()));
    contextMenu.addAction(&forwardAction);

    contextMenu.exec(mapToGlobal(_pos));
}

void MainWindow::displayAboutMsg()
{
    QMessageBox::about(this, "Web Browser", "Jest to program realizujący funkcjonalności przeglądarki internetowej.\n\n"
                                            "Autor: Damian Świerk");
}

void MainWindow::displayZoomSettings()
{
    zoomDial = new ZoomDialog(ui->zoomSlider->value(), this);
    zoomDial->show();

    connect(zoomDial, SIGNAL(finished (int)), this, SLOT(zoomDialogFinished(int)));
}

void MainWindow::zoomDialogFinished(int _result)
{
    if(_result == QDialog::Accepted)
        ui->zoomSlider->setValue(zoomDial->value());

    delete zoomDial;
}

void MainWindow::displayHistoryWindow()
{
    histBrowser = new HistoryBrowser(ui->webView->history(), this);
    histBrowser->show();

    connect(histBrowser, SIGNAL(finished (int)), this, SLOT(historyWindowFinished(int)));
    connect(histBrowser, SIGNAL(finished (int)), histBrowser, SLOT(deleteLater()));
}

void MainWindow::historyWindowFinished(int _result)
{
    if(_result == QDialog::Accepted)
        ui->webView->load(histBrowser->getChosenUrl());
}



