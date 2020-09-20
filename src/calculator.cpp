#include <assert.h>

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <regex>

#include "calculator.h"


using std::cout;
using std::endl;

///////////////////////////////////////////////////////////////////////////////////////////////////

class IsChar
{
public:
	IsChar( const std::string& str) : mStr(str)	{}
	bool operator ()( const char& c)	{ return  (find( mStr.begin(), mStr.end(), c) != mStr.end() ); }

private:
	std::string mStr;
};

void RemoveChar( std::string& str, const std::string& schar)
{
	IsChar ischar( schar);
	str.erase( remove_if( str.begin(), str.end(), ischar ), str.end() ); // TODO :: use lambda instead of ischar
}


// removes all blank chars from the 'str'
inline void RemoveBlanks( std::string& str)
{
	RemoveChar( str, std::string(" \t\n\r") );
}
 
///////////////////////////////////////////////////////////////////////////////////////////////////


int OperPriority( EOperator opr)
{
	switch (opr)
	{
	case EOperator::PLUS:
		return 10;

	case EOperator::MINUS:
		return 15;

	case EOperator::MULT:
	case EOperator::DIV:
		return 20;

	case EOperator::MODULO:
		return 25;

	case EOperator::LSHFT:
	case EOperator::RSHFT:
		return 30;

	case EOperator::AND:
	case EOperator::OR:
	case EOperator::XOR:
	case EOperator::NAND:
	case EOperator::NOR:
		return 5;

	case EOperator::EVAL:
		return 0;
	};

	return 0;
}

std::string OperToString( EOperator opr)
{
	switch (opr)
	{
	case EOperator::NOR:
		return std::string( " !|| " );

	case EOperator::NAND:
		return std::string( " !&& " );

	case EOperator::XOR:
		return std::string( " ^^ " );

	case EOperator::OR:
		return std::string( " || " );

	case EOperator::AND:
		return std::string( " && " );

	case EOperator::PLUS:
		return std::string( " + " );

	case EOperator::MINUS:
		return std::string( " - " );

	case EOperator::MULT:
		return std::string( " * " );

	case EOperator::DIV:
		return std::string( " / " );

	case EOperator::MODULO:
		return std::string( " % " );

	case EOperator::LSHFT:
		return std::string( " << " );

	case EOperator::RSHFT:
		return std::string( " >> " );
	
	case EOperator::EVAL:
		return std::string( " = " );

	case EOperator::CHSIGN:
		return std::string( "negate" );

	case EOperator::SQR:
		return std::string( "sqr" );

	case EOperator::ROOT:
		return std::string( "root" );

	case EOperator::FACTOR:
		return std::string( "fact" );
	};

	return "";
}

EOperator StringToOper( std::string str)
{
	EOperator opr;

	if ( str == "+")
	{
		opr = EOperator::PLUS;
	}
	else if ( str == "-")
	{
		opr = EOperator::MINUS;
	}
	else if ( str == "*")
	{
		opr = EOperator::MULT;
	}
	else if ( str == "/")
	{
		opr = EOperator::DIV;
	}
	else if ( str == "%")
	{
		opr = EOperator::MODULO;
	}
	else if ( str == ">>")
	{
		opr = EOperator::RSHFT;
	}
	else if ( str == "<<")
	{
		opr = EOperator::LSHFT;
	}	
	else if ( str == "=")
	{
		opr = EOperator::EVAL;
	}
	else if ( str == "&&")
	{
		opr = EOperator::AND;
	}
	else if ( str == "||")
	{
		opr = EOperator::OR;
	}
	else if ( str == "^^")
	{
		opr = EOperator::XOR;
	}
	else if ( str == "!&&")
	{
		opr = EOperator::NAND;
	}
	else if ( str == "!||")
	{
		opr = EOperator::NOR;
	}
	else if ( str == "=")
	{
		opr = EOperator::EVAL;
	}
	else
	{
		opr = EOperator::UNKNOWN;
	}

	return opr;
}


