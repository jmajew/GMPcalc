#ifndef __QCALC_WIDGET_H__
#define __QCALC_WIDGET_H__


#include "ui_calculator_form.h"
#include "qcalc.h"



enum class EInputMode
{
    UNKNOWN = 0,
    ARGUMENT,
    OPERATOR,
    BEG_SUBEXPR,
    END_SUBEXPR
};

class QCalcWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QCalcWidget( QWidget *parent = nullptr);

private slots:
    void    on_baseChanged( EBase base);
    void    on_equal();
    void    on_clear();
    void    on_startSExpr();
    void    on_closeSExpr();

private:
    void    inputDigit( char c);
    void    inputOperator( EOperator opr);
    void    inputOperatorInPlace( EOperator opr);


private:
    void    keyPressEvent(QKeyEvent *event);

private:
    Ui::QCalcWidget ui;

    EInputMode  mIMode;
    Calc        calc;
};


#endif // __QCALC_WIDGET_H__

