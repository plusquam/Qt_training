/*!
  \date 25.11.2017r.
  \author Damian Świerk
  */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

/*!
 * \brief MainWindow::MainWindow
 * Konstruktor klasy. W tej metodzie łączone są wszystkie sygnały i sloty potrzebne do działania programu.
 * W tej metodzie również są wczytywane i ustawiane wszystkie parametry aplikacji.
 *
 * \param _parent - wskaźnik na widget nadrzędny
 */
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
    ui->findTextWidget->hide();

    /// Łączenie sygnałów i slotów dla obsługi wprowadzania adresu i kontroli stanu ładowania strony ///

    connect(ui->webView, SIGNAL(loadStarted()), ui->loadProgressBar, SLOT(show()));
    connect(ui->webView, SIGNAL(loadStarted()), this, SLOT(startPageLoad()));
    connect(ui->webView, SIGNAL(loadProgress(int)), ui->loadProgressBar, SLOT(setValue(int)));
    connect(ui->webView, SIGNAL(loadFinished(bool)), ui->loadProgressBar, SLOT(hide()));
    connect(ui->webView, SIGNAL(loadFinished(bool)), this, SLOT(finishPageLoad()));
    connect(this, SIGNAL(setUrlTitle(QString)), ui->titleLabel, SLOT(setText(QString)));
    connect(ui->webView, SIGNAL(urlChanged(QUrl)), this, SLOT(newUrl(QUrl)));
    connect(ui->webView, SIGNAL(iconChanged()), this, SLOT(changeIcon()));
    connect(ui->adressBar, SIGNAL(returnPressed()), this, SLOT(urlInserted()));

    /// Łączenie sygnałów i slotów dla obsługi klawiszy i suwaka głównego okna ///

    connect(ui->pageBackButton, SIGNAL(clicked(bool)), ui->webView, SLOT(back()));
    connect(ui->pageNextButton, SIGNAL(clicked(bool)), ui->webView, SLOT(forward()));
    connect(ui->refreshButton, SIGNAL(clicked(bool)), this, SLOT(refreshClicked()));
    connect(this, SIGNAL(stopPageLoad()), ui->webView, SLOT(stop()));
    connect(this, SIGNAL(refreshPage()), ui->webView, SLOT(reload()));
    connect(ui->zoomSlider, SIGNAL(valueChanged(int)), this, SLOT(zoomChanged(int)));

    /// Łączenie sygnałów i slotów wyświetlania pomocy ///

    connect(ui->actionAbout_Qt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(displayAboutMsg()));

    /// Łączenie sygnału i slotu wyświetlania linku w pasku statusowym ///

    connect(ui->webView->page(), SIGNAL(linkHovered(QString,QString,QString)),
            ui->statusBar, SLOT(showMessage(QString)));

    /// Łączenie sygnałów i slotów dla funkcji w menu ///

    connect(ui->actionZoom, SIGNAL(triggered()), this, SLOT(displayZoomSettings()));
    connect(ui->actionHistory, SIGNAL(triggered()), this, SLOT(displayHistoryWindow()));
    connect(ui->actionClear_History, SIGNAL(triggered()), this, SLOT(clearHistory()));

    /// Łączenie sygnał i slotu dla wyszukiwania tekstu ///

    connect(ui->findTextWidget, SIGNAL(sendText(QString)), this, SLOT(findTextSlot(QString)));


    ui->zoomSlider->setValue(settings.value("zoom", 100).toInt());
    settings.endGroup();

    this->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(showContextMenu(const QPoint &)));

    ui->webView->load(url);
    ui->webView->show();
    ui->adressBar->setText(ui->webView->url().toString());
}

/*!
 * \brief MainWindow::~MainWindow
 * Destruktor klasy.
 * W tej metodzie również są wczytywane i ustawiane wszystkie parametry aplikacji.
 */
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

/*!
 * \brief MainWindow::urlInserted
 * Metoda wczytująca podany w pasku adres url.
 */
void MainWindow::urlInserted()
{
    QUrl url = QUrl::fromUserInput(ui->adressBar->text());

    if(url.toString() != ui->webView->url().toString())
        ui->webView->load(url);
}

/*!
 * \brief MainWindow::newUrl
 * Metoda odświeżająca wyświetlany adres w pasku url.
 *
 * \param _url - wskaźnik na widget nadrzędny
 */
void MainWindow::newUrl(QUrl _url)
{
    if(_url.toString() != "")
        ui->adressBar->setText(_url.toString());

    qDebug() << ui->webView->url().toString();
    qDebug() << QDateTime::currentDateTime().toString();
}

/*!
 * \brief MainWindow::startPageLoad
 * Metoda wywoływana w chwili rozpoczęcia ładowania strony.
 */
void MainWindow::startPageLoad()
{
    this->pageLoading = true;
    ui->refreshButton->setText("X");
}

/*!
 * \brief MainWindow::finishPageLoad
 * Metoda wywoływana w chwili zakończenia ładowania strony.
 */
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

/*!
 * \brief MainWindow::refreshClicked
 * Metoda wywoływana w chwili wciśnięcia klawisza odświeżania strony.
 */
