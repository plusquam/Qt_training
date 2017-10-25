#include "calculatorinterface.h"
#include "ui_calculatorinterface.h"

#include "calculator.h"

CalculatorInterface::CalculatorInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CalculatorInterface),
    m_calculator(new Calculator(this))
{
    ui->setupUi(this);
    QSignalMapper *numberMapper = new QSignalMapper;

    /////////////////////
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
/////////////////////

    connect(ui->buttonAdd,SIGNAL(clicked()), m_calculator, SLOT(addClicked()));
    connect(ui->buttonSubtrackt,SIGNAL(clicked()), m_calculator, SLOT(subClicked()));
    connect(ui->buttonMultiply,SIGNAL(clicked()), m_calculator, SLOT(multiClicked()));
    connect(ui->buttonDivide,SIGNAL(clicked()), m_calculator, SLOT(divClicked()));

    connect(ui->buttonClear,SIGNAL(clicked()), m_calculator, SLOT(calcClicked()));
    connect(ui->buttonAllClear,SIGNAL(clicked()), m_calculator, SLOT(allClearClicked()));

    connect(ui->buttonCalculate,SIGNAL(clicked()), m_calculator, SLOT(calcClicked()));

    connect(m_calculator, SIGNAL(showNumber(QString)), ui->entryLabel, SLOT(setText(QString)));

    //////////
    QSignalMapper *radioButtonMapper = new QSignalMapper;

    connect(ui->radioButtonDec,SIGNAL(clicked(bool)), radioButtonMapper, SLOT(map()));
    radioButtonMapper->setMapping(ui->radioButtonDec,10);

    connect(ui->radioButtonBin,SIGNAL(clicked(bool)), radioButtonMapper, SLOT(map()));
    radioButtonMapper->setMapping(ui->radioButtonBin,2);

    connect(ui->radioButtonQuat,SIGNAL(clicked(bool)), radioButtonMapper, SLOT(map()));
    radioButtonMapper->setMapping(ui->radioButtonQuat,4);

    connect(ui->radioButtonOct,SIGNAL(clicked(bool)), radioButtonMapper, SLOT(map()));
    radioButtonMapper->setMapping(ui->radioButtonOct,8);

    connect(ui->radioButtonHex,SIGNAL(clicked(bool)), radioButtonMapper, SLOT(map()));
    radioButtonMapper->setMapping(ui->radioButtonHex,16);

    connect(radioButtonMapper, SIGNAL(mapped(int)), m_calculator, SLOT(baseEntered(int)));
    ////////
}

CalculatorInterface::~CalculatorInterface()
{
    delete ui;
}
