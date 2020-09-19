#ifndef __CALCULATOR_H__
#define __CALCULATOR_H__

#include <iostream>
#include <string>
#include <vector>

#include "mini-gmp.h"

enum class EBase
{
	UNKNOWN	= 0,
	BIN		= 2,
	DEC		= 10,
	HEX		= 16,
};


enum class EOperator
{
	UNKNOWN	= 0,
// 2 args oper
	PLUS,
	MINUS,
	MULT,
	DIV,
	MODULO,
	LSHFT,
	RSHFT,
	OR,
	AND,
	NOR,
	XOR,
	NAND,
// 1 arg oper
	NOT,
	CHSIGN,
	COMPL,
	SQR,
	ROOT,
	FACTOR,
	EVAL,
};

void RemoveChar( std::string& str, const std::string& schar);

int			OperPriority( EOperator opr);
std::string OperToString( EOperator opr);
EOperator	StringToOper( std::string str);


std::string ConvertTo( const std::string& arg, EBase ibase, EBase obase);
mp_bitcnt_t ToUnsigned( std::string& rstr, const std::string& arg, EBase base);

//bool		TestSize( const std::string& arg, size_t size, EBase base);


std::string	EvaluateOne( const std::string& a, EOperator opr, EBase base=EBase::HEX);
std::string EvaluateTwo( const std::string& al, const std::string& ar, EOperator op, EBase base=EBase::HEX);


///////////////////////////////////////////////////////////////////////////////////////////////////
class Operator
{
public:
	Operator( EOperator o);

public:
	EOperator	op;
	int			prio;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
class Argument
{
public:
	Argument( int id=-1) : mId(id), mValue("")				{}
	Argument( const std::string& a) : mId(-1), mValue(a)	{}

	bool		IsExpr() const	{ return (mId > 0 ); }
	bool		IsValid() const	{ return (mValue != ""); }
	
public:
	int	mId;
	std::string	mValue;
};


///////////////////////////////////////////////////////////////////////////////////////////////////
class Expression
{
public:
	using ArgOp = std::pair< Argument, Operator >;


	Expression()		{ mstack.resize(1); }

	int		Create( std::string sxp, int idex = 0);
	void	Reset();

	std::string	Eval(int idex=0);
	std::string	ExprToString(EBase ibase, EBase obase, int idex=0) const;

	void		Dump(int idex=0) const;
	std::string	DumpExpr(int idex=0) const;

private:
	void	Find_ArgOps( std::string& sexp, int idex );
	void	Find_SubExpr( std::string& sexp, int idex );

private:
	std::vector< std::vector<ArgOp> >	mstack;
};



#endif // __CALCULATOR_H__
