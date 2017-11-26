/*!
  \date 25.11.2017r.
  \author Damian Świerk
  */

#ifndef ZOOMDIALOG_H
#define ZOOMDIALOG_H

#include <QDialog>
#include <QAbstractButton>
#include <QDialogButtonBox>

namespace Ui {
class ZoomDialog;
}

/*!
 * \brief Klasa ZoomDialog
 * Klasa przechowująca własności kontrolki zmiany wartości współczynnika skalowania strony.
 */
class ZoomDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ZoomDialog(int _zoomVal, QWidget *_parent = 0);    ///< Konstruktor
    ~ZoomDialog();                                              ///< Destruktor
    int value();                                                ///< Getter wartości współczynnika

public slots:
    void zoomChanged(int _factor);  ///< Slot wywoływany w chwili zmiany wartości współczynnika

private:
    Ui::ZoomDialog *ui; ///< Wskaźnik na obiekt klasy
    int zoomVal;        ///< Wartość współćzynnika
};

#endif // ZOOMDIALOG_H
