#include <regex>

#include "qcalc.h"

Calc::Calc()
{
	mbase = EBase::HEX;
	reset();
}

void	Calc::reset()							
{ 
	mExpr.Reset(); 
	mbraLevel = 0;
	mstrEval = "";
	mstrShow = "";
	mstrArg = "";
	mbreset = false; // ??
}

void	Calc::resetCond()
{
	if (mbreset)
	{
		mbraLevel = 0;
		mstrEval = "";
		mstrShow = "";
		mstrArg = "";
		mbreset = false;
	}
}

void	Calc::pushArgOper( const std::string& arg , EOperator opr, EBase base)
{
	resetCond();

	if ( mstrArg != "" )
	{
		mstrShow += " " + mstrArg + " " + OperToString( opr);
		mstrArg = "";
	}
	else
	{
		mstrShow += "[" + ConvertTo( arg, base, mbase ) + "]" + OperToString( opr);
	}

	mstrEval += "[" + ConvertTo( arg, base, mbase ) + "]" + OperToString( opr);
}

void	Calc::pushOper( EOperator opr, EBase base)
{
	resetCond();

	mstrEval	+= OperToString( opr);
	mstrShow	+= OperToString( opr);
}

void	Calc::StartSubExpr()
{
	resetCond();

	++mbraLevel;
	mstrEval	+= std::string("(");
	mstrShow	+= std::string("(");
}

void	Calc::FinishSubExpr( std::string arg, EBase base)
{
	--mbraLevel;
	if ( arg != "")
	{
		if ( mstrArg != "" )
		{
			mstrShow += " " + mstrArg + " ])";;
			mstrArg = "";
		}
		else
		{
			mstrShow +=  "[" + ConvertTo( arg, base, mbase ) + "])";
		}

		mstrEval +=  "[" + ConvertTo( arg, base, mbase ) + "])";	
	}
	else
	{
		mstrEval +=  std::string(")");
		mstrShow +=  std::string(")");
	}
}

std::string	Calc::EvaluateInPlace( const std::string& a, EOperator opr, EBase base)
{
	resetCond();

	if ( opr != EOperator::CHSIGN )
	{
		if ( mstrArg == "" )
			mstrArg = OperToString(opr) + "([" + ConvertTo( a, base, mbase ) + "])";
		else
			mstrArg = OperToString(opr) + "(" + mstrArg + ")";
	}

	std::string str = EvaluateOne( a, opr, base);
	return str;//QString( str.c_str() );
}

std::string	Calc::Evaluate()			
{
	std::string sexpr = mstrEval;
	RemoveChar( sexpr, "[]");

	mExpr.Reset();
	mExpr.Create( sexpr);
	mbreset = true;
	//mstrEval = "";

	std::string res = mExpr.Eval();
	return res;

	//QString res( mExpr.Eval().c_str() );
	////ConvertTo( res, mbase, base );
	//return res;
}

std::string	Calc::getExpresion( EBase base) const	
{ 
	std::string str = mstrShow;
	//std::string res = "";

	std::regex rex("\\[([-0-9A-F]+)\\]");
	std::smatch rex_match;

	while ( std::regex_search( str, rex_match, rex) )
	{
		std::string sval = rex_match[1];
		sval = ConvertTo( sval, mbase, base );

		str.replace( rex_match[0].first, rex_match[0].second, sval );
	}

	//if ( mbraLevel > 0 )
	return str;

	//Expression expr;
	//expr.Create(mstrEval);
	//std::string str = expr.ExprToString( mbase, base);
	//return str; 
}


