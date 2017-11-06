#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    analyzer(new DirAnalyzer)
{
    ui->setupUi(this);

    QFileSystemModel *model = new QFileSystemModel;
    model->setRootPath(QDir::currentPath());

    ui->treeView->setModel(model);

    model->setRootPath(QString("/home"));

    ui->treeView->setRootIndex(model->index(model->rootPath()));
    ui->treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);

    qDebug() << endl << model->rootPath();

    connect(ui->actionAbout_Qt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_treeView_doubleClicked(const QModelIndex &index)
{
    qDebug()<< index << endl << index.data(QFileSystemModel::FilePathRole).toString();
    ui->statusBar->showMessage(index.data(QFileSystemModel::FilePathRole).toString());
}
