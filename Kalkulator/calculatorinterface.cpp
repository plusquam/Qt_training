#include "calculatorinterface.h"
#include "ui_calculatorinterface.h"

#include "calculator.h"

/*!
 * \brief CalculatorInterface::CalculatorInterface - konstruktor klasy
 * \param parent - wskaźnik na obiek nadrzędny
 */
CalculatorInterface::CalculatorInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CalculatorInterface),
    m_calculator(new Calculator(this))
{
    ui->setupUi(this);
    QSignalMapper *numberMapper = new QSignalMapper;

    /*!
     *  Przypisanie sygnałów wciśnięcia klawiszy cyfr do obiektu numberMapper
     */

    connect(ui->buttonZero,SIGNAL(clicked()), numberMapper, SLOT(map()));
    numberMapper->setMapping(ui->buttonZero,0);

    connect(ui->buttonOne,SIGNAL(clicked()), numberMapper, SLOT(map()));
    numberMapper->setMapping(ui->buttonOne,1);

    connect(ui->buttonTwo,SIGNAL(clicked()), numberMapper, SLOT(map()));
    numberMapper->setMapping(ui->buttonTwo,2);

    connect(ui->buttonThree,SIGNAL(clicked()), numberMapper, SLOT(map()));
    numberMapper->setMapping(ui->buttonThree,3);

    connect(ui->buttonFour,SIGNAL(clicked()), numberMapper, SLOT(map()));
    numberMapper->setMapping(ui->buttonFour,4);

    connect(ui->buttonFive,SIGNAL(clicked()), numberMapper, SLOT(map()));
    numberMapper->setMapping(ui->buttonFive,5);

    connect(ui->buttonSix,SIGNAL(clicked()), numberMapper, SLOT(map()));
    numberMapper->setMapping(ui->buttonSix,6);

    connect(ui->buttonSeven,SIGNAL(clicked()), numberMapper, SLOT(map()));
    numberMapper->setMapping(ui->buttonSeven,7);

    connect(ui->buttonEight,SIGNAL(clicked()), numberMapper, SLOT(map()));
    numberMapper->setMapping(ui->buttonEight,8);

    connect(ui->buttonNine,SIGNAL(clicked()), numberMapper, SLOT(map()));
    numberMapper->setMapping(ui->buttonNine,9);

    connect(ui->buttonA,SIGNAL(clicked()), numberMapper, SLOT(map()));
    numberMapper->setMapping(ui->buttonA,10);

    connect(ui->buttonB,SIGNAL(clicked()), numberMapper, SLOT(map()));
    numberMapper->setMapping(ui->buttonB,11);

    connect(ui->buttonC,SIGNAL(clicked()), numberMapper, SLOT(map()));
    numberMapper->setMapping(ui->buttonC,12);

    connect(ui->buttonD,SIGNAL(clicked()), numberMapper, SLOT(map()));
    numberMapper->setMapping(ui->buttonD,13);

    connect(ui->buttonE,SIGNAL(clicked()), numberMapper, SLOT(map()));
    numberMapper->setMapping(ui->buttonE,14);

    connect(ui->buttonF,SIGNAL(clicked()), numberMapper, SLOT(map()));
    numberMapper->setMapping(ui->buttonF,15);

    connect(numberMapper, SIGNAL(mapped(int)), m_calculator, SLOT(numEntered(int)));

    /*!
     *  Przypisanie sygnałów wciśnięcia klawiszy działań
     */

    connect(ui->buttonAdd,SIGNAL(clicked()), m_calculator, SLOT(addClicked()));
    connect(ui->buttonSubtrackt,SIGNAL(clicked()), m_calculator, SLOT(subClicked()));
    connect(ui->buttonMultiply,SIGNAL(clicked()), m_calculator, SLOT(multiClicked()));
    connect(ui->buttonDivide,SIGNAL(clicked()), m_calculator, SLOT(divClicked()));

    connect(ui->buttonClear,SIGNAL(clicked()), m_calculator, SLOT(calcClicked()));
    connect(ui->buttonAllClear,SIGNAL(clicked()), m_calculator, SLOT(allClearClicked()));

    connect(ui->buttonCalculate,SIGNAL(clicked()), m_calculator, SLOT(calcClicked()));

    connect(m_calculator, SIGNAL(showNumber(QString)), ui->numberLabel, SLOT(setText(QString)));
    connect(m_calculator, SIGNAL(showOperations(QString)), ui->operationsBrowser, SLOT(setPlainText(QString)));


    /*!
     *  Przypisanie sygnałów wciśnięcia przełączników podstawy systemu liczbowego do obiektu dataBaseButtonMapper
     */

    QSignalMapper *dataBaseButtonMapper = new QSignalMapper;

    connect(ui->radioButtonDec,SIGNAL(clicked(bool)), dataBaseButtonMapper, SLOT(map()));
    dataBaseButtonMapper->setMapping(ui->radioButtonDec,DATA_BASE_DEC);

    connect(ui->radioButtonBin,SIGNAL(clicked(bool)), dataBaseButtonMapper, SLOT(map()));
    dataBaseButtonMapper->setMapping(ui->radioButtonBin,DATA_BASE_BIN);

    connect(ui->radioButtonQuat,SIGNAL(clicked(bool)), dataBaseButtonMapper, SLOT(map()));
    dataBaseButtonMapper->setMapping(ui->radioButtonQuat,DATA_BASE_QUAT);

    connect(ui->radioButtonOct,SIGNAL(clicked(bool)), dataBaseButtonMapper, SLOT(map()));
    dataBaseButtonMapper->setMapping(ui->radioButtonOct,DATA_BASE_OCT);

    connect(ui->radioButtonHex,SIGNAL(clicked(bool)), dataBaseButtonMapper, SLOT(map()));
    dataBaseButtonMapper->setMapping(ui->radioButtonHex,DATA_BASE_HEX);

    connect(dataBaseButtonMapper, SIGNAL(mapped(int)), m_calculator, SLOT(baseEntered(int)));
    connect(dataBaseButtonMapper, SIGNAL(mapped(int)), this, SLOT(activateButtons(int)));

    /*!
     *  Przypisanie sygnałów wciśnięcia przełączników długości słowa do obiektu dataSizeButtonMapper
     */

    QSignalMapper *dataSizeButtonMapper = new QSignalMapper;

    connect(ui->radioButtonChar,SIGNAL(clicked(bool)), dataSizeButtonMapper, SLOT(map()));
    dataSizeButtonMapper->setMapping(ui->radioButtonChar, DATA_SIZE_CHAR);

    connect(ui->radioButtonShort,SIGNAL(clicked(bool)), dataSizeButtonMapper, SLOT(map()));
    dataSizeButtonMapper->setMapping(ui->radioButtonShort, DATA_SIZE_SHORT);

    connect(ui->radioButtonInt,SIGNAL(clicked(bool)), dataSizeButtonMapper, SLOT(map()));
    dataSizeButtonMapper->setMapping(ui->radioButtonInt, DATA_SIZE_INT);

    connect(ui->radioButtonLong,SIGNAL(clicked(bool)), dataSizeButtonMapper, SLOT(map()));
    dataSizeButtonMapper->setMapping(ui->radioButtonLong, DATA_SIZE_LONG);

    connect(dataSizeButtonMapper, SIGNAL(mapped(int)), m_calculator, SLOT(sizeEntered(int)));
}

