/*!
  \date 25.11.2017r.
  \author Damian Świerk
  */

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

/*!
 * \brief Klasa HistoryBrowser
 * Klasa zawierająca funkcjonalności okna przeglądania historii przeglądarki.
 */
class HistoryBrowser : public QDialog
{
    Q_OBJECT

public:
    explicit HistoryBrowser(QWebHistory* _history ,QWidget *_parent = 0);   ///< Konstruktor
    ~HistoryBrowser();                                                      ///< Destruktor
    QUrl getChosenUrl();                                                    ///< Getter zwracający zaznaczony w oknie adress url

private slots:
    void on_histTableView_clicked(const QModelIndex &index);        ///< Slot wywoływany w chwili kliknięcia na element w tabeli
    void on_histTableView_doubleClicked(const QModelIndex &index);  ///< Slot wywoływany w chwili podwójnego kliknięcia na element w tabeli

signals:
    void doubleClicked();   ///< Sygnał wywoływany po podwójnym wciśnięciu na element w tabeli

private:
    Ui::HistoryBrowser *ui;     ///< Obiekt tej klasy
    QUrl chosenUrl;             ///< Atrybut przechowujący zaznaczony adress url
    QWebHistory *history;       ///< Wskaźnik na obiekt historii przeglądarki
    WebBrowserModel histModel;  ///< Model przechowujący elementy historii przeglądarki
};

#endif // HISTORYBROWSER_H
