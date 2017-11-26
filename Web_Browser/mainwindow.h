/*!
  \date 25.11.2017r.
  \author Damian Świerk
  */

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
#include "findtextdial.h"

#define HOME_PAGE "http://google.pl"    ///< Makro adresu domowego

namespace Ui {
class MainWindow;
}

/*!
 * \brief Klasa MainWindow
 * Klasa zawierająca wszystkie właściwiości i funkcje przeglądarki internetowej.
 * Ta klasa jest odpowiedzialna za działanie głównego okna przeglądarki.
 * Deklaracja obiektu klasy pozwoli na stworzenie nowego okna przeglądarki.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *_parent = 0);  ///< Konstruktor
    ~MainWindow();                              ///< Destruktor

signals:
    void refreshPage();         ///< Sygnał emitowany w celu odświeżenia strony
    void stopPageLoad();        ///< Sygnał emitowany w celu zatrzymania wczytywania strony
    void setUrlTitle(QString);  ///< Sygnał emitowany w celu zmiany wyświetlanego tytułu strony

public slots:
    void urlInserted();     ///< Slot wywoływany w chwili podania nowego adresu
    void newUrl(QUrl _url); ///< Slot zmieniający wyświetlany adres w pasku adresu

    void startPageLoad();           ///< Slot wywoływany w chwili rozpoczęcia ładowania strony
    void finishPageLoad();          ///< Slot wywoływany w chwili zakończenia ładowania strony
    void refreshClicked();          ///< Slot wywoływany w chwili wciśnięcia klawisza odświeżania
    void changeIcon();              ///< Slot wywoływany w chwili zmiany ikony strony
    void zoomChanged(int _factor);  ///< Slot wywoływany w chwili zmiany współczynnika skalowania strony

    void showContextMenu(const QPoint& _pos);   ///< Slot wyświetlający menu kontekstowe do nawigacji strony
    void displayAboutMsg();                     ///< Slot wyświetlający okno informacji o programie
    void displayZoomSettings();                 ///< Slot wyświetlający okno zmiany współczynnika skalowania strony
    void zoomDialogFinished(int _result);       ///< Slot wywoływany w chwili zatwierdzenia współczynnika

    void displayHistoryWindow();                ///< Slot wyświetlający okno historii przeglądarki
    void historyWindowFinished(int _result);    ///< Slot wywoływany w chwili zamknięcia okna historii
    void clearHistory();                        ///< Slot wykonywujący czyszczenie historii przeglądarki

    void findTextSlot(QString _text);           ///< Slot odpowiadający za wszukiwanie texu na stronie

private:
    Ui::MainWindow *ui;             ///< Wskaźnik na obiekt klasy
    bool pageLoading;               ///< Flaga przechowująca informację czy jest ładowana strona
    ZoomDialog *zoomDial;           ///< Wskaźnik na obiekt klasy okna dialogowego ZoomDialog
    HistoryBrowser *histBrowser;    ///< Wskaźnik na obiekt klasy okna historii przeglądarki
};

#endif // MAINWINDOW_H
