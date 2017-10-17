#include "tempconverter.h"

TempConverter::TempConverter(int tempCelsius, QObject *parent) :
    QObject(parent),
    m_tempCelsius(tempCelsius)
{
}

int TempConverter::getTempCelsius() const
{
    return this->m_tempCelsius;
}

int TempConverter::getTempFahrenheit() const
{
    return this->m_tempCelsius * (9.0/5.0) + 32;
}

void TempConverter::setTempCelsius(int tempCelsius)
{
    if(this->m_tempCelsius == tempCelsius)
        return;

    this->m_tempCelsius = tempCelsius;

    emit tempCelsiusChanged(this->m_tempCelsius);
    emit tempFahrenheitChanged(getTempFahrenheit());
}

void TempConverter::setTempFahrenheit(int tempFahrenheit)
{
    setTempCelsius((5.0/9.0) * (tempFahrenheit - 32));
}
