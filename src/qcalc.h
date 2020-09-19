#ifndef __QCALC_H__
#define __QCALC_H__

#include <QString>

#include "calculator.h"



///////////////////////////////////////////////////////////////////////////////////////////////////
class Calc
{
public:
	Calc();

	void		reset();
    EBase       getBase() const					{ return mbase; }
	int			getBraLevel() const				{ return mbraLevel; }

	std::string		getExpresion( EBase base) const;

	void	pushArgOper( const std::string& arg, EOperator opr, EBase base);
	void	pushOper( EOperator opr, EBase base);

	void	StartSubExpr();
	void	FinishSubExpr( std::string arg, EBase base);

	std::string	Evaluate();
	std::string	EvaluateInPlace( const std::string& a, EOperator opr, EBase base);

private:
	void	resetCond();

private:
	EBase			mbase;
	int				mbraLevel;

	bool			mbreset;

	std::string		mstrEval;	// expr for eval
	std::string		mstrShow;	// expr for show
	std::string		mstrArg;	// inplace arg for show

	Expression		mExpr;
};


#endif // __QCALC_H__
