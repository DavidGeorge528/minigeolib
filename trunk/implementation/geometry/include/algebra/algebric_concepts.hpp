#ifndef ALG_ALGEBRIC_CONCEPTS_HPP
#define ALG_ALGEBRIC_CONCEPTS_HPP

#include <boost/concept/usage.hpp>

namespace algebra
{

template< typename T>
class Subtractable
{
public:
	BOOST_CONCEPT_USAGE( Subtractable)
	{
		// Require operator-
		result_ = op1_ - op2_;
	}

private:
	T result_, op1_, op2_;
};


template< typename T>
class Additivable
{
public:
	BOOST_CONCEPT_USAGE( Additivable)
	{
		// Require operator+
		result_ = op1_ + op2_;
	}

private:
	T result_, op1_, op2_;
};


} // namespace algebra

#endif // ALG_ALGEBRIC_CONCEPTS_HPP
