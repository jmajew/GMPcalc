#ifndef __CALCULATOR_H__
#define __CALCULATOR_H__

#include <iostream>
#include <string>
#include <vector>

#include <QString>
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

inline QString mpzToQString( const mpz_t& q, EBase base)
{
	size_t n = mpz_sizeinbase(q, (int)base) + 2;
	char *ptab = new char[n];
	mpz_get_str( ptab, -(int)base, q);
	QString rstr( ptab);

	delete [] ptab;

	return rstr;
}

inline bool TestSize( const QString& arg, size_t size, EBase base)
{
    mpz_t q;
    mpz_init( q);
    mpz_set_str( q, arg.toLocal8Bit().constData(), (int)base);

	if ( mpz_sizeinbase(q,2) > size)
		return false;

	return true;
}

inline QString ConvertTo( const QString& arg, EBase ibase, EBase obase)
{
    mpz_t q;
    mpz_init( q);
    mpz_set_str( q,  arg.toLocal8Bit().constData(), (int)ibase);
	QString rstr = mpzToQString( q, obase);
	mpz_clear( q);

	return rstr;
}


inline mp_bitcnt_t ToUnsigned( QString& rstr,  const QString& arg, EBase base)
{
    mpz_t q, r;
	mpz_t mask;
	mpz_init( mask);
    mpz_init( q);
    mpz_init( r);
    mpz_set_str( q,  arg.toLocal8Bit().constData(), (int)base);

	size_t bitq = mpz_sizeinbase(q, 2);
	mp_bitcnt_t sizebit = static_cast<mp_bitcnt_t>( (bitq / 32 + 1) * 32 );

	if ( mpz_sgn( q) < 0 )
	{
		for ( mp_bitcnt_t i=0; i<sizebit; ++i)
			mpz_setbit( mask, i);

		mpz_neg( q, q);
		mpz_xor( r, q, mask);
		mpz_add_ui( q, r, 1);
		

		rstr = mpzToQString( q, base);
	}
	else
	{
		//mpz_setbit( q, sizebit);
		rstr = mpzToQString( q, base);
		//rstr.remove(0, 1); 
	}

	mpz_clear( mask);
	mpz_clear( q);
	mpz_clear( r);

	return sizebit/8;
}

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
	bool		IsValid() const	{ return (mId > 0 || mValue != ""); }

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

	int		Create( std::string sxp, int idex = 0, int pos=0);
	void	Reset();

	std::string	Eval(int idex=0);
	std::string	ExprToString(EBase ibase, EBase obase, int idex=0) const;

	void		Dump(int idex=0) const;
	std::string	DumpExpr(int idex=0) const;

private:
	//void CloneStack();

private:
	std::vector< std::vector<ArgOp> >	mstack;
};




///////////////////////////////////////////////////////////////////////////////////////////////////
class Calc
{
public:
	Calc() : mbase(EBase::HEX), mstr(""), mbend(false)		{}

	void		reset()							{ mExpr.Reset(); }
    EBase       getBase() const					{ return mbase; }

	QString		getExpresion( EBase base) const;

	void	pushArgOper( const QString& arg , EOperator opr, EBase base);
	//void	pushOperator( const QString& arg);


	void	StartSubExpr();
	void	FinishSubExpr();

	QString	Evaluate();
	QString	EvaluateInPlace( const QString& a, EOperator opr, EBase base);

	//QString	EvaluateSingle( const QString& a, EOperator opr, const QString& b );

private:
	EBase			mbase;

	bool			mbend;
	std::string		mstr;

	Expression		mExpr;

};

#endif // __CALCULATOR_H__