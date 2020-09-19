#include <regex>

#include "qcalc.h"

void	Calc::pushArgOper( const std::string& arg , EOperator opr, EBase base)
{
	if (mbend)
	{
		mstr = "";
		mbend = false;
	}

	mstr += std::string("[") + ConvertTo( arg, base, mbase ) + std::string("]") + OperToString( opr);
}

void	Calc::pushOper( EOperator opr, EBase base)
{
	if (mbend)
	{
		mstr = "";
		mbend = false;
	}

	mstr += OperToString( opr);
}

void	Calc::StartSubExpr()
{
	if (mbend)
	{
		mstr = "";
		mbend = false;
	}

	++mbraLevel;
	mstr += std::string("(");
}

void	Calc::FinishSubExpr( std::string arg, EBase base)
{
	--mbraLevel;
	if ( arg != "")
		mstr +=  std::string("[") + ConvertTo( arg, base, mbase ) + std::string("]") + std::string(")");
	else
		mstr +=  std::string(")");
}

std::string	Calc::getExpresion( EBase base) const	
{ 
	std::string str = mstr;
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
	//expr.Create(mstr);
	//std::string str = expr.ExprToString( mbase, base);
	//return str; 
}



std::string	Calc::EvaluateInPlace( const std::string& a, EOperator opr, EBase base)
{
	std::string str = EvaluateOne( a, opr, base);
	return str;//QString( str.c_str() );
}

std::string	Calc::Evaluate()			
{
	std::string sexpr = mstr;
	RemoveChar( sexpr, "[]");

	mExpr.Reset();
	mExpr.Create( sexpr);
	mbend = true;
	//mstr = "";

	std::string res = mExpr.Eval();
	return res;

	//QString res( mExpr.Eval().c_str() );
	////ConvertTo( res, mbase, base );
	//return res;
}

