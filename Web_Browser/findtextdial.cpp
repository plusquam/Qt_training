/*!
  \date 25.11.2017r.
  \author Damian Świerk
  */

#include "findtextdial.h"
#include "ui_findtextdial.h"
#include <QDebug>

/*!
 * \brief FindTextDial::FindTextDial
 * Konstruktor klasy.
 *
 * \param _parent - wskaźnik na widget nadrzędny
 */
FindTextDial::FindTextDial(QWidget *_parent) :
    QWidget(_parent),
    ui(new Ui::FindTextDial)
{
    ui->setupUi(this);

    connect(ui->exitButton, SIGNAL(clicked()), this, SLOT(hide()));
    connect(ui->textEdit, SIGNAL(textChanged(QString)), this, SLOT(setText(QString)));
    connect(ui->textEdit, SIGNAL(returnPressed()), this, SLOT(setText()));
    connect(ui->findButton, SIGNAL(clicked()), this, SLOT(findClicked()));
    connect(this, SIGNAL(findClickedReturn()), this, SLOT(findClicked()));
}

/*!
 * \brief FindTextDial::~FindTextDial
 * Destruktor klasy.
 */
FindTextDial::~FindTextDial()
{
    delete ui;
}

/*!
 * \brief FindTextDial::setText
 * Slot zmieniający wartość atrybutu text po zmianie wyszukiwanego tekstu.
 *
 * \param _text - ciąg znaków przechowujący szukany tekst
 */
void FindTextDial::setText(QString _text)
{
    this->text = _text;
}

/*!
 * \brief FindTextDial::setText
 * Slot zmieniający wartość atrybutu text po zmianie wyszukiwanego tekstu
 * W chwili naciśnięcia klawisza enter.
 */
void FindTextDial::setText()
{
    this->text = ui->textEdit->text();
    emit findClickedReturn();
}

/*!
 * \brief FindTextDial::findClicked
 * Slot wywołujący sygnał informujący o zmianie szukanego tekstu.
 */
void FindTextDial::findClicked()
{
    qDebug() << this->text;
    emit sendText(this->text);
}
