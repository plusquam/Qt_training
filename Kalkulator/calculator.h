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

class Calculator : public QObject
{
    Q_OBJECT
public:
    explicit Calculator(QObject *parent = 0);
    ~Calculator();
    void clearData();

signals:
    void showNumber(QString);

public slots:
    void numEntered(int);
    void baseEntered(int);

    void clearClicked();
    void allClearClicked();

    void addClicked();
    void subClicked();
    void multiClicked();
    void divClicked();

    void calcClicked();

private:
    long m_lastValue;
    long m_currValue;
    char m_operationFlag;

    char m_dataBase;
    char m_dataSize;

    void calculate(bool _clearData);

};




#endif // CALCULATOR_H
