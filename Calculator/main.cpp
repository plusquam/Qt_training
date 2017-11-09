/*!
 *\mainpage Kalkulator
 * \author Damian Świerk
 * \date 29.10.2017
 * \section Założenia
 *
 * Założenia projektowe
 Cel projektu:
    *-# podstawowe operacje arytmetyczne (+,-,*,/) oraz logiczne,
    *-# przeliczanie danych w rożnych systemach liczbowych (np. dwójkowym, czwórkowym, szesnastkowym),
    *-# przyjazny graficzny interfejs użytkownika,
    * dostosowujący się do rozmiarów okna oraz trybu pracy (np. ukrywający niedostępne/niedozwolone opcje),
    *-# interfejs GUI i logika sterująca muszą być rozdzielone,
    *-# dodatkowo: możliwość obliczeń na liczbach zespolonych lub ułamkach wymiernych.


 Wnioski:
    *-# Poznanie obsługi widgetów takich jak button, radioButton.
    *-# Zdobycie wiedzy na temat konwersji między różnymi typami danych
    *-# Zaznajomienie się z działaniem signal mappera
    *-# Zwiększenie doświadczenia z szablonami funkcji
    *-# Poznanie sposobów implementacji kalkulatora z wykorzystaniem Qt


*/

#include "calculatorinterface.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    long b = -2;
    char c = (char)b;
    qDebug() << (int)c;
    qDebug() << sizeof(char) << sizeof(short) << sizeof(int) << sizeof(long);
    QApplication a(argc, argv);
    CalculatorInterface w;
    w.show();

    return a.exec();
}
