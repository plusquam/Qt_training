#include "calculator.h"

Calculator::Calculator(QObject *_parent) :
    QObject(_parent),
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
    switch(this->m_dataSize)
    {
    case DATA_SIZE_CHAR:
        this->m_currValue = (long)addNewNum<char>(_number);
        sendToShow<char>((char)this->m_currValue);
        break;

    case DATA_SIZE_SHORT:
        this->m_currValue = (long)addNewNum<short>(_number);
        sendToShow<short>((short)this->m_currValue);
        break;

    case DATA_SIZE_INT:
        this->m_currValue = (long)addNewNum<int>(_number);
        sendToShow<int>((int)this->m_currValue);
        break;

    case DATA_SIZE_LONG:
        this->m_currValue = (long)addNewNum<long>(_number);
        sendToShow<long>(this->m_currValue);
        break;
    }
}

void Calculator::baseEntered(int _base)
{
    this->m_dataBase = (char)_base;

    if(this->m_currValue != 0)
        sendToShow<long>(this->m_currValue);
    else
        if(this->m_lastValue != 0)
            sendToShow<long>(this->m_lastValue);
        else
            sendToShow<int>(0);
}

void Calculator::sizeEntered(int _size)
{
    this->m_dataSize = _size;
}

void Calculator::clearClicked()
{
    this->m_currValue = 0;

    sendToShow<long>(this->m_currValue);
}

void Calculator::allClearClicked()
{
    this->clearData();

    this->m_operations.clear();
    emit showOperations(this->m_operations);

    sendToShow<long>(this->m_currValue);
}

void Calculator::addClicked()
{
    if(this->m_operationFlag == 0)
    {
        this->m_lastValue = this->m_currValue;
        this->m_currValue = 0;

        this->m_operations.append(QString::number(this->m_lastValue));
        this->m_operations.append('+');
        emit showOperations(this->m_operations);
    }
    else
    {
        this->m_operations.append(QString::number(this->m_currValue));
        this->m_operations.append('+');
        this->selectCalcType(false);
    }

    this->m_operationFlag = FLAG_OPER_ADD;
}

void Calculator::subClicked()
{
    if(this->m_operationFlag == 0)
    {
        this->m_lastValue = this->m_currValue;
        this->m_currValue = 0;

        this->m_operations.append(QString::number(this->m_lastValue));
        this->m_operations.append('-');
        emit showOperations(this->m_operations);
    }
    else
    {
        this->m_operations.append(QString::number(this->m_currValue));
        this->m_operations.append('-');
        this->selectCalcType(false);
    }

    this->m_operationFlag = FLAG_OPER_SUB;
}

void Calculator::multiClicked()
{
    if(this->m_operationFlag == 0)
    {
        this->m_lastValue = this->m_currValue;
        this->m_currValue = 0;

        this->m_operations.append(QString::number(this->m_lastValue));
        this->m_operations.append('*');
        emit showOperations(this->m_operations);
    }
    else
    {
        this->m_operations.append(QString::number(this->m_currValue));
        this->m_operations.append('*');
        this->selectCalcType(false);
    }

    this->m_operationFlag = FLAG_OPER_MLT;
}

void Calculator::divClicked()
{
    if(this->m_operationFlag == 0)
    {
        this->m_lastValue = this->m_currValue;
        this->m_currValue = 0;

        this->m_operations.append(QString::number(this->m_lastValue));
        this->m_operations.append('/');
        emit showOperations(this->m_operations);
    }
    else
    {
        this->m_operations.append(QString::number(this->m_currValue));
        this->m_operations.append('/');
        this->selectCalcType(false);
    }

    this->m_operationFlag = FLAG_OPER_DIV;
}

void Calculator::calcClicked()
{
    this->m_operations.append(QString::number(this->m_currValue));

    this->selectCalcType(true);
}

void Calculator::selectCalcType(bool _clear)
{
    switch(this->m_dataSize)
    {
    case DATA_SIZE_CHAR:
        this->calculate<char>(_clear);
        break;

    case DATA_SIZE_SHORT:
        this->calculate<short>(_clear);
        break;

    case DATA_SIZE_INT:
        this->calculate<int>(_clear);
        break;

    case DATA_SIZE_LONG:
        this->calculate<long>(_clear);
        break;
    }
}

template<typename TYPE>
void Calculator::calculate(bool _isCalcClicked)
{
    TYPE tempLastVal = (TYPE)this->m_lastValue, tempCurrVal = (TYPE)this->m_currValue;

    switch(this->m_operationFlag)
    {
    case FLAG_OPER_ADD:
        tempLastVal += tempCurrVal;
        break;

    case FLAG_OPER_SUB:
        tempLastVal -= tempCurrVal;
        break;

    case FLAG_OPER_MLT:
        tempLastVal *= tempCurrVal;
        break;

    case FLAG_OPER_DIV:
        tempLastVal /= tempCurrVal;
        break;

    default:
        return;
    }

    this->m_lastValue = (long)tempLastVal;

    sendToShow<TYPE>(tempLastVal);

    this->m_currValue = 0;

    if(_isCalcClicked)
    {
        m_operationFlag = 0;

        this->m_operations.append(QString('='));
        this->m_operations.append(QString::number(this->m_lastValue));
    }

    emit showOperations(this->m_operations);

    if(_isCalcClicked)
        m_operations.clear();
}

template<typename TYPE>
void Calculator::sendToShow(TYPE _numb)
{
    emit showNumber(QString::number(_numb, (int)this->m_dataBase).toUpper());
}


template<typename TYPE>
TYPE Calculator::addNewNum(int _numb)
{
    TYPE tempVal = (TYPE)this->m_currValue;
    tempVal *= (TYPE)this->m_dataBase;
    tempVal += _numb;

    return tempVal;
}
