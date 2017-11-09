/*!
  Klasa Calculator służy do przechowywania właściwości i metod
  wykorzystywanych do stworzenia narzędzi służacych do obsługi
  interfejsu kalkulatora zbudowanego wewnątrz klasy CalculatorInterface.

  Klasa posiada:
  * właściwości dziedziczone z klasy QObject,
  * metody oraz atrybuty klasy pozwalające na wykonywanie działań kalkulatora.
  * sygnały do powiadamiania o zmianach,
  * zmienne prywatne do przechowywania bierzącej lub ostatniej wartości liczb,
  * flagi: działań, długości słowa oraz podstaw liczb

  Damian Świerk, październik 2017

*/

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QObject>
#include <QString>
#include "QDebug"

#define FLAG_OPER_ADD 1 << 0
#define FLAG_OPER_SUB 1 << 1
#define FLAG_OPER_MLT 1 << 2
#define FLAG_OPER_DIV 1 << 3
#define FLAG_OPER_CALC 1 << 7

#define DATA_BASE_DEC 10
#define DATA_BASE_BIN 2
#define DATA_BASE_QUAT 4
#define DATA_BASE_OCT 8
#define DATA_BASE_HEX 16

#define DATA_SIZE_CHAR sizeof(char)
#define DATA_SIZE_SHORT sizeof(short)
#define DATA_SIZE_INT sizeof(int)
#define DATA_SIZE_LONG sizeof(long)

/*!
 * \brief Klasa Calculator - pakiet narzędzi do obsługi kalkulatora
 *
 * Klasa Calculator służy do przechowywania właściwości i metod
 * wykorzystywanych do obsługi działań graficznego kalkulatora klasy CalculatorInterface.
 */
class Calculator : public QObject
{
    Q_OBJECT
public:
    explicit Calculator(QObject *_parent = 0);
    void clearData(); ///< metoda przywracająca domyśle wartości atrybutów klasy

signals:
    void showNumber(QString); ///< sygnał dokonywujący wyświetlenia podanego ciągu znaków w numberLabel
    void showOperations(QString); ///< sygnał dokonywujący wyświetlenia podanego ciągu znaków w operationsBrowser

public slots:
    void numEntered(int);   ///< metoda wywołująca proces wprowadzania kolejnej cyfry
    void baseEntered(int);  ///< metoda zmieniająca podstawę wprowadzanych liczb
    void sizeEntered(int);  ///< metoda zmieniająca rozmiar operowanych słów

    void clearClicked();    ///< metoda wykonująca proces po wciśnięciu klawisza C
    void allClearClicked(); ///< metoda wykonująca proces po wciśnięciu klawisza AC

    void addClicked();      ///< metoda wykonująca proces po wciśnięciu klawisza +
    void subClicked();      ///< metoda wykonująca proces po wciśnięciu klawisza -
    void multiClicked();    ///< metoda wykonująca proces po wciśnięciu klawisza *
    void divClicked();      ///< metoda wykonująca proces po wciśnięciu klawisza /

    void calcClicked();     ///< metoda wykonująca proces po wciśnięciu klawisza =

private:
    long m_lastValue;       ///< atrybut przechowujący wynik, bądź poprzednio wprowadzoną liczbę
    long m_currValue;       ///< atrybut przechowujący ostatnio wprowadzoną liczbę
    char m_operationFlag;   ///< flaga wybranego ostatniego działania

    char m_dataBase;        ///< atrybut przechowujący podstawę liczby
    char m_dataSize;        ///< atrybut przechowujący długość słowa

    QString m_operations;   ///< atrybut przechowujący ciąg operacji

    void selectCalcType(bool _isCalcClicked);   ///< metoda wybierająca odpowiednie działanie na liczbach

    template<typename TYPE>
    void calculate(bool _isCalcClicked);    ///< szablon metody wykonującej obliczenia dla odpowiedniego typu danych

    template<typename TYPE>
    void sendToShow(TYPE _numb);    ///< szablon metody wywołującej sygnał showNumber() dla odpowiedniego typu danych

    template<typename TYPE>
    TYPE addNewNum(int _numb);      ///< szablon metody dopisującej kolejny znak dla odpowiedniej długości słowa

};

#endif // CALCULATOR_H