inline std::string mpzToString( const mpz_t& q, EBase base)
{
	size_t n = mpz_sizeinbase(q, (int)base) + 2;
	char *ptab = new char[n];
	mpz_get_str( ptab, -(int)base, q);
	std::string rstr( ptab);

	delete [] ptab;

	return rstr;
}

 bool TestSize( const std::string& arg, size_t size, EBase base)
{
    mpz_t q;
    mpz_init( q);
    mpz_set_str( q, arg.c_str(), (int)base);

	if ( mpz_sizeinbase(q,2) > size)
		return false;

	return true;
}

 std::string ConvertTo( const std::string& arg, EBase ibase, EBase obase)
{
    mpz_t q;
    mpz_init( q);
    mpz_set_str( q,  arg.c_str(), (int)ibase);
	std::string rstr = mpzToString( q, obase);
	mpz_clear( q);

	return rstr;
}


 mp_bitcnt_t ToUnsigned( std::string& rstr,  const std::string& arg, EBase base)
{
	const int MIN_LENGTH = 16;

    mpz_t q, r;
	mpz_t mask;
	mpz_init( mask);
    mpz_init( q);
    mpz_init( r);
    mpz_set_str( q,  arg.c_str(), (int)base);

	size_t bitq = mpz_sizeinbase(q, 2);
	mp_bitcnt_t sizebit = static_cast<mp_bitcnt_t>( (bitq / MIN_LENGTH + 1) * MIN_LENGTH );

	if ( mpz_sgn( q) < 0 )
	{
		for ( mp_bitcnt_t i=0; i<sizebit; ++i)
			mpz_setbit( mask, i);

		mpz_neg( q, q);
		mpz_xor( r, q, mask);
		mpz_add_ui( q, r, 1);
		

		rstr = mpzToString( q, base);
	}
	else
	{
		//mpz_setbit( q, sizebit);
		rstr = mpzToString( q, base);
		//rstr.remove(0, 1); 
	}

	mpz_clear( mask);
	mpz_clear( q);
	mpz_clear( r);

	return sizebit/8;
}


///////////////////////////////////////////////////////////////////////////////////////////////////

//std::string	EvaluateOne( const std::string& a, EOperator opr, EBase base=EBase::HEX)
std::string	EvaluateOne( const std::string& a, EOperator opr, EBase base)
{
	mpz_t ta, tc;
	mpz_init( ta);
	mpz_init( tc);
	mpz_set_str( ta, a.c_str(), (int)base );

	switch (opr)
	{
	case EOperator::CHSIGN:
		{
			mpz_neg( tc, ta);
			break;
		}
	case EOperator::SQR:
		{
			mpz_mul( tc, ta, ta);
			break;
		}
	case EOperator::ROOT:
		{
			if ( mpz_sgn( ta) > 0 )
				mpz_sqrt( tc, ta);
			else
				return "!";	

			break;
		}
	case EOperator::FACTOR:
		{
			unsigned long n = mpz_get_ui(ta);
			if ( n <= 5000 && n >= 0 )
				mpz_fac_ui( tc, n);
			else
				return "!";

			break;
		}
	case EOperator::NOT:
		{
			mp_bitcnt_t nbit = mpz_sizeinbase(ta, 2);
			mpz_set_ui( tc, 0);
			mpz_setbit( tc, nbit);
			mpz_sub_ui( tc, tc, 1);	
			mpz_xor( tc, ta, tc);

			break;
		}

	};

	std::string res = mpzToString( tc, base);

    mpz_clear(ta);
    mpz_clear(tc);

	return res;
}

