#include <QKeyEvent>

#include "calculator_form.h"

const QChar MathSymbolSquareRoot(0x221A);
const QChar MathSymbolPlusMinus(0x00B1);
const QChar MathSymbolSquare(0x00B2);

CalculatorForm::CalculatorForm(QWidget *parent) : QWidget(parent)
{
    ui.setupUi(this);

    ui.pushButton_Root->setText( QString(MathSymbolSquareRoot) + QString("x") );
    ui.pushButton_Sqr->setText( QString("x") + QString(MathSymbolSquare) );
    ui.pushButton_ChSign->setText( QString(MathSymbolPlusMinus) );

    connect( ui.pushButton_0, &QPushButton::clicked, this,  [=](){ ui.display->inputDigit('0'); } ); 
    connect( ui.pushButton_1, &QPushButton::clicked, this,  [=](){ ui.display->inputDigit('1'); } ); 
    connect( ui.pushButton_2, &QPushButton::clicked, this,  [=](){ ui.display->inputDigit('2'); } ); 
    connect( ui.pushButton_3, &QPushButton::clicked, this,  [=](){ ui.display->inputDigit('3'); } ); 
    connect( ui.pushButton_4, &QPushButton::clicked, this,  [=](){ ui.display->inputDigit('4'); } ); 
    connect( ui.pushButton_5, &QPushButton::clicked, this,  [=](){ ui.display->inputDigit('5'); } ); 
    connect( ui.pushButton_6, &QPushButton::clicked, this,  [=](){ ui.display->inputDigit('6'); } ); 
    connect( ui.pushButton_7, &QPushButton::clicked, this,  [=](){ ui.display->inputDigit('7'); } ); 
    connect( ui.pushButton_8, &QPushButton::clicked, this,  [=](){ ui.display->inputDigit('8'); } ); 
    connect( ui.pushButton_9, &QPushButton::clicked, this,  [=](){ ui.display->inputDigit('9'); } ); 
    connect( ui.pushButton_A, &QPushButton::clicked, this,  [=](){ ui.display->inputDigit('A'); } ); 
    connect( ui.pushButton_B, &QPushButton::clicked, this,  [=](){ ui.display->inputDigit('B'); } ); 
    connect( ui.pushButton_C, &QPushButton::clicked, this,  [=](){ ui.display->inputDigit('C'); } ); 
    connect( ui.pushButton_D, &QPushButton::clicked, this,  [=](){ ui.display->inputDigit('D'); } ); 
    connect( ui.pushButton_E, &QPushButton::clicked, this,  [=](){ ui.display->inputDigit('E'); } ); 
    connect( ui.pushButton_F, &QPushButton::clicked, this,  [=](){ ui.display->inputDigit('F'); } ); 

    connect( ui.pushButton_Add,     &QPushButton::clicked, this,  [=](){ this->inputOperator(EOperator::PLUS); } ); 
    connect( ui.pushButton_Subs,    &QPushButton::clicked, this,  [=](){ this->inputOperator(EOperator::MINUS); } ); 
    connect( ui.pushButton_Mul,     &QPushButton::clicked, this,  [=](){ this->inputOperator(EOperator::MULT); } ); 
    connect( ui.pushButton_Div,     &QPushButton::clicked, this,  [=](){ this->inputOperator(EOperator::DIV); } ); 
    connect( ui.pushButton_Mod,     &QPushButton::clicked, this,  [=](){ this->inputOperator(EOperator::MODULO); } ); 
    connect( ui.pushButton_LShft,   &QPushButton::clicked, this,  [=](){ this->inputOperator(EOperator::LSHFT); } ); 
    connect( ui.pushButton_RShft,   &QPushButton::clicked, this,  [=](){ this->inputOperator(EOperator::RSHFT); } ); 

    connect( ui.pushButton_ChSign,  &QPushButton::clicked, this,  [=](){ this->inputOperatorInPlace(EOperator::CHSIGN); } ); 
    connect( ui.pushButton_Sqr,     &QPushButton::clicked, this,  [=](){ this->inputOperatorInPlace(EOperator::SQR); } ); 
    connect( ui.pushButton_Root,    &QPushButton::clicked, this,  [=](){ this->inputOperatorInPlace(EOperator::ROOT); } ); 
    connect( ui.pushButton_Fact,    &QPushButton::clicked, this,  [=](){ this->inputOperatorInPlace(EOperator::FACTOR); } ); 
    //connect( ui.pushButton_Cmpl,    &QPushButton::clicked, this,  [=](){ this->inputOperatorInPlace(EOperator::COMPL); } ); 

    connect( ui.pushButton_Run,     &QPushButton::clicked, this,  &CalculatorForm::on_equal ); 
    connect( ui.pushButton_Clear,   &QPushButton::clicked, this,  &CalculatorForm::on_clear ); 

    connect( ui.display, &Display::baseChanged, this,  &CalculatorForm::on_baseChanged ); 


    //connect( ui.pushButton_Unsigned, &QPushButton::toggled, this,  [=](bool b){ ui.pushButton_Signed->setChecked(!b); } ); 
    //connect( ui.pushButton_Signed,   &QPushButton::toggled, this,   [=](bool b){ ui.pushButton_Unsigned->setChecked(!b); } ); 
    //connect( ui.pushButton_Signed,   &QPushButton::toggled, this,   [=](bool b){ ui.comboBox_BitLength->setDisabled(b); } ); 

    //ui.pushButton_Signed->toggle();
}


