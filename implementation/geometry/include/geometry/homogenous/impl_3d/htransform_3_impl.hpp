#ifndef GEOMETRY_IMPL_HTRANSFORM_3_IMPL_HPP
#define GEOMETRY_IMPL_HTRANSFORM_3_IMPL_HPP

#include "geometry/homogenous/hcoord_system_concept.hpp"
#include "algebra/matrix_4_4.hpp"
#include <boost/concept/assert.hpp>
#include <boost/static_assert.hpp>

namespace geometry
{
namespace impl_3d
{

	// DOC:
template< typename CS >
class htransform_3_impl
{
	BOOST_CONCEPT_ASSERT( (hcoord_system_concept< CS>));
	BOOST_STATIC_ASSERT( 3 == CS::DIMENSIONS);

public:
	typedef CS coord_system;
	typedef typename coord_system::unit_type unit_type;
	typedef typename coord_system::unit_traits_type unit_traits_type;
	typedef typename coord_system::position_type position_type;

private:
	typedef algebra::matrix< 4, 4, unit_type, unit_traits_type> matrix_type;

public:
	htransform_3_impl()
		: tr_( matrix_type::IDENTITY()) { }

	htransform_3_impl(		
			const unit_type& a11, const unit_type& a12, const unit_type& a13, const unit_type& a14,
			const unit_type& a21, const unit_type& a22, const unit_type& a23, const unit_type& a24,
			const unit_type& a31, const unit_type& a32, const unit_type& a33, const unit_type& a34,
			const unit_type& a41, const unit_type& a42, const unit_type& a43, const unit_type& a44)
		: tr_( a11, a12, a13, a14, a21, a22, a23, a24, a31, a32, a33, a34, a41, a42, a43, a44) 
	{ }

	position_type transformed( const position_type& pos) const
	{
		return tr_ * pos;
	}

	void transform( position_type& pos) const
	{
		pos = tr_ * pos;
	}

private:
	matrix_type tr_;
};

} // impl_3d
} // geometry

#endif // GEOMETRY_IMPL_HTRANSFORM_3_IMPL_HPP
