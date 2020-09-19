#include <QVBoxLayout>
#include <QLineEdit>

#include "display.h"


void ArgString_Separ( std::string& arg, size_t count, char separ)
{
	int64_t insertPosition = arg.length() - count;
    int64_t minpos = 0;
    if ( arg.length() > 0 )
        if ( arg.front() == '-' || arg.back() == '+' )
            minpos = 1;

	while (insertPosition > minpos) 
	{
        arg.insert( insertPosition, std::string({separ}) );
		insertPosition -= count;
	}
}


Display::Display(QWidget *parent) : QWidget(parent)
{
    bAsUnsigned = false;
    curSize = 0;
    //argSizeLimit = 0;

    ui.setupUi(this);

    connect( ui.radioButton_Bin, &QRadioButton::toggled, this,  [=](bool ch){ this->setBase(EBase::BIN, ch); } ); 
    connect( ui.radioButton_Dec, &QRadioButton::toggled, this,  [=](bool ch){ this->setBase(EBase::DEC, ch); } ); 
    connect( ui.radioButton_Hex, &QRadioButton::toggled, this,  [=](bool ch){ this->setBase(EBase::HEX, ch); } ); 

    connect( ui.pushButton_Unsigned, &QPushButton::toggled, this,  &Display::on_asUnsigned ); 

    //connect( this, &Display::baseChanged, ui.textEdit_Display,  &MultiDisplay::on_baseChanged ); 

    ui.pushButton_Unsigned->setText( "as signed");
    ui.labelSize->setText("");

    ui.radioButton_Dec->setChecked(true);
    curBase = EBase::DEC;
    bresetArg = true;

    curExpr = "";
	curArgument = "0";

    ui.textEdit_Display->setText( QString(curArgument.c_str()) );


    QFont font;
    font.setStyleHint( QFont::TypeWriter );
    ui.textEdit_Display->setCurrentFont(font);
    ui.textEdit_Display->setAlignment( Qt::AlignRight);

    fmtDefault = ui.textEdit_Display->currentCharFormat();
}

void    Display::on_asUnsigned( bool b)
{
    bAsUnsigned = b;
    update();
    if ( bAsUnsigned )
    {
        ui.labelSize->setText(QString(" ") + QString::number(curSize) + QString(" B") );
        ui.pushButton_Unsigned->setText( "as unsigned");
    }
    else
    {
        ui.labelSize->setText("");
        ui.pushButton_Unsigned->setText( "as signed");
    }

}

QString    Display::convertArgToDisplay( const std::string& arg, EBase base)
{
    std::string rstr = arg;
    switch ( base)
    {
    case EBase::BIN:
    case EBase::HEX:
        ArgString_Separ( rstr, 4, ' ');
        break;

    case EBase::DEC:
        ArgString_Separ( rstr, 3, ',');
        break;
    };

    return QString( rstr.c_str());
}

void    Display::setBase( EBase base, bool check)
{
    if ( check )
    {
        //update curExpr
        curArgument = ConvertTo( curArgument, curBase, base);
        curBase = base;

        update();
        
        emit baseChanged( curBase);
    }
}

void    Display::update()
{
    ui.textEdit_Display->setAlignment( Qt::AlignRight);
    //ui.textEdit_Display->setText( convertArgToDisplay( curArgument, curBase) );

    ui.textEdit_Display->setText( QString(curExpr.c_str()) );
    ui.textEdit_Display->append( "");

    ui.textEdit_Display->setFontPointSize(18);
    ui.textEdit_Display->setAlignment( Qt::AlignRight);

    std::string qstr; 
    //std::string sarg_bin, sarg_dec, sarg_hex;

    if ( bAsUnsigned)
    {
        curSize = ToUnsigned( qstr, curArgument, curBase);
        ui.labelSize->setText(QString(" ") + QString::number(curSize) + QString(" Byte") );

    }
    else
    {
        qstr = curArgument;
        ui.labelSize->setText("");
    }

    ui.textEdit_Display->append( convertArgToDisplay( qstr, curBase));

    QTextCursor cur = ui.textEdit_Display->textCursor();
    cur.setCharFormat( fmtDefault);
    ui.textEdit_Display->setTextCursor( cur);

    std::string sarg_bin = ConvertTo( qstr, curBase, EBase::BIN);
    std::string sarg_dec = ConvertTo( qstr, curBase, EBase::DEC);
    std::string sarg_hex = ConvertTo( qstr, curBase, EBase::HEX);

    ui.lineEdit_DispBin->setText( convertArgToDisplay( sarg_bin, EBase::BIN) );
    ui.lineEdit_DispDec->setText( convertArgToDisplay( sarg_dec, EBase::DEC) );
    ui.lineEdit_DispHex->setText( convertArgToDisplay( sarg_hex, EBase::HEX) );

    //if ( bAsUnsigned)
    //{
    //    std::string qstr; 
    //    curSize = ToUnsigned( qstr, curArgument, curBase);
    //    ui.textEdit_Display->append( convertArgToDisplay( qstr, curBase));
    //    ui.labelSize->setText(QString(" ") + QString::number(curSize) + QString(" B") );

    //}
    //else
    //{
    //    ui.textEdit_Display->append( convertArgToDisplay( curArgument, curBase));
    //    ui.labelSize->setText("");
    //}

    //QTextCursor cur = ui.textEdit_Display->textCursor();
    //cur.setCharFormat( fmtDefault);
    //ui.textEdit_Display->setTextCursor( cur);

    //std::string sarg_bin = ConvertTo( curArgument, curBase, EBase::BIN);
    //std::string sarg_dec = ConvertTo( curArgument, curBase, EBase::DEC);
    //std::string sarg_hex = ConvertTo( curArgument, curBase, EBase::HEX);

    //ui.lineEdit_DispBin->setText( convertArgToDisplay( sarg_bin, EBase::BIN) );
    //ui.lineEdit_DispDec->setText( convertArgToDisplay( sarg_dec, EBase::DEC) );
    //ui.lineEdit_DispHex->setText( convertArgToDisplay( sarg_hex, EBase::HEX) );

}


void    Display::inputDigit( char c)
{
    std::string sarg;
    if( bresetArg)
    {
        sarg = "";
        bresetArg = false;
    }
    else
    {
        sarg = curArgument;
    }

	//sarg = sarg + QString( c);

    //if ( argSizeLimit > 0 )
    //{
    //    if ( TestSize( sarg + c, argSizeLimit, curBase ) )
    //        sarg += c;
    //}
    //else
    {
        sarg += c;
    }

    //curExpr += c;
    curArgument = ConvertTo( sarg, curBase, curBase);
    update();
}
