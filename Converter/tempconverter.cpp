#include "tempconverter.h"

/*!
 * \brief TempConverter::TempConverter - konstruktor klasy
 * \param tempCelsius - początkowa wartość temperatury wyrażona w stopniach Celcjusza
 * \param parent - wskaźnik na obiek nadrzędny
 */
TempConverter::TempConverter(int tempCelsius, QObject *parent) :
    QObject(parent),
    m_tempCelsius(tempCelsius),
    m_isCelsiusDialChanged(false),
    m_isFahrenheitDialChanged(false)
{
}

/*!
 * \brief TempConverter::getTempCelsius - pomocnicza funkcja pobierająca wartość temp. w sklai Celcjusza
 * \return
 */
double TempConverter::getTempCelsius() const
{
    return this->m_tempCelsius;
}

/*!
 * \brief TempConverter::getTempFahrenheit - pomocnicza funkcja pobierająca wartość temp. w sklai Fahrenheita
 * \return
 */
double TempConverter::getTempFahrenheit() const
{
    return this->m_tempCelsius * (9.0/5.0) + 32;
}

/*!
 * \brief TempConverter::setTempCelsius - pomocnicza funkcja zmieniająca wartość temp. w skali Celcjusza
 * \param tempCelsius - wartość temperatury w stopniach C
 */
void TempConverter::setTempCelsius(int tempCelsius)
{
    this->m_tempCelsius = tempCelsius;
}

/*!
 * \brief TempConverter::setTempFahrenheit - pomocnicza funkcja zmieniająca wartość temp. w skali Fahrenheita
 * \param tempFahrenheit - wartość temperatury w stopniach F
 */
void TempConverter::setTempFahrenheit(int tempFahrenheit)
{
    this->m_tempCelsius = (5.0 / 9.0) * (tempFahrenheit -32);
}

/*!
 * \brief TempConverter::celsiusDialChanged - metoda wywoływana w chwili zmiany wartości temp. w skali Celcjusza
 * \param tempCelsius - wartość po zmianie temperatury
 */
void TempConverter::celsiusDialChanged(int tempCelsius)
{
    /*!
     Sprawdzenie czy metoda nie została wywołana ponownie dla jednej zmiany wartości pokrętła.
     */
    m_isCelsiusDialChanged = !m_isCelsiusDialChanged;

    if(!m_isCelsiusDialChanged)
        return;

    m_isFahrenheitDialChanged = !m_isFahrenheitDialChanged;

    this->m_tempCelsius = tempCelsius;

    /*!
     Wywoływania metod zmiany wartości pokręteł i wartości wyświetlanych na widgetach lcd.
     */
    emit displayCelsius(QString::number(this->m_tempCelsius, 'f', 2 ));
    emit displayFahrenheit(QString::number(this->m_tempCelsius * (9.0/5.0) + 32, 'f', 2 ));

    emit setCelsiusDial(this->m_tempCelsius);
    emit setFahrenheitDial(this->m_tempCelsius);
}

/*!
 * \brief TempConverter::fahrenheitDialChanged - metoda wywoływana w chwili zmiany wartości temp. w skali Fahrenheita
 * \param tempCelsius - wartość po zmianie temperatury
 */
void TempConverter::fahrenheitDialChanged(int tempCelsius)
{
    /*!
     Sprawdzenie czy metoda nie została wywołana ponownie dla jednej zmiany wartości pokrętła.
     */
    m_isFahrenheitDialChanged = !m_isFahrenheitDialChanged;

    if(!m_isFahrenheitDialChanged)
        return;

    m_isCelsiusDialChanged = !m_isCelsiusDialChanged;

    this->m_tempCelsius = tempCelsius;

    int tempFahrenheit = (int)(this->m_tempCelsius * (9.0/5.0) + 32);

    /*!
     Wywoływania metod zmiany wartości pokręteł i wartości wyświetlanych na widgetach lcd.
     */
    emit displayCelsius(QString::number((5.0 / 9.0) * (double)(tempFahrenheit -32), 'f', 2 ));
    emit displayFahrenheit(QString::number(tempFahrenheit, 'f', 2 ));

    emit setCelsiusDial(this->m_tempCelsius);
    emit setFahrenheitDial(this->m_tempCelsius);

}
