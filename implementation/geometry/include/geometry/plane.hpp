#ifndef GEOMETRY_PLANE_HPP
#define GEOMETRY_PLANE_HPP

#include "geometry/impl/geometric_object.hpp"
#include "geometry/impl/enablers.hpp"
#include "geometry/plane_concept.hpp"
#include "algebra/vector.hpp"

namespace geometry
{

template< typename CS, typename Enable = void>
class plane;


// See http://en.wikipedia.org/wiki/Plane_(geometry)
template< typename CS>
class plane< CS, typename impl::enabled_for< CS, 3, hcoord_system_tag>::type>:
	public impl::geometric_object< CS, plane_tag>
{
	typedef algebra::vector< 4, unit_type, unit_traits_type> repr_type;
public:
	plane( const unit_type& a, const unit_type& b, const unit_type& c, const unit_type& d)
		: coefs_( a, b, c, d)
	{}

	plane()
		: coefs_( 0,0,0,0) {}

	const unit_type& a() const { return coefs_.at<0>(); }
	const unit_type& b() const { return coefs_.at<1>(); }
	const unit_type& c() const { return coefs_.at<2>(); }
	const unit_type& d() const { return coefs_.at<3>(); }

private:
	repr_type coefs_;
};

} // geometry

#endif // GEOMETRY_PLANE_HPP
