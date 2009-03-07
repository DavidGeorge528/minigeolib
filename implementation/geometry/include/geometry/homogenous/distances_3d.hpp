#ifndef GEOMETRY_HOMOGENOUS_DISTANCES_3D_HPP
#define GEOMETRY_HOMOGENOUS_DISTANCES_3D_HPP

#include "geometry/coord_system_concept.hpp"
#include "geometry/coord_system_tags.hpp"
#include "geometry/impl/enablers.hpp"
#include "geometry/vertex_concept.hpp"
#include "geometry/line_concept.hpp"
#include "geometry/plane_concept.hpp"
#include "geometry/impl/vector_utils.hpp"
#include <boost/concept/assert.hpp>
#include <cassert>

namespace geometry
{

template< typename V>
typename boost::enable_if_c< impl::is_vertex< V, 3>::value, typename V::coord_system::length_type>::type  
	distance( const V& vertex1, const V& vertex2)
{
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


/// \brief It calculates the minimum distance between two lines
template< typename L>
typename boost::enable_if< impl::is_line< L, 3>, typename L::coord_system::length_type>::type
	distance( const L& line1, const L& line2)
{
	BOOST_CONCEPT_ASSERT( (Line3D<L>));

	typedef typename L::unit_traits_type unit_traits_type;

	// We need one point from each line - P1(x1,y1,z1), P2(x2,y2,z2)
	typename L::unit_type x1 = line1.base().x(), y1 = line1.base().y(), z1 = line1.base().z();
	typename L::unit_type x2 = line2.base().x(), y2 = line2.base().y(), z2 = line2.base().z();

	typename L::unit_type dx1 = line1.dir().dx(), dy1 = line1.dir().dy(), dz1 = line1.dir().dz();
	typename L::unit_type dx2 = line2.dir().dx(), dy2 = line2.dir().dy(), dz2 = line2.dir().dz();

	typename L::unit_type dx=x2-x1, dy=y2-y1, dz=z2-z1;

	// Now, calculate the cross product n = v1 x v2, where v1 and v2 are directions for line 1 and line 2.
	typename L::unit_type nx = dy1*dz2 - dz1*dy2, ny = dz1*dx2 - dx1*dz2, nz = dx1*dy2 - dy1*dx2;
	typename L::unit_type norm = std::sqrt( nx*nx + ny*ny + nz*nz);
	if( unit_traits_type::is_zero( norm))
	{
		// We are in the case of parallel line
		// The distance D is P1P2 x dir1 / norm of dir1
		// Since direction of the line is always of norm 1, we don't need to bother to consider that in calculation.
		nx = dy*dz1 - dz*dy1, ny = dz*dx1 - dx*dz1, nz = dx*dy1 - dy*dx1;
		typename L::unit_type dist = std::sqrt( nx*nx + ny*ny + nz*nz);
		return dist;
	}
	else 
	{
		// We are in the case of skewing line
		// The distance D is P1P2 dot n / norm of n
		typename L::unit_type dist = (dx*nx + dy*ny + dz*nz)/norm;
		return dist;
	}
}

/// \brief It calculates the distance between two planes.
/// \tparam P the plane type, implementing Plane concept.
template< typename P>
typename boost::enable_if< impl::is_plane<P,3>, typename P::unit_type>::type
	distance( const P& p1, const P& p2)
{
	BOOST_CONCEPT_ASSERT( (Plane<P>));

	typedef P plane;
	typedef typename plane::unit_type unit_type;
	typedef typename plane::unit_traits_type unit_traits_type;

	unit_type a1 = p1.a(), b1 = p1.b(), c1 = p1.c(), d1 = p1.d();
	unit_type a2 = p2.a(), b2 = p2.b(), c2 = p2.c(), d2 = p2.d();

	// First, check whether the planes are parallel:
	unit_type norm1 = impl::norm( a1, b1, c1);
	unit_type norm2 = impl::norm( a2, b2, c2);
	// Cosinus of the dihedral angle.
	unit_type cos_angle = impl::dot_product( a1, b1, c1, a2, b2, c2) / (norm1*norm2);
	if( unit_traits_type::is_zero( unit_type(1.0) - std::abs(cos_angle)))
	{
		// parallel planes. Sanity checks first: both planes can be reduced to the same values for a, b and c.
		assert( unit_traits_type::is_zero( std::abs( a1/norm1) - std::abs( a2/norm2)));
		assert( unit_traits_type::is_zero( std::abs( b1/norm1) - std::abs( b2/norm2)));
		assert( unit_traits_type::is_zero( std::abs( c1/norm1) - std::abs( c2/norm2)));

		unit_type a = a1/norm1, b = b1/norm1, c = c1/norm1;
		unit_type dist = (d2/norm2 - d1/norm1);
		return dist;
	}
	else
	{
		return 0;
	}
}

} // geometry

#endif // GEOMETRY_HOMOGENOUS_DISTANCES_3D_HPP
