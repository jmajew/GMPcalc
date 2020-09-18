#ifndef __CALCULATOR_FORM_H__
#define __CALCULATOR_FORM_H__


#include "ui_calculator_form.h"
#include "calculator.h"


class CalculatorForm : public QWidget
{
    Q_OBJECT

public:
    explicit CalculatorForm( QWidget *parent = nullptr);

private slots:
    void    on_baseChanged( EBase base);
    void    on_equal();
    void    on_clear();

private:
    void    inputOperator( EOperator opr);
    void    inputOperatorInPlace( EOperator opr);


private:
    void    keyPressEvent(QKeyEvent *event);

private:
    Ui::CalculatorForm ui;

    Calc    calc;
};


#endif // __CALCULATOR_FORM_H__

