#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    converter(new TempConverter(0, this))
{
    ui->setupUi(this);

    connect(ui->dialCelsius, SIGNAL(valueChanged(int), ui->lcdCelsius, SLOT(display(int));
    connect(ui->dialCelsius, SIGNAL(valueChanged(int), converter, SLOT(setTempCelsius(int));
    connect(converter, SIGNAL(tempCelsiusChanged(int)), ui->dialCelsius, SLOT(setValue(int));

    connect(ui->dialFahrenheit, SIGNAL(valueChanged(int)), ui->lcdFahrenheit, SLOT(display(int));
    connect(ui->dialFahrenheit, SIGNAL(valueChanged(int)), converter, SLOT(setTempFahrenheit(int));
    connect(converter, SIGNAL(tempFahrenheitChanged(int)), ui->dialFahrenheit, SLOT(setValue(int));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete converter;
}
