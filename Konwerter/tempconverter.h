#ifndef TEMPCONVERTER_H
#define TEMPCONVERTER_H

#include <QObject>

class TempConverter : public QObject
{
    Q_OBJECT
public:
    explicit TempConverter(int tempCelsius, QObject *parent = 0);

    int getTempCelsius() const;
    int getTempFahrenheit() const;

private:
    int m_tempCelsius;

signals:
    void tempCelsiusChanged(int);
    void tempFahrenheitChanged(int);

public slots:
    void setTempCelsius(int);
    void setTempFahrenheit(int);


};

#endif // TEMPCONVERTER_H
