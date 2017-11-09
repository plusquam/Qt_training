/*!
  Klasa TempConverter służy do konwersji wartości temperatury między skalami Celciusza
  i Fahrenheita.

  Klasa posiada:
  * sloty do zadawania wartości temperatury i wywoływania metody zmiany wartości temperatury,
  * sygnały do powiadamiania o zmianach,
  * metody pomocnicze do pobierania wartości w danej skali,
  * zmienną prywatną do przechowywania wartości temperatury,
  * zmienne pomocnicze służące do wykluczenia powtórzeń wywoływania metod

  Damian Świerk, październik 2017

*/

#ifndef TEMPCONVERTER_H
#define TEMPCONVERTER_H

#include <QObject>

/*!
 * \brief Klasa TempConverter - konwersja wartości temperatury
 *
 * Klasa MainWindow służy do przeliczania wartości temperatury między
 * skalami Celcjusza i Fahrenheita.
 */
class TempConverter : public QObject
{
    Q_OBJECT
public:
    explicit TempConverter(int tempCelsius, QObject *parent = 0);

    double getTempCelsius() const; ///< pomocnicza funkcja pobierająca wartość temp. w sklai Celcjusza
    double getTempFahrenheit() const; ///< pomocnicza funkcja pobierająca wartość temp. w sklai Fahrenheita

private:
    double m_tempCelsius; ///< zmienna przechowująca temperaturę w stopniach C
    bool m_isCelsiusDialChanged; ///< zmienna odzwierciedlająca zmianę wartości temperatury
    bool m_isFahrenheitDialChanged; ///< zmienna odzwierciedlająca zmianę wartości temperatury

signals:
    void displayCelsius(QString); ///< sygnał zmiany wartości wyświetlacza lcdCelsius
    void displayFahrenheit(QString); ///< sygnał zmiany wartości wyświetlacza lcdFahrenheit
    void setCelsiusDial(int); ///< sygnał zmiany wartości pokrętła dialCelsius
    void setFahrenheitDial(int); ///< sygnał zmiany wartości pokrętła dialFahrenheit

public slots:
    void setTempCelsius(int); ///< zmiana wartości zmiennej m_tempCelsius w skali Celcjusza
    void setTempFahrenheit(int); ///< zmiana wartości zmiennej m_tempCelsius w skali Fahrenheita
    void celsiusDialChanged(int); ///< metoda wywoływana w chwili zmiany wartości temp. w skali Celcjusza
    void fahrenheitDialChanged(int); ///< metoda wywoływana w chwili zmiany wartości temp. w skali Fahrenheita

};

#endif // TEMPCONVERTER_H
