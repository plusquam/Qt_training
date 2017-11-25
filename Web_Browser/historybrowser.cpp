#include "historybrowser.h"
#include "ui_historybrowser.h"
#include <QDebug>

HistoryBrowser::HistoryBrowser(QWebHistory *_history, QWidget *_parent) :
    QDialog(_parent),
    ui(new Ui::HistoryBrowser),
    history(_history),
    histModel(_history)
{
    ui->setupUi(this);
    this->setWindowTitle("Browser history");

    ui->histTableView->setModel(&histModel);

    connect(ui->gotoButton, SIGNAL(clicked(bool)), this, SLOT(accept()));
    connect(ui->closeButton, SIGNAL(clicked(bool)), this, SLOT(reject()));
    connect(this, SIGNAL(doubleClicked()), this, SLOT(accept()));

    ui->histTableView->resizeColumnsToContents();
    ui->histTableView->resizeRowsToContents();

    ui->histTableView->show();
}

HistoryBrowser::~HistoryBrowser()
{
    delete ui;
}

QUrl HistoryBrowser::getChosenUrl()
{
    return this->chosenUrl;
}

void HistoryBrowser::on_histTableView_clicked(const QModelIndex &index)
{
    int rowIdx = index.row();

    this->chosenUrl = history->itemAt(history->count() - 1 - rowIdx).url();
    qDebug() << "Url: " << history->itemAt(history->count() - 1 - rowIdx).url();

    ui->histTableView->selectRow(rowIdx);
}

void HistoryBrowser::on_histTableView_doubleClicked(const QModelIndex &index)
{
    int rowIdx = index.row();

    this->chosenUrl = history->itemAt(history->count() - 1 - rowIdx).url();
    qDebug() << "Url_double: " << history->itemAt(history->count() - 1 - rowIdx).url();

    emit doubleClicked();
}
