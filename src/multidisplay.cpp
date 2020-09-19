#include "multidisplay.h"

MultiDisplay::MultiDisplay(QWidget *parent) : QTextEdit(parent)
{
    argBase = EBase::DEC;
}


//void	MultiDisplay::AddDigit( char c)
//{
//	//curArgument = curArgument + QString( c);
//
//	this->setText( curArgument);
//}
//
//
//void    MultiDisplay::on_baseChanged( EBase base)
//{
//    curArgument = ConvertTo( curArgument, argBase, base);
//    argBase = base;
//    this->setCurArg( curArgument);
//}