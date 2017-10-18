/*!
  Klasa MainWindow służy do przechowywania właściwości i metod
  wykorzystywanych do stworzenia graficznego interfejsu użytkownika.

  Klasa posiada:
  * właściwości dziedziczone z klasy QMainWindow,
  * wskaźniki na dynamicznie alokowane klasy MainWindow oraz TempConverter.

  Damian Świerk, październik 2017

*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tempconverter.h"

namespace Ui {
class MainWindow;
}

/*!
 * \brief Klasa MainWindow - graficzny interfejs użytkownika
 *
 * Klasa MainWindow służy do przechowywania właściwości i metod
 * wykorzystywanych do stworzenia graficznego interfejsu użytkownika.
 */
class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui; ///< wskaźnik na dynamicznie alkowaną na stercie klasę MainWindow

    TempConverter *converter; ///< wskaźnik na dynamicznie alokowaną na stercie klasę TempConverter
};

#endif // MAINWINDOW_H
