#include "calculator.h"

/*!
 * \brief Calculator::Calculator - konstruktor klasy
 * \param _parent - wskaźnik na obiek nadrzędny
 */
Calculator::Calculator(QObject *_parent) :
    QObject(_parent),
    m_lastValue(0),
    m_currValue(0),
    m_operationFlag(0),
    m_dataBase(DATA_BASE_DEC),
    m_dataSize(DATA_SIZE_LONG)
{}

/*!
 * \brief Calculator::clearData - metoda przywracająca wartości domyślne atrybutów klasy
 */
void Calculator::clearData()
{
    this->m_currValue = 0;
    this->m_lastValue = 0;
    this->m_operationFlag = 0;
    this->m_dataBase = DATA_BASE_DEC;
    this->m_dataSize = DATA_SIZE_LONG;
    this->m_operations.clear();
}

/*!
 * \brief Calculator::numEntered - metoda wywołująca proces wprowadzania kolejnej cyfry
 * \param _number - podana cyfra
 */
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

/*!
 * \brief Calculator::baseEntered - metoda zmieniająca podstawę wprowadzanych liczb
 * \param _base - podana podstawa systemu liczbowego
 */
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

/*!
 * \brief Calculator::sizeEntered - metoda zmieniająca rozmiar operowanych słów
 * \param _size - podana długość słowa
 */
void Calculator::sizeEntered(int _size)
{
    this->m_dataSize = _size;
}

/*!
 * \brief Calculator::clearClicked -  metoda wykonująca proces po wciśnięciu klawisza C
 */
void Calculator::clearClicked()
{
    this->m_currValue = 0;

    sendToShow<long>(this->m_currValue);
}

/*!
 * \brief Calculator::allClearClicked -  metoda wykonująca proces po wciśnięciu klawisza AC
 */
void Calculator::allClearClicked()
{
    this->clearData();

    emit showOperations(this->m_operations);

    sendToShow<long>(this->m_currValue);
}

/*!
 * \brief Calculator::addClicked -  metoda wykonująca proces po wciśnięciu klawisza +
 */
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

/*!
 * \brief Calculator::subClicked -  metoda wykonująca proces po wciśnięciu klawisza -
 */
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

/*!
 * \brief Calculator::multiClicked -  metoda wykonująca proces po wciśnięciu klawisza *
 */
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

/*!
 * \brief Calculator::divClicked -  metoda wykonująca proces po wciśnięciu klawisza /
 */
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

/*!
 * \brief Calculator::calcClicked -  metoda wykonująca proces po wciśnięciu klawisza =
 */
void Calculator::calcClicked()
{
    this->m_operations.append(QString::number(this->m_currValue));

    this->selectCalcType(true);
}

/*!
 * \brief Calculator::selectCalcType - metoda wybierająca odpowiednie działanie na liczbach
 * \param _isCalcClicked - warunek czy należy wciśnięto klawisz =
 */
void Calculator::selectCalcType(bool _isCalcClicked)
{
    switch(this->m_dataSize)
    {
    case DATA_SIZE_CHAR:
        this->calculate<char>(_isCalcClicked);
        break;

    case DATA_SIZE_SHORT:
        this->calculate<short>(_isCalcClicked);
        break;

    case DATA_SIZE_INT:
        this->calculate<int>(_isCalcClicked);
        break;

    case DATA_SIZE_LONG:
        this->calculate<long>(_isCalcClicked);
        break;
    }
}

/*!
 * \brief Calculator::calculate - szablon metody wykonującej obliczenia dla odpowiedniego typu danych
 * \param _isCalcClicked - warunek czy należy wciśnięto klawisz =
 */
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

/*!
 * \brief Calculator::sendToShow - szablon metody wywołującej sygnał showNumber() dla odpowiedniego typu danych
 * \param _numb - podana liczba do wyświetlenia
 */
template<typename TYPE>
void Calculator::sendToShow(TYPE _numb)
{
    emit showNumber(QString::number(_numb, (int)this->m_dataBase).toUpper());
}

/*!
 * \brief Calculator::addNewNum - szablon metody dopisującej kolejny znak dla odpowiedniej długości słowa
 * \param _numb - cyfra, która ma być dołączona na końcu liczby
 */
template<typename TYPE>
TYPE Calculator::addNewNum(int _numb)
{
    TYPE tempVal = (TYPE)this->m_currValue;
    tempVal *= (TYPE)this->m_dataBase;
    tempVal += _numb;

    return tempVal;
}