/*!
 * \brief CalculatorInterface::~CalculatorInterface - destruktor klasy
 */
CalculatorInterface::~CalculatorInterface()
{
    delete ui;
}

/*!
 * \brief CalculatorInterface::activateButtons - metoda aktywowania odpowiednich klawiszy cyfr
 * \param _base - wybrana postawa systemu liczbowego
 */
void CalculatorInterface::activateButtons(int _base)
{
    switch(_base)
    {
    case DATA_BASE_BIN:
        ui->buttonTwo->setEnabled(false);
        ui->buttonThree->setEnabled(false);
        ui->buttonFour->setEnabled(false);
        ui->buttonFive->setEnabled(false);
        ui->buttonSix->setEnabled(false);
        ui->buttonSeven->setEnabled(false);
        ui->buttonEight->setEnabled(false);
        ui->buttonNine->setEnabled(false);
        ui->buttonA->setEnabled(false);
        ui->buttonB->setEnabled(false);
        ui->buttonC->setEnabled(false);
        ui->buttonD->setEnabled(false);
        ui->buttonE->setEnabled(false);
        ui->buttonF->setEnabled(false);
        break;

    case DATA_BASE_QUAT:
        ui->buttonTwo->setEnabled(true);
        ui->buttonThree->setEnabled(true);
        ui->buttonFour->setEnabled(false);
        ui->buttonFive->setEnabled(false);
        ui->buttonSix->setEnabled(false);
        ui->buttonSeven->setEnabled(false);
        ui->buttonEight->setEnabled(false);
        ui->buttonNine->setEnabled(false);
        ui->buttonA->setEnabled(false);
        ui->buttonB->setEnabled(false);
        ui->buttonC->setEnabled(false);
        ui->buttonD->setEnabled(false);
        ui->buttonE->setEnabled(false);
        ui->buttonF->setEnabled(false);
        break;

    case DATA_BASE_OCT:
        ui->buttonTwo->setEnabled(true);
        ui->buttonThree->setEnabled(true);
        ui->buttonFour->setEnabled(true);
        ui->buttonFive->setEnabled(true);
        ui->buttonSix->setEnabled(true);
        ui->buttonSeven->setEnabled(true);
        ui->buttonEight->setEnabled(false);
        ui->buttonNine->setEnabled(false);
        ui->buttonA->setEnabled(false);
        ui->buttonB->setEnabled(false);
        ui->buttonC->setEnabled(false);
        ui->buttonD->setEnabled(false);
        ui->buttonE->setEnabled(false);
        ui->buttonF->setEnabled(false);
        break;

    case DATA_BASE_DEC:
        ui->buttonTwo->setEnabled(true);
        ui->buttonThree->setEnabled(true);
        ui->buttonFour->setEnabled(true);
        ui->buttonFive->setEnabled(true);
        ui->buttonSix->setEnabled(true);
        ui->buttonSeven->setEnabled(true);
        ui->buttonEight->setEnabled(true);
        ui->buttonNine->setEnabled(true);
        ui->buttonA->setEnabled(false);
        ui->buttonB->setEnabled(false);
        ui->buttonC->setEnabled(false);
        ui->buttonD->setEnabled(false);
        ui->buttonE->setEnabled(false);
        ui->buttonF->setEnabled(false);
        break;

    case DATA_BASE_HEX:
        ui->buttonTwo->setEnabled(true);
        ui->buttonThree->setEnabled(true);
        ui->buttonFour->setEnabled(true);
        ui->buttonFive->setEnabled(true);
        ui->buttonSix->setEnabled(true);
        ui->buttonSeven->setEnabled(true);
        ui->buttonEight->setEnabled(true);
        ui->buttonNine->setEnabled(true);
        ui->buttonA->setEnabled(true);
        ui->buttonB->setEnabled(true);
        ui->buttonC->setEnabled(true);
        ui->buttonD->setEnabled(true);
        ui->buttonE->setEnabled(true);
        ui->buttonF->setEnabled(true);
        break;
    }
}
