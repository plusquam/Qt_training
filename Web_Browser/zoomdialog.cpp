#include "zoomdialog.h"
#include "ui_zoomdialog.h"

ZoomDialog::ZoomDialog(int _zoomVal, QWidget *_parent) :
    zoomVal(_zoomVal),
    QDialog(_parent),
    ui(new Ui::ZoomDialog),
    isAccepted(false)
{
    ui->setupUi(this);
    this->setWindowTitle("Page zoom settings");

    ui->zoomSlider->setValue(_zoomVal);
    ui->zoomValue->setText(QString::number(_zoomVal) + "%");

    connect(ui->zoomSlider, SIGNAL(valueChanged(int)), this, SLOT(zoomChanged(int)));
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

ZoomDialog::~ZoomDialog()
{
    delete ui;
}

int ZoomDialog::value()
{
    return this->zoomVal;
}

void ZoomDialog::zoomChanged(int _factor)
{
    this->zoomVal = _factor;
    ui->zoomValue->setText(QString::number(_factor) + "%");
}

