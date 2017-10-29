#ifndef CALCULATORINTERFACE_H
#define CALCULATORINTERFACE_H

#include <QWidget>
#include <QSignalMapper>

class Calculator;

namespace Ui {
class CalculatorInterface;
}

class CalculatorInterface : public QWidget
{
    Q_OBJECT

public:
    explicit CalculatorInterface(QWidget *parent = 0);
    ~CalculatorInterface();

public slots:
    void activateButtons(int);

private:
    Ui::CalculatorInterface *ui;
    Calculator *m_calculator;
};

#endif // CALCULATORINTERFACE_H
