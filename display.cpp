#include <QVBoxLayout>
#include <QLineEdit>

#include "display.h"


void ArgString_Separ( QString& arg, size_t count, char separ)
{
	int64_t insertPosition = arg.length() - count;
    int64_t minpos = 0;
    if ( arg.startsWith('-') || arg.startsWith('+') )
        minpos = 1;

	while (insertPosition > minpos) 
	{
		arg.insert( insertPosition, QString(separ));
		insertPosition -= count;
	}
}


Display::Display(QWidget *parent) : QWidget(parent)
{
    bAsUnsigned = false;
    curSize = 0;
    argSizeLimit = 0;

    ui.setupUi(this);

    connect( ui.radioButton_Bin, &QRadioButton::toggled, this,  [=](bool ch){ this->setBase(EBase::BIN, ch); } ); 
    connect( ui.radioButton_Dec, &QRadioButton::toggled, this,  [=](bool ch){ this->setBase(EBase::DEC, ch); } ); 
    connect( ui.radioButton_Hex, &QRadioButton::toggled, this,  [=](bool ch){ this->setBase(EBase::HEX, ch); } ); 

    connect( ui.pushButton_Unsigned, &QPushButton::toggled, this,  &Display::on_asUnsigned ); 

    //connect( this, &Display::baseChanged, ui.textEdit_Display,  &MultiDisplay::on_baseChanged ); 

    ui.labelSize->setText("");

    ui.radioButton_Dec->setChecked(true);
    calcBase = EBase::DEC;
    bStart = true;
    curExpr = "";
	curArgument = "";
    ui.textEdit_Display->setText( curArgument);


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
        ui.labelSize->setText(QString(" ") + QString::number(curSize) + QString(" B") );
    else
        ui.labelSize->setText("");

}

QString    Display::convertArgToDisplay( const QString& arg, EBase base)
{
    QString rstr = arg;
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

    return rstr;
}

void    Display::setBase( EBase base, bool check)
{
    if ( check )
    {
        //update curExpr
        curArgument = ConvertTo( curArgument, calcBase, base);
        calcBase = base;

        update();
        
        emit baseChanged( calcBase);
    }
}

void    Display::update()
{
    ui.textEdit_Display->setAlignment( Qt::AlignRight);
    //ui.textEdit_Display->setText( convertArgToDisplay( curArgument, calcBase) );

    ui.textEdit_Display->setText( curExpr );
    ui.textEdit_Display->append( "");

    ui.textEdit_Display->setFontPointSize(18);
    ui.textEdit_Display->setAlignment( Qt::AlignRight);

    if ( bAsUnsigned)
    {
        QString qstr; 
        curSize = ToUnsigned(qstr, curArgument, calcBase);
        ui.textEdit_Display->append( convertArgToDisplay( qstr, calcBase));
        ui.labelSize->setText(QString(" ") + QString::number(curSize) + QString(" B") );

    }
    else
    {
        ui.textEdit_Display->append( convertArgToDisplay( curArgument, calcBase));
        ui.labelSize->setText("");
    }

    QTextCursor cur = ui.textEdit_Display->textCursor();
    cur.setCharFormat( fmtDefault);
    ui.textEdit_Display->setTextCursor( cur);

    QString sarg_bin = ConvertTo( curArgument, calcBase, EBase::BIN);
    QString sarg_dec = ConvertTo( curArgument, calcBase, EBase::DEC);
    QString sarg_hex = ConvertTo( curArgument, calcBase, EBase::HEX);

    ui.lineEdit_DispBin->setText( convertArgToDisplay( sarg_bin, EBase::BIN) );
    ui.lineEdit_DispDec->setText( convertArgToDisplay( sarg_dec, EBase::DEC) );
    ui.lineEdit_DispHex->setText( convertArgToDisplay( sarg_hex, EBase::HEX) );

}


void    Display::inputDigit( char c)
{
    QString sarg;
    if( bStart)
    {
        sarg = "";
        bStart = false;
    }
    else
    {
        sarg = curArgument;
    }

	//sarg = sarg + QString( c);

    if ( argSizeLimit > 0 )
    {
        if ( TestSize( sarg + QString( c), argSizeLimit, calcBase ) )
            sarg += c;
    }
    else
    {
        sarg += c;
    }

    curArgument = ConvertTo( sarg, calcBase, calcBase);
    update();
}