//std::string EvaluateTwo( const std::string& al, const std::string& ar, EOperator op, EBase base=EBase::HEX)
std::string EvaluateTwo( const std::string& al, const std::string& ar, EOperator op, EBase base)
{
	//EBase base = EBase::HEX;

	mpz_t ta, tb, tc;
	mpz_init(ta);
	mpz_init(tb);
	mpz_init(tc);

	mpz_set_str( ta, al.c_str(), (int)base );
	mpz_set_str( tb, ar.c_str(), (int)base );

	switch (op)
	{
	case EOperator::PLUS:
		mpz_add( tc, ta, tb);
		break;

	case EOperator::MINUS:
		mpz_sub( tc, ta, tb);
		break;

	case EOperator::MULT:
		mpz_mul( tc, ta, tb);
		break;

	case EOperator::DIV:
		mpz_tdiv_q( tc, ta, tb);
		break; 

	case EOperator::MODULO:
		mpz_tdiv_r( tc, ta, tb);
		break; 

	case EOperator::LSHFT:
		{
			unsigned long shift = mpz_get_ui( tb);
			mpz_mul_2exp( tc , ta , shift);
			break;
		}

	case EOperator::RSHFT:
		{
			unsigned long shift = mpz_get_ui( tb);
			mpz_tdiv_q_2exp( tc , ta , shift);
			break;
		}

	case EOperator::AND:
		{
			mpz_and( tc, ta, tb);
			break;
		}
	case EOperator::NAND:
		{
			mpz_and( tc, ta, tb);

			mp_bitcnt_t nbit = mpz_sizeinbase(tc, 2);
			mpz_set_ui( tb, 0);
			mpz_setbit( tb, nbit);
			mpz_sub_ui( tb, tb, 1);	
			mpz_xor( tc, tc, tb);
			break;
		}
	case EOperator::OR:
		{
			mpz_ior( tc, ta, tb);
			break;
		}
	case EOperator::XOR:
		{
			mpz_xor( tc, ta, tb);
			break;
		}
	case EOperator::NOR:
		{
			mpz_ior( tc, ta, tb);

			mp_bitcnt_t nbit = mpz_sizeinbase(tc, 2);
			mpz_set_ui( tb, 0);
			mpz_setbit( tb, nbit);
			mpz_sub_ui( tb, tb, 1);	
			mpz_xor( tc, tc, tb);
			break;
		}
	};

	std::string res = mpzToString( tc, base);

    mpz_clear(ta);
    mpz_clear(tb);
    mpz_clear(tc);

	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
Operator::Operator( EOperator o) : op(o)	
{ 
	prio = OperPriority(op); 
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void Expression::Reset()
{
	mstack.clear();
	mstack.resize(1);
}


void Expression::Find_ArgOps( std::string& sexp, int idex )
{
	std::regex rex( "^([\\+\\-]?[0-9A-F]+|#[0-9]+)(\\+|\\-|/|\\*|<<|>>|=|&&|\\|\\||!&&|!\\|\\||\\^\\^|\\%)" );
	std::smatch rex_match;

	while ( std::regex_search( sexp, rex_match, rex) )
	{
		//cout << rex_match[1] << " :::: "  << rex_match[2] << endl;
		std::string sval = rex_match[1];
		
		Argument arg;
		if (sval.front() == '#')
		{
			sval.erase( sval.begin() );
			int id = std::stoi( sval);
			arg = Argument( id);
		}
		else
		{
			arg = Argument( sval);
		}

		mstack[idex].push_back( ArgOp( arg, StringToOper( rex_match[2]) ) );

		sexp.erase( rex_match[0].first, rex_match[0].second);
		//cout << sexp << endl;
	}
}

void Expression::Find_SubExpr( std::string& sexp, int idex )
{
	std::regex rex( "\\(([^\\(\\)]+)\\)" );

	std::smatch rex_match;

	while ( std::regex_search( sexp, rex_match, rex) )
	{
		//cout << rex_match[1] << endl;

		size_t id = mstack.size();
		mstack.resize( id+1 );

		std::string newsexp = rex_match[1];
		newsexp += "=";
		Create( newsexp, id);

		std::string sid = std::string("#") + std::to_string(id);		// temp subexpr ref "#id"
		sexp.replace( rex_match[0].first, rex_match[0].second, sid );
		
		//cout << sexp << endl;
	}
}


int	Expression::Create( std::string sexp, int idex)
{
	//Reset();
	RemoveBlanks( sexp);

	Find_SubExpr( sexp, idex);
	Find_ArgOps( sexp, idex);

	return 0;
}


//int	Expression::Create_Old( std::string sxp, int idex, int pos)
//{
//	RemoveBlanks( sxp);
//
//	Argument	curarg;
//	EOperator	opr = EOperator::UNKNOWN;
//	std::string sarg = "";
//
//	int mode = 10;
//	bool bstart = true;
//	std::string sign = "";
//
//	while ( pos < static_cast<int>(sxp.length()) )
//	{
//		char c = sxp[pos];
//
//		if ( c == ')' )
//		{
//			if ( sarg != "" )
//			{
//				sarg = sign + sarg;
//				curarg.mId = -1;
//				curarg.mValue = sarg;
//			}
//
//			mstack[idex].push_back( ArgOp( curarg, EOperator::EVAL) );
//			return pos+1;
//		}
//
//		if ( mode == 10) // argument
//		{
//			if ( bstart)
//			{
//				if ( c == '-' )
//				{
//					sarg = "-";
//					++pos;
//				}
//				bstart = false;
//			}
//			else
//			//if ( c>='0' && c<='9' )
//			if ( ( c>='0' && c<='9' ) || (c>='A' && c<='F') )
//			{
//				//barg = false;
//				sarg += c;
//				++pos;
//			}
//			else
//			if  ( c == '(' )
//			{
//				curarg.mId = static_cast<int>( mstack.size() );
//				curarg.mValue = "";
//				mstack.resize( mstack.size() + 1);
//
//				pos = Create_Old( sxp, curarg.mId, pos+1);
//				
//				sarg = "";
//				sign = "";
//				mode = 11;
//			}
//			else
//			{
//				sarg = sign + sarg;
//				curarg.mId = -1;
//				curarg.mValue = sarg;
//
//				sarg = "";
//				sign = "";
//				mode = 11;
//			}
//
//			continue;
//		}
//		else if ( mode == 11) // operator
//		{
//			opr = CharToOper( c);
//
//			if ( opr != EOperator::UNKNOWN)
//			{
//				if ( curarg.IsValid() )
//				{
//					mstack[idex].push_back( ArgOp( curarg, opr) );
//					opr = EOperator::UNKNOWN;
//					mode = 10;
//					bstart = true;
//				}
//			}
//		}
//
//		++pos;
//	}
//
//	return pos;
//}

std::string	Expression::Eval(int idex)
{
	if ( mstack[0].empty() )
		return "";

	do
	{
		for ( auto itr=mstack[idex].begin(); (itr+1)!=mstack[idex].end(); )
		{
			auto itrnxt = itr+1;
			auto itrprv = (itr==mstack[idex].begin() ? itr : itr-1);
			
			if ( itr->second.prio >= itrnxt->second.prio && itr->second.prio >= itrprv->second.prio )
			{
				if ( itr->first.IsExpr() )
					itr->first = Argument( Eval(itr->first.mId) );

				if ( itrnxt->first.IsExpr() )
					itrnxt->first = Argument( Eval(itrnxt->first.mId) );

				std::string sarg = EvaluateTwo( itr->first.mValue, itrnxt->first.mValue, itr->second.op );
				itrnxt->first = Argument( sarg);

				itr = mstack[idex].erase( itr);

				//Dump(); cout << endl;
			}
			else
			{
				++itr;
			}
		}
	}
	while ( mstack[idex].size() > 1);

	return mstack[idex].front().first.mValue;
}
	
std::string	Expression::ExprToString(EBase ibase, EBase obase, int idex) const
{
	std::string str = "";

	for ( const auto& e : mstack[idex])
	{
		if ( e.first.IsExpr() )
			str += std::string( "(") + DumpExpr( e.first.mId) + std::string( ")");
		else
			str += ConvertTo( e.first.mValue, ibase, obase);

		str += OperToString( e.second.op);
	}

	return str;
}

std::string Expression::DumpExpr(int idex) const
{
	std::string str = "";

	for ( const auto& e : mstack[idex])
	{
		if ( e.first.IsExpr() )
			str += std::string( "(") + DumpExpr( e.first.mId) + std::string( ")");
		else
			str += e.first.mValue;

		if ( e.second.op != EOperator::EVAL )
			str += OperToString( e.second.op);
	}

	return str;
}

void Expression::Dump(int idex) const
{
	cout << "(";
	for ( const auto& e : mstack[idex])
	{
		if ( e.first.IsExpr() )
			this->Dump( e.first.mId);
		else
			cout << e.first.mValue;

		cout << OperToString( e.second.op);
	}
	cout << ")";
}




///////////////////////////////////////////////////////////////////////////////////////////////////

//
//int main()
//{
//	std::string sexpr = "21 + 13 - 40*2 + 1 - 3*2 + 9";
//	//std::string sexpr2 = "21 + ((13 - 40)*2 + 1 - (3 +1))*2 + 9";
//	std::string sexpr2 = "21+((13-40)*2+1-(3+1))*2+9";
//	//                    0123456789012345678901234567890
//
//	ArgExpression expr;
//	expr.Create( sexpr2);
//	std::string spr = expr.DumpExpr();
//	cout << spr << endl;
//	expr.Dump(); cout << endl << endl;
//
//	cout << expr.Eval() << endl;
//
//	cout << endl;
//	cout << "hello" << endl;
//	return 0;
//}


