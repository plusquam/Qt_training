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
