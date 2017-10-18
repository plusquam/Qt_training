#include "mainwindow.h"
#include "ui_mainwindow.h"

/*!
 * \brief MainWindow::MainWindow - konstruktor klasy
 * \param parent - wskaźnik na obiek nadrzędny
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    converter(new TempConverter(0, this))
{
    ui->setupUi(this);

    /*!
     * wywoływania metod aktywowane w chwili zmiany wartości widgetów Dial
     */
    connect(ui->dialCelsius, SIGNAL(valueChanged(int)), converter, SLOT(celsiusDialChanged(int)));
    connect(ui->dialFahrenheit, SIGNAL(valueChanged(int)), converter, SLOT(fahrenheitDialChanged(int)));

    /*!
     * wywoływania metod zmieniających wartości pokręteł
     */
    connect(converter, SIGNAL(setCelsiusDial(int)), ui->dialCelsius, SLOT(setValue(int)));
    connect(converter, SIGNAL(setFahrenheitDial(int)), ui->dialFahrenheit, SLOT(setValue(int)));

    /*!
     * wywoływania metod zmieniających wartości wyświetlane na widgetach lcd
     */
    connect(converter, SIGNAL(displayCelsius(QString)), ui->lcdCelsius, SLOT(display(QString)));
    connect(converter, SIGNAL(displayFahrenheit(QString)), ui->lcdFahrenheit, SLOT(display(QString)));

}

/*!
 * \brief MainWindow::~MainWindow - destruktor klasy
 */
MainWindow::~MainWindow()
{
    delete ui;
    delete converter;
}
