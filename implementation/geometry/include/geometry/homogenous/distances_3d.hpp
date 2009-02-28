#ifndef GEOMETRY_HOMOGENOUS_DISTANCES_3D_HPP
#define GEOMETRY_HOMOGENOUS_DISTANCES_3D_HPP

#include "geometry/coord_system_concept.hpp"
#include "geometry/coord_system_tags.hpp"
#include "geometry/impl/enablers.hpp"
#include "geometry/vertex_concept.hpp"
#include "geometry/line_concept.hpp"
#include "geometry/plane_concept.hpp"
#include <boost/concept/assert.hpp>

namespace geometry
{

template< typename V>
typename boost::enable_if_c< impl::is_vertex< V, 3>::value, typename V::coord_system::length_type>::type  
	distance( const V& vertex1, const V& vertex2)
{
	BOOST_CONCEPT_ASSERT( (coord_system_concept<typename V::coord_system>));
	BOOST_CONCEPT_ASSERT( (HomogenousVertex3D<V>));
	typename V::unit_type 
		dx = vertex2.x() - vertex1.x(),
		dy = vertex2.y() - vertex1.y(),
		dz = vertex2.z() - vertex1.z();
	return std::sqrt( dx*dx + dy*dy + dz*dz);
}


/// Let A(x1,y1,z1), B(x2,y2,z2) = Two points defining the line 
/// P(x,y,z) = Point whose distance from line AB is to be found
/// 
/// We can find vectors,
/// AB = <x2-x1, y2-y1, z2-z1> = <x3, y3, z3>
/// AP = < x-x1,  y-y1, z-z1 > = <x4, y4, z4>
/// 
/// I am using angle brackets < > to distinguish vectors from points.
/// 
/// Now, let's take the cross product AB X AP.  This is how you can calculate it:
/// 
/// AB X AP = < y3*z4 - z3*y4, -(x3*z4 - x4*z3), x3*y4 - x4*y3 >
/// 
/// Let's let (a) be the length of AB X AP.  Then
/// 
/// a = Sqrt{ (y3*z4 - z3*y4)^2 + (x3*z4 - x4*z3)^2 + (x3*y4 - x4*y3)^2 }
/// 
/// If you divide (a) by the distance AB you will get the distance of P 
/// from line AB. Distance AB can be found using the distance formula as,
/// AB = square root of (x3^2 + y3^2 + z3^2)
/// 
/// Thus the distance we are looking for is a/AB.
template< typename V, typename L>
typename boost::enable_if_c< impl::is_vertex< V, 3>::value && impl::is_line< L, 3>::value, 
			typename V::coord_system::length_type>::type
distance( const V& v, const L& l)
{
	BOOST_CONCEPT_ASSERT( (HomogenousVertex3D<V>));
	BOOST_CONCEPT_ASSERT( (Line<L>));
	BOOST_CONCEPT_ASSERT( (coord_system_concept< typename V::coord_system>));

	const typename L::vertex_type& line_base = l.base();
	const typename L::direction_type& line_dir = l.dir();
	
	// Calculate vector components for [v, l.base)
	typename V::unit_type 
		dbx = line_base.x() - v.x(),
		dby = line_base.y() - v.y(),
		dbz = line_base.z() - v.z();
	// Calculate distance as cross product between the previously calculated vector [v, l.base) and the unity vector 
	// determining the line direction (l.dir)
	typename V::unit_type
		x = line_dir.dy()*dbz - line_dir.dz()*dby,
		y = line_dir.dx()*dbz - line_dir.dz()*dbx,
		z = line_dir.dx()*dby - line_dir.dy()*dbx;
	typename V::unit_type
		result = std::sqrt( x*x + y*y + z*z);
	return result;
}


/// \brief It calculates the distance between a vertex and a plane.
template< typename V, typename P>
typename boost::enable_if_c< impl::is_plane< P, 3>::value && impl::is_vertex< V, 3>::value, 
		typename V::coord_system::length_type>::type
	distance( const V& vertex, const P& plane)
{
	// For the plane Ax + By + Cz + D and vertex (x0, y0, z0) ...
	typename V::unit_type x = vertex.x(), y = vertex.y(), z = vertex.z(), 
		a = plane.a(), b = plane.b(), c = plane.c(), d = plane.d();

	// ... the distance is as in the formula below.
	return (a*x + b*y + c*z + d)/std::sqrt( a*a + b*b + c*c);
}

} // geometry

#endif // GEOMETRY_HOMOGENOUS_DISTANCES_3D_HPP
