#ifndef ALG_UNIT_TRAITS_HPP
#define ALG_UNIT_TRAITS_HPP

#include "algebra/algebric_concepts.hpp"
#include <boost/concept/assert.hpp>

namespace algebra
{

template< typename U>
struct unit_traits
{
	typedef U unit_type;

	static U zero() { return 0; }
	static U one() { return 1; }

	static U add( const U& op1, const U& op2) 
	{ 
		BOOST_CONCEPT_ASSERT( (Additivable<U>));
		return op1 + op2; 
	}

	static U subtract( const U& op1, const U& op2) 
	{
		BOOST_CONCEPT_ASSERT( (Subtractable<U>));
		return op1 - op2; 
	}
};

} // namespace algebra

#endif // ALG_UNIT_TRAITS_HPP
