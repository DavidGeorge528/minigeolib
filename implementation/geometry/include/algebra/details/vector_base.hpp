#ifndef ALGEBRA_DETAILS_VECTOR_BASE_HPP
#define ALGEBRA_DETAILS_VECTOR_BASE_HPP

#include "algebra/unit_traits.hpp"
#include <cassert>

namespace algebra
{
namespace details
{

template< unsigned D, typename U, typename UT = unit_traits< U> >
class vector_base
{
public:
	enum { DIMENSIONS = D };
	typedef UT unit_traits_type;
	typedef typename unit_traits_type::unit_type unit_type;

protected:
	vector_base()
	{
	}

public:

	const unit_type& operator()( unsigned index) const 
	{ 
		assert( index < DIMENSIONS);
		return v_[index];
	}

	unit_type& operator()( unsigned index)
	{
		assert( index < DIMENSIONS);
		return v_[index];
	}

protected:
	unit_type v_[ DIMENSIONS];

};

} // namespace details

} // namespace algebra

#endif // ALGEBRA_DETAILS_VECTOR_BASE_HPP
