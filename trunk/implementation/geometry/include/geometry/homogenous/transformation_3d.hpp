#ifndef GEOMETRY_HOMOGENOUS_TRANSFORMATION_3_HPP
#define GEOMETRY_HOMOGENOUS_TRANSFORMATION_3_HPP

#include "geometry/transformation.hpp"

namespace geometry
{

template< typename CS >
class transformation< CS, typename impl::enabled_for< CS, 3, hcoord_system_tag>::type >
	: public impl::transformation_base< CS >
{
public:
	transformation(		
		const unit_type& a11, const unit_type& a12, const unit_type& a13, const unit_type& a14,
		const unit_type& a21, const unit_type& a22, const unit_type& a23, const unit_type& a24,
		const unit_type& a31, const unit_type& a32, const unit_type& a33, const unit_type& a34,
		const unit_type& a41, const unit_type& a42, const unit_type& a43, const unit_type& a44)
		: tr_( a11, a12, a13, a14, a21, a22, a23, a24, a31, a32, a33, a34, a41, a42, a43, a44) 
	{ }

	static transformation translation( const unit_type& dx, const unit_type& dy, const unit_type& dz)
	{
		return transformation( 1, 0, 0, dx, 0, 1, 0, dy, 0, 0, 1, dz, 0, 0, 0, 1);
	}

	position_type transformed( const position_type& pos) const
	{
		return tr_ * pos;
	}

	void transform( position_type& pos) const
	{
		pos = tr_ * pos;
	}

private:
	typedef algebra::matrix< 4, 4, unit_type, unit_traits_type> matrix_type;
	matrix_type tr_;
};

} // geometry

#endif // GEOMETRY_HOMOGENOUS_TRANSFORMATION_3_HPP
