#ifndef GEOMETRY_HOMOGENOUS_HTRANSFORMATION_3_HPP
#define GEOMETRY_HOMOGENOUS_HTRANSFORMATION_3_HPP

#include "geometry/transformation.hpp"
#include "geometry/homogenous/hcoord_system_3.hpp"
#include "geometry/homogenous/impl_3d/htransform_3_impl.hpp"

namespace geometry
{

// DOCUMENT
// TEST
template< typename U, typename UT >
class transformation< hcoord_system< 3, U, UT> >: public impl_3d::htransform_3_impl< hcoord_system< 3, U, UT> >
{
	typedef impl_3d::htransform_3_impl< hcoord_system< 3, U, UT> > base_type_;
	typedef transformation< hcoord_system< 3, U, UT> > my_type_;
public:
	transformation(		
		const unit_type& a11, const unit_type& a12, const unit_type& a13, const unit_type& a14,
		const unit_type& a21, const unit_type& a22, const unit_type& a23, const unit_type& a24,
		const unit_type& a31, const unit_type& a32, const unit_type& a33, const unit_type& a34,
		const unit_type& a41, const unit_type& a42, const unit_type& a43, const unit_type& a44)
		: base_type_( a11, a12, a13, a14, a21, a22, a23, a24, a31, a32, a33, a34, a41, a42, a43, a44) 
	{ }

	static my_type_ translation( const unit_type& dx, const unit_type& dy, const unit_type& dz)
	{
		return my_type_( 1, 0, 0, dx, 0, 1, 0, dy, 0, 0, 1, dz, 0, 0, 0, 1);
	}
};

} // geometry

#endif // GEOMETRY_HOMOGENOUS_HTRANSFORMATION_3_HPP
