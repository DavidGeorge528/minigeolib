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
	/// \tparam V the type of the vertex. It should be a three dimensional vertex, implementing the three-dimensional 
	///		vertex concept.
	/// \tparam D the type of the direction object. It should be a three dimensional direction.
	/// \param v the vertex defining the position of the plane.
	/// \param dir the normal direction defining the orientation of the plane.
	/// \see http://en.wikipedia.org/wiki/Plane_(geometry)
	template< typename V, typename D>
	plane( const V& v, const D& dir, 
		typename boost::enable_if< impl::is_vertex< V, 3> >::type* = NULL,
		typename boost::enable_if< impl::is_direction< D, 3> >::type* = NULL)
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


	/// \brief It creates a plane defined by three vertices.
	/// \tparam V the type of the vertex. It should be a three dimensional vertex, implementing the three-dimensional 
	///		vertex concept.
	template< typename V>
	plane( const V& v1, const V& v2, const V& v3,
		typename boost::enable_if< impl::is_vertex< V, 3> >::type* = NULL)
	{
		unit_type x1 = v1.x(), y1 = v1.y(), z1 = v1.z();
		unit_type x2 = v2.x(), y2 = v2.y(), z2 = v2.z();
		unit_type x3 = v3.x(), y3 = v3.y(), z3 = v3.z();

		coefs_.at<0>() = y1*(z2 - z3) + y2*(z3 - z1) + y3*(z1 - z2);
		coefs_.at<1>() = z1*(x2 - x3) + z2*(x3 - x1) + z3*(x1 - x2);
		coefs_.at<2>() = x1*(y2 - y3) + x2*(y3 - y1) + x3*(y1 - y2);
		coefs_.at<3>() = -(x1*(y2*z3 - y3*z2) + x2*(y3*z1 - y1*z3) + x3*(y1*z2 - y2*z1));
	}

	const unit_type& a() const { return coefs_.at<0>(); }
	const unit_type& b() const { return coefs_.at<1>(); }
	const unit_type& c() const { return coefs_.at<2>(); }
	const unit_type& d() const { return coefs_.at<3>(); }

private:
	repr_type coefs_;
};

namespace impl
{

/// \see is_plane< typename P, unsigned D>
template< typename CS, unsigned D>
struct is_plane< plane< CS>, D>
{
	BOOST_STATIC_CONSTANT( bool, value = (D == CS::DIMENSIONS));
};

} // namespace impl

} // geometry

#endif // GEOMETRY_PLANE_HPP
