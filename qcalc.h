#ifndef __QCALC_H__
#define __QCALC_H__

#include <QString>

#include "calculator.h"



///////////////////////////////////////////////////////////////////////////////////////////////////
class Calc
{
public:
	Calc() : mbase(EBase::HEX), mbraLevel(0), mstr(""), mbend(false)		{}

	void		reset()							{ mExpr.Reset(); mstr = ""; }
    EBase       getBase() const					{ return mbase; }
	int			getBraLevel() const				{ return mbraLevel; }

	std::string		getExpresion( EBase base) const;

	void	pushArgOper( const std::string& arg, EOperator opr, EBase base);
	void	pushOper( EOperator opr, EBase base);
	//void	pushOperator( const QString& arg);


	void	StartSubExpr();
	void	FinishSubExpr( std::string arg, EBase base);

	std::string	Evaluate();
	std::string	EvaluateInPlace( const std::string& a, EOperator opr, EBase base);

	//QString	EvaluateSingle( const QString& a, EOperator opr, const QString& b );

private:
	EBase			mbase;
	int				mbraLevel;

	bool			mbend;
	std::string		mstr;

	Expression		mExpr;
};


#endif // __QCALC_H__
