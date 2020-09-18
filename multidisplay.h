#ifndef __MULTIDISPLAY_H__
#define __MULTIDISPLAY_H__

#include <QString>
#include <QTextEdit>

#include "calculator.h"


class MultiDisplay : public QTextEdit
{
	Q_OBJECT
	
public:
    explicit MultiDisplay(QWidget *parent = nullptr);

	//const QString&	getCurArg() const	{ return curArgument; }
	//void			setCurArg( const QString& str)	
	//{ 
	//	//curArgument = str;
	//	this->setText( str); 
	//}

	//void	AddDigit( char c);

public slots:
    //void    on_baseChanged( EBase base);

private:
	EBase	argBase; 
	
};

#endif // __MULTIDISPLAY_H__