void    CalculatorForm::on_baseChanged( EBase base)
{
    switch ( base)
    {
    case EBase::BIN:
        ui.pushButton_0->setEnabled(true);
        ui.pushButton_1->setEnabled(true);
        ui.pushButton_2->setDisabled(true);
        ui.pushButton_3->setDisabled(true);
        ui.pushButton_4->setDisabled(true);
        ui.pushButton_5->setDisabled(true);
        ui.pushButton_6->setDisabled(true);
        ui.pushButton_7->setDisabled(true);
        ui.pushButton_8->setDisabled(true);
        ui.pushButton_9->setDisabled(true);
        ui.pushButton_A->setDisabled(true);
        ui.pushButton_B->setDisabled(true);
        ui.pushButton_C->setDisabled(true);
        ui.pushButton_D->setDisabled(true);
        ui.pushButton_E->setDisabled(true);
        ui.pushButton_F->setDisabled(true);
        break;

    case EBase::DEC:
        ui.pushButton_0->setEnabled(true);
        ui.pushButton_1->setEnabled(true);
        ui.pushButton_2->setEnabled(true);
        ui.pushButton_3->setEnabled(true);
        ui.pushButton_4->setEnabled(true);
        ui.pushButton_5->setEnabled(true);
        ui.pushButton_6->setEnabled(true);
        ui.pushButton_7->setEnabled(true);
        ui.pushButton_8->setEnabled(true);
        ui.pushButton_9->setEnabled(true);
        ui.pushButton_A->setDisabled(true);
        ui.pushButton_B->setDisabled(true);
        ui.pushButton_C->setDisabled(true);
        ui.pushButton_D->setDisabled(true);
        ui.pushButton_E->setDisabled(true);
        ui.pushButton_F->setDisabled(true);
        break;

    case EBase::HEX:
        ui.pushButton_0->setEnabled(true);
        ui.pushButton_1->setEnabled(true);
        ui.pushButton_2->setEnabled(true);
        ui.pushButton_3->setEnabled(true);
        ui.pushButton_4->setEnabled(true);
        ui.pushButton_5->setEnabled(true);
        ui.pushButton_6->setEnabled(true);
        ui.pushButton_7->setEnabled(true);
        ui.pushButton_8->setEnabled(true);
        ui.pushButton_9->setEnabled(true);
        ui.pushButton_A->setEnabled(true);
        ui.pushButton_B->setEnabled(true);
        ui.pushButton_C->setEnabled(true);
        ui.pushButton_D->setEnabled(true);
        ui.pushButton_E->setEnabled(true);
        ui.pushButton_F->setEnabled(true);
        break;
    }

    QString sexpr = calc.getExpresion( ui.display->getBase() );
    ui.display->setExpresion( sexpr /*+ ui.display->getCurArg()*/ );
}

void    CalculatorForm::on_clear()
{
    calc.reset();
    ui.display->reset();
}

void    CalculatorForm::on_equal()
{
    calc.pushArgOper( ui.display->getCurArg(), EOperator::EVAL, ui.display->getBase() );

    QString sexpr = calc.getExpresion( ui.display->getBase() );
    QString res = calc.Evaluate();

    //ui.display->setExpresion( sexpr + ui.display->getCurArg() + QString( " =" ) );
    ui.display->setExpresion( sexpr );

    if ( res != QString("") )
        ui.display->setMainValue( ConvertTo( res, calc.getBase(), ui.display->getBase()) );
}


void    CalculatorForm::keyPressEvent(QKeyEvent *event)
{
    char c = event->key();
    if ( c >= '0' && c <= '9' && ( ui.display->getBase() == EBase::DEC || ui.display->getBase() == EBase::HEX) )
        ui.display->inputDigit( c );

    if ( c >= 'A' && c <= 'F' && (ui.display->getBase() == EBase::HEX) )
        ui.display->inputDigit( c );

    if ( c >= '0' && c <= '1' && (ui.display->getBase() == EBase::BIN) )
        ui.display->inputDigit( c );
}

void    CalculatorForm::inputOperator( EOperator opr)
{
    calc.pushArgOper( ui.display->getCurArg(), opr, ui.display->getBase() );
    ui.display->startCurArg();

    QString sexpr = calc.getExpresion( ui.display->getBase() );
    ui.display->setExpresion( sexpr);
}


void    CalculatorForm::inputOperatorInPlace( EOperator opr)
{
    //std::string res = calc.pushArgOper( ui.display->getCurArg(), opr, ui.display->getBase() );

    QString sarg = ui.display->getCurArg();
    sarg = calc.EvaluateInPlace( sarg, opr, ui.display->getBase() );

    ui.display->setMainValue( sarg);
    ui.display->startCurArg();
}
