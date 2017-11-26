/*!
  \date 25.11.2017r.
  \author Damian Świerk
  */

#include "historybrowser.h"
#include "ui_historybrowser.h"
#include <QDebug>

/*!
 * \brief HistoryBrowser::HistoryBrowser
 * Konstruktor klasy.
 *
 * \param _history - wskaźnik na obiekt historii przeglądarki
 * \param _parent - wskaźnik na widget nadrzędny
 */
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

/*!
 * \brief HistoryBrowser::~HistoryBrowser
 * Destruktor klasy.
 */
HistoryBrowser::~HistoryBrowser()
{
    delete ui;
}

/*!
 * \brief HistoryBrowser::getChosenUrl
 * Metoda zwracająca zaznaczony adress url.
 */
QUrl HistoryBrowser::getChosenUrl()
{
    return this->chosenUrl;
}

/*!
 * \brief HistoryBrowser::on_histTableView_clicked
 * Metoda wywoływana w chwili pojednczego kliknięcia na element tabeli.
 *
 * \param index - index modelu zaznaczonego adresu
 */
void HistoryBrowser::on_histTableView_clicked(const QModelIndex &index)
{
    int rowIdx = index.row();

    this->chosenUrl = history->itemAt(history->count() - 1 - rowIdx).url();
    qDebug() << "Url: " << history->itemAt(history->count() - 1 - rowIdx).url();

    ui->histTableView->selectRow(rowIdx);
}

/*!
 * \brief HistoryBrowser::on_histTableView_doubleClicked
 * Metoda wywoływana w chwili podwójnego kliknięcia na element tabeli.
 *
 * \param index - index modelu zaznaczonego adresu
 */
void HistoryBrowser::on_histTableView_doubleClicked(const QModelIndex &index)
{
    int rowIdx = index.row();

    this->chosenUrl = history->itemAt(history->count() - 1 - rowIdx).url();
    qDebug() << "Url_double: " << history->itemAt(history->count() - 1 - rowIdx).url();

    emit doubleClicked();
}
