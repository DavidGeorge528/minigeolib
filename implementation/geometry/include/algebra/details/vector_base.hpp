#ifndef ALGEBRA_DETAILS_VECTOR_BASE_HPP
#define ALGEBRA_DETAILS_VECTOR_BASE_HPP

#include "algebra/matrix.hpp"
#include <boost/static_assert.hpp>
#include <cassert>

namespace algebra
{
namespace details
{
	
/// \ingroup algebra
/// \brief It is the base class for vector implementation. It provides the common utility functions and type aliases 
///		used by vector specializations. Defined for reusability.
template< unsigned D, typename U, typename UT = unit_traits< U> >
class vector_base
{
public:
	enum 
	{ 
		DIMENSIONS = D	///< The number of elements in the vector.
	};

	typedef UT unit_traits_type;
	typedef typename unit_traits_type::unit_type unit_type;
	typedef matrix< DIMENSIONS, DIMENSIONS,unit_type,unit_traits_type> matrix_type;

protected:
	vector_base()
	{
	}

public:
	/// \brief It provides index based access to the elements of the vector.
	/// \{
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
	/// \}


	// TODO: Test
	template< unsigned I>
	unit_type& at()
	{
		BOOST_STATIC_ASSERT( I < DIMENSIONS);
		return v_[I];
	}

	// TODO: Test
	template< unsigned I>
	const unit_type& at() const
	{
		BOOST_STATIC_ASSERT( I < DIMENSIONS);
		return v_[I];
	}

protected:
	/// \brief It contains the elements of the vector.
	unit_type v_[ DIMENSIONS];

};

} // namespace details

} // namespace algebra

#endif // ALGEBRA_DETAILS_VECTOR_BASE_HPP
