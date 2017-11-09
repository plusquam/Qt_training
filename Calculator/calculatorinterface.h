/*!
  Klasa CalculatorInterface służy do przechowywania właściwości i metod
  wykorzystywanych do stworzenia graficznego interfejsu użytkownika kalkulatora.

  Klasa posiada:
  * właściwości dziedziczone z klasy QWidget,
  * wskaźniki na dynamicznie alokowane klasy Calculator oraz CalculatorInterface.

  Damian Świerk, październik 2017

*/

#ifndef CALCULATORINTERFACE_H
#define CALCULATORINTERFACE_H

#include <QWidget>
#include <QSignalMapper>

class Calculator;

namespace Ui {
class CalculatorInterface;
}

/*!
 * \brief Klasa CalculatorInterface - graficzny interfejs użytkownika
 *
 * Klasa CalculatorInterface służy do przechowywania właściwości i metod
 * wykorzystywanych do stworzenia graficznego interfejsu użytkownika kalkulatora.
 */
class CalculatorInterface : public QWidget
{
    Q_OBJECT

public:
    explicit CalculatorInterface(QWidget *parent = 0);
    ~CalculatorInterface();

public slots:
    void activateButtons(int); ///< metoda odblokowująca klawisze adekwatnie do wybranego systemu liczbowego

private:
    Ui::CalculatorInterface *ui;    ///< wskaźnik na obiekt klasy CalculatorInterface
    Calculator *m_calculator;       ///< wskaźnik na obiekt klasy Calculator
};

#endif // CALCULATORINTERFACE_H
