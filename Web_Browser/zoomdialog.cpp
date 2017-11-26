/*!
  \date 25.11.2017r.
  \author Damian Świerk
  */

#include "zoomdialog.h"
#include "ui_zoomdialog.h"

/*!
 * \brief ZoomDialog::ZoomDialog
 * Konstruktor klasy.
 *
 * \param _zoomVal - wartość współczynnika
 * \param _parent - wskaźnik na widget nadrzędny
 */
ZoomDialog::ZoomDialog(int _zoomVal, QWidget *_parent) :
    QDialog(_parent),
    ui(new Ui::ZoomDialog),
    zoomVal(_zoomVal)
{
    ui->setupUi(this);
    this->setWindowTitle("Page zoom settings");

    ui->zoomSlider->setValue(_zoomVal);
    ui->zoomValue->setText(QString::number(_zoomVal) + "%");

    connect(ui->zoomSlider, SIGNAL(valueChanged(int)), this, SLOT(zoomChanged(int)));
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

/*!
 * \brief ZoomDialog::~ZoomDialog
 * Destruktor klasy.
 */
ZoomDialog::~ZoomDialog()
{
    delete ui;
}

/*!
 * \brief ZoomDialog::value
 * Metoda zwracająca wartość współczynnika.
 */
int ZoomDialog::value()
{
    return this->zoomVal;
}

/*!
 * \brief ZoomDialog::zoomChanged
 * Metoda wywoływana w chwili zmiany wartości współczynnika.
 *
 * \param _factor - wartość współczynnika
 */
void ZoomDialog::zoomChanged(int _factor)
{
    this->zoomVal = _factor;
    ui->zoomValue->setText(QString::number(_factor) + "%");
}

