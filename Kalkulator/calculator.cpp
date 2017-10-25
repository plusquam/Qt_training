#include "calculator.h"

Calculator::Calculator(QObject *parent) :
    QObject(parent),
    m_lastValue(0),
    m_currValue(0),
    m_operationFlag(0),
    m_dataBase(DATA_BASE_DEC),
    m_dataSize(DATA_SIZE_LONG)
{}

Calculator::~Calculator()
{}

void Calculator::clearData()
{
    this->m_currValue = 0;
    this->m_lastValue = 0;
    this->m_operationFlag = 0;
}

void Calculator::numEntered(int _number)
{
    this->m_currValue *= 10;
    this->m_currValue += _number;

    emit showNumber(QString::number(this->m_currValue));
}

void Calculator::baseEntered(int _base)
{
    this->m_dataBase = (char)_base;

    emit showNumber(QString::number(this->m_currValue, _base));
}

void Calculator::clearClicked()
{
    m_currValue = 0;

    emit showNumber(QString::number(this->m_currValue));
}

void Calculator::allClearClicked()
{
    this->clearData();

    emit showNumber(QString::number(this->m_currValue));
}

void Calculator::addClicked()
{
    if(m_operationFlag == 0)
    {
        this->m_lastValue = this->m_currValue;
        this->m_currValue = 0;
    }
    else
        this->calculate(false);

    m_operationFlag = FLAG_OPER_ADD;
}

void Calculator::subClicked()
{
    if(m_operationFlag == 0)
    {
        this->m_lastValue = this->m_currValue;
        this->m_currValue = 0;
    }
    else
        this->calculate(false);

    m_operationFlag = FLAG_OPER_SUB;
}

void Calculator::multiClicked()
{
    if(m_operationFlag == 0)
    {
        this->m_lastValue = this->m_currValue;
        this->m_currValue = 0;
    }
    else
        this->calculate(false);

    m_operationFlag = FLAG_OPER_MLT;
}

void Calculator::divClicked()
{
    if(m_operationFlag == 0)
    {
        this->m_lastValue = this->m_currValue;
        this->m_currValue = 0;
    }
    else
        this->calculate(false);

    m_operationFlag = FLAG_OPER_DIV;
}

void Calculator::calcClicked()
{
    this->calculate(true);
}

void Calculator::calculate(bool _clearData)
{
    if(m_operationFlag == 0)  return;
    else
        if(m_operationFlag == FLAG_OPER_ADD)
        {
            this->m_lastValue += this->m_currValue;

            emit showNumber(QString::number(this->m_lastValue));

            this->m_currValue = 0;
            if(_clearData)
            {
                m_operationFlag = 0;
                this->m_lastValue = 0;
            }
        }
        else
            if(m_operationFlag == FLAG_OPER_SUB)
                {
                    this->m_lastValue -= this->m_currValue;

                    emit showNumber(QString::number(this->m_lastValue));

                    this->m_currValue = 0;
                    if(_clearData)
                    {
                        m_operationFlag = 0;
                        this->m_lastValue = 0;
                    }

                }
                else
                    if(m_operationFlag == FLAG_OPER_MLT)
                    {
                        this->m_lastValue *= this->m_currValue;

                        emit showNumber(QString::number(this->m_lastValue));

                        this->m_currValue = 0;
                        if(_clearData)
                        {
                            m_operationFlag = 0;
                            this->m_lastValue = 0;
                        }

                    }
                    else
                        if(m_operationFlag == FLAG_OPER_DIV)
                        {
                            this->m_lastValue /= this->m_currValue;

                            emit showNumber(QString::number(this->m_lastValue));

                            this->m_currValue = 0;
                            if(_clearData)
                            {
                                m_operationFlag = 0;
                                this->m_lastValue = 0;
                            }

                        }

}


