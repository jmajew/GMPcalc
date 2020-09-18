#ifndef __DISPLAY_H__
#define __DISPLAY_H__

//#include <QtWidgets/QWidget>
#include "ui_display_form.h"

#include "calculator.h"


class Display : public QWidget
{
    Q_OBJECT

public:
    explicit Display(QWidget *parent = nullptr);

	const QString&	getCurArg() const	    { return curArgument; }
    EBase           getBase() const         { return calcBase; }

    void    setMainValue( const QString& res)
    {
        curArgument = res;
        update();
    }

    void    setExpresion( const QString& res)
    {
        curExpr = res;
        update();
    }

    void    reset()                 { curArgument = curExpr = ""; update(); }
    void    inputDigit( char c);
    void    startCurArg()           { bStart = true; }
    void    endCurArg();

signals:
    void baseChanged(EBase base);

private slots:
    void    on_asUnsigned( bool b);

private:
    QString convertArgToDisplay( const QString& arg, EBase base);
    void    setBase( EBase base, bool check);
    void    update();

private:
    Ui::DisplayForm ui;

    QTextCharFormat fmtDefault;

    bool    bStart;
    EBase   calcBase;

    bool    bAsUnsigned;
    size_t  curSize;
    size_t  argSizeLimit;   //??????????????
    QString	curArgument;
    QString curExpr;
};

#endif // __DISPLAY_H__
