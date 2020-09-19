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

	const std::string&	getCurArg() const	    { return curArgument; }
    EBase               getBase() const         { return calcBase; }

    void    setMainValue( const std::string& res)
    {
        curArgument = res;
        update();
    }

    void    setExpresion( const std::string& str)
    {
        curExpr = str;
        update();
    }

    void    setStatusLabel( const std::string& str)
    {
        ui.labelStatus->setText( QString( str.c_str() ) );
    }

    void    reset()                 { curArgument = "0"; curExpr = ""; update(); }
    void    update();

    void    inputDigit( char c);
    void    startCurArg()           { bStart = true; bEnd = false; }
    void    endCurArg()             { bEnd = true; }

    bool    isEndCurArg() const    { return bEnd; }

signals:
    void baseChanged(EBase base);

private slots:
    void    on_asUnsigned( bool b);

private:
    QString    convertArgToDisplay( const std::string& arg, EBase base);
    //QString convertArgToDisplay( const QString& arg, EBase base);
    void    setBase( EBase base, bool check);

private:
    Ui::DisplayForm ui;

    QTextCharFormat fmtDefault;

    bool    bStart;
    bool    bEnd;
    EBase   calcBase;

    bool    bAsUnsigned;
    size_t  curSize;
    size_t  argSizeLimit;   //??????????????

    std::string	curArgument;
    std::string curExpr;
};

#endif // __DISPLAY_H__
