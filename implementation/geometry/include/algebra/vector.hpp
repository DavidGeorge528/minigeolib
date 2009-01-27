#ifndef ALG_VECTOR_HPP
#define ALG_VECTOR_HPP

#include "algebra/details/vector_base.hpp"
#include <boost/bind.hpp>
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

	friend my_type_ operator*( const unit_type& s, const my_type_& v)
	{
		my_type_ result;
		std::transform( &v.v_[0], &v_[0] + DIMENSIONS, &result.v_[0], boost::bind( &my_type_::multiply, s, _1) );
		return result;
	}

	friend my_type_ operator*( const my_type_& v, const unit_type& s)
	{
		my_type_ result;
		std::transform( &v.v_[0], &v_[0] + DIMENSIONS, &result.v_[0], boost::bind( &my_type_::multiply, _1, s) );
		return result;
	}

	my_type_& operator*=( const unit_type& s)
	{
		std::transform( &v_[0], &v_[0] + DIMENSIONS, &v_[0], boost::bind( &my_type_::multiply, _1, s));
		return *this;
	}


	friend my_type_ operator/( const my_type_& v, const unit_type& s)
	{
		my_type_ result;
		std::transform( &v.v_[0], &v_[0] + DIMENSIONS, &result.v_[0], boost::bind( &my_type_::divide, _1, s) );
		return result;
	}


	my_type_& operator/=( const unit_type& s)
	{
		std::transform( &v_[0], &v_[0] + DIMENSIONS, &v_[0], boost::bind( &my_type_::divide, _1, s));
		return *this;
	}

private:
	static unit_type subtract( const unit_type& op1, const unit_type& op2)
	{
		return op1 - op2;
	}

	static unit_type add( const unit_type& op1, const unit_type& op2)
	{
		return op1 + op2;
	}

	static unit_type multiply( const unit_type& op1, const unit_type& op2)
	{
		return  op1*op2;
	}

	static unit_type divide( const unit_type& op1, const unit_type& op2)
	{
		return op1 / op2;
	}
};

} // namespace algebra

#include "vector_2.hpp"
#include "vector_3.hpp"
#include "vector_4.hpp"

#endif // ALG_VECTOR_HPP
