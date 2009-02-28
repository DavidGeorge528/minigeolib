#ifndef GEOMETRY_PLANE_HPP
#define GEOMETRY_PLANE_HPP

#include "geometry/impl/geometric_object.hpp"
#include "geometry/impl/enablers.hpp"
#include "geometry/plane_concept.hpp"
#include "geometry/vertex_concept.hpp"
#include "geometry/direction_concept.hpp"
#include "algebra/vector.hpp"
#include <boost/type_traits/is_same.hpp>

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

	/// \brief It creates a plane defined by a vertex and a normal direction.
	/// \tparam V the type of the vertex. It should be a three dimensional vertex.
	/// \tparam D the type of the direction object. It should be a three dimensional direction.
	/// \param v the vertex defining the position of the plane.
	/// \param dir the normal direction defining the orientation of the plane.
	/// \see http://en.wikipedia.org/wiki/Plane_(geometry)
	template< typename V, typename D>
	plane( const V& v, const D& dir, 
		typename boost::enable_if< boost::is_same< typename V::tag, vertex_tag> >::type* = NULL,
		typename boost::enable_if< boost::is_same< typename D::tag, direction_tag> >::type* = NULL)
	{
		// Temporary copies of the coordinates. For example, when using homogenous coordinates, this avoids calculating 
		// the normalized coordinates more than one time (at each x() accessor method invocation.
		typename V::unit_type vx = 
			v.x(), vy = v.y(), vz = v.z(),
			dx = dir.dx(), dy = dir.dy(), dz = dir.dz();

		// Calculate the plane equation components:
		// A, B, C - are normal direction components on X, Y and Z axis.
		typename V::unit_type a = dx, b = dy, c = dz,
		// D is negative dot product of normal direction and vertex coordinate vector.
			d = -(vx*dx + vy*dy + vz*dz);
		// Setup the results
		coefs_.at<0>() = a; coefs_.at<1>() = b; coefs_.at<2>() = c; coefs_.at<3>() = d;
	}

	const unit_type& a() const { return coefs_.at<0>(); }
	const unit_type& b() const { return coefs_.at<1>(); }
	const unit_type& c() const { return coefs_.at<2>(); }
	const unit_type& d() const { return coefs_.at<3>(); }

private:
	repr_type coefs_;
};

} // geometry

#endif // GEOMETRY_PLANE_HPP