void MainWindow::refreshClicked()
{
    if(this->pageLoading)
        emit stopPageLoad();
    else
        emit refreshPage();
}

/*!
 * \brief MainWindow::changeIcon
 * Metoda wywoływana w chwili zmiany ikony strony.
 */
void MainWindow::changeIcon()
{
    ui->pageIcon->setIcon(ui->webView->icon());
    qDebug() << "Icon changed";
}

/*!
 * \brief MainWindow::zoomChanged
 * Metoda wywoływana w chwili zmiany wartości współczynnika skalowania strony.
 *
 * \param _factor - wartość współczynnika
 */
void MainWindow::zoomChanged(int _factor)
{
    ui->webView->setZoomFactor((qreal)((double)_factor/100.));
    ui->zoomValueLabel->setText(QString::number(_factor) + "%");
}

/*!
 * \brief MainWindow::showContextMenu
 * Metoda wyświetlająca menu kontekstowe nawigacji strony.
 *
 * \param _pos - lokalizacja kursora
 */
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

/*!
 * \brief MainWindow::displayAboutMsg
 * Metoda wyświetlająca okno informacji o programie.
 */
void MainWindow::displayAboutMsg()
{
    QMessageBox::about(this, "Web Browser", "Jest to program realizujący funkcjonalności przeglądarki internetowej takie jak:\n\n"
                                            "* Wyświetlanie stron www o zadanym adresie,\n"
                       "* Miejsce do wpisywania adresu strony z automatycznym dodawaniem brakujących informacji\n"
                       "  (np. protokołu 'http:\\') oraz wyświetlaniem adresu załadowanej strony np. po kliknięciu odnośnika,\n"
                       "* Reagowanie na nawigację przy pomocy myszki (np. przechodzenie do klikniętych odnośników),\n"
                       "* Podgląd adresu odnośnika na pasku statusu po najechaniu myszką nad odnośnik,\n"
                       "* Nawigacja po odwiedzonych stronach przy pomocy klawiszy poprzednia/następna strona,\n"
                       "* Menu kontekstowe do nawigacji,\n"
                       "* Zapamiętywanie historii odwiedzanych stron, prezentacja w kontrolce graficznej i w menu np. Historia,\n"
                       "* Wyszukiwanie tekstu w zawartości strony,\n"
                       "* Informowanie o postępie w ładowaniu strony (ang. progress bar),\n"
                       "* Zoom - skalowanie zawartości strony www,\n"
                       "* Zaimplementowane funkcjonalności powinny się pojawić w menu,\n"
                       "* Program powinien wykorzystywać ikonki, podpowiedzi oraz okienko 'O programie...' w celu ułatwienia obsługi,\n"
                       "* Przeglądarka powinna zapisywać swój stan (np. rozmiar i pozycję okna, ostatnio przeglądaną stronę itp.).\n\n\n"
                                            "Autor: Damian Świerk");
}

/*!
 * \brief MainWindow::displayZoomSettings
 * Metoda wyświetlająca okno zmiany współczynnika skalowania strony.
 */
void MainWindow::displayZoomSettings()
{
    zoomDial = new ZoomDialog(ui->zoomSlider->value(), this);
    zoomDial->show();

    connect(zoomDial, SIGNAL(finished (int)), this, SLOT(zoomDialogFinished(int)));
}

/*!
 * \brief MainWindow::zoomDialogFinished
 * Metoda wywoływana w chwili zamknięcia okna zmiany współczynnika skalowania strony.
 *
 * \param _result - rezultat zamknięcia strony.
 */
void MainWindow::zoomDialogFinished(int _result)
{
    if(_result == QDialog::Accepted)
        ui->zoomSlider->setValue(zoomDial->value());

    delete zoomDial;
}

/*!
 * \brief MainWindow::displayHistoryWindow
 * Metoda wyświetlająca okno historii przeglądarki.
 */
void MainWindow::displayHistoryWindow()
{
    histBrowser = new HistoryBrowser(ui->webView->history(), this);
    histBrowser->show();

    connect(histBrowser, SIGNAL(finished (int)), this, SLOT(historyWindowFinished(int)));
    connect(histBrowser, SIGNAL(finished (int)), histBrowser, SLOT(deleteLater()));
}

/*!
 * \brief MainWindow::historyWindowFinished
 * Metoda wywoływana w chwili zamknięcia okna historii przeglądarki.
 *
 * \param _result - rezultat zamknięcia strony.
 */
void MainWindow::historyWindowFinished(int _result)
{
    if(_result == QDialog::Accepted)
        ui->webView->load(histBrowser->getChosenUrl());
}

/*!
 * \brief MainWindow::clearHistory
 * Metoda czyszcząca historię przeglądaki.
 */
void MainWindow::clearHistory()
{
    ui->webView->history()->clear();
}

/*!
 * \brief MainWindow::findTextSlot
 * Metoda wywołująca wyszukiwanie podanego tekstu w zawartośći strony.
 *
 * \param _text - szukana fraza.
 */
void MainWindow::findTextSlot(QString _text)
{
    ui->webView->findText(_text, QWebPage::HighlightAllOccurrences);
}



