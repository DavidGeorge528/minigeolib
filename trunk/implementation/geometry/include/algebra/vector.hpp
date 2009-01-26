#ifndef ALG_VECTOR_HPP
#define ALG_VECTOR_HPP

#include "algebra/details/vector_base.hpp"
#include <algorithm>

namespace algebra
{

template< unsigned D, typename U, typename UT = unit_traits< U> >
class vector: public details::vector_base< D, U, UT>
{
	typedef vector< D, U, UT> my_type_;
public:
	vector()
	{
		std::fill_n( &v_[0], D, unit_traits_type::zero());
	}

	template< typename It> vector( It begin, It end)
	{
		assert( std::distance( begin, end) == DIMENSIONS);
		std::copy( begin, end, &v_[0]);
	}

	template< typename It> vector( It begin)
	{
		for( unsigned n = 0; n < DIMENSIONS; ++n, ++begin)
		{
			v_[n] = *begin;
		}
	}

	my_type_& operator=( const my_type_& op)
	{
		if( this != &op)
		{
			std::copy( op.begin(), op.end(), &v_[0]);
		}
		return *this;
	}

	friend my_type_ operator+( const my_type_& op1, const my_type_& op2)
	{
		my_type_ result;
		std::transform( &op1.v_[0], &op1.v_[0] + DIMENSIONS, &op2.v_[0], &result.v_[0], &unit_traits_type::add);
		return result;
	}

	my_type_& operator+=( const my_type_& op)
	{
		std::transform( &v_[0], &v_[0] + DIMENSIONS, &op.v_[0], &v_[0], &unit_traits_type::add);
		return *this;
	}

	friend my_type_ operator-( const my_type_& op1, const my_type_& op2)
	{
		my_type_ result;
		std::transform( &op1.v_[0], &op1.v_[0] + DIMENSIONS, &op2.v_[0], &result.v_[0], &unit_traits_type::subtract);
		return result;
	}

	my_type_& operator-=( const my_type_& op)
	{
		std::transform( &v_[0], &v_[0] + DIMENSIONS, &op.v_[0], &v_[0], &unit_traits_type::subtract);
		return *this;
	}
};

} // namespace algebra

#include "vector_2.hpp"
#include "vector_3.hpp"
#include "vector_4.hpp"

#endif // ALG_VECTOR_HPP
