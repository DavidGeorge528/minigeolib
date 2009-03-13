#ifndef GEOMETRY_HOMOGENOUS_DISTANCES_HPP
#define GEOMETRY_HOMOGENOUS_DISTANCES_HPP

#include "geometry/homogenous/hcoord_system_concept.hpp"
#include "geometry/vertex_concept.hpp"
#include "geometry/line_concept.hpp"
#include "geometry/plane_concept.hpp"
#include "geometry/impl/vector_utils.hpp"
#include <boost/concept/assert.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <cassert>

namespace geometry
{

/// \brief It calculates the distances between two vertices in homogenous coordinate system.
/// \tparam V the vertex type, implementing HVertexConcept.
template< typename V>
typename boost::enable_if< impl::is_vertex< V, 0, hcoord_system_tag>, typename V::unit_type>::type
	distance( const V& v1, const V& v2)
{
	BOOST_CONCEPT_ASSERT( (HCoordSystem<typename V::coord_system>));
	BOOST_CONCEPT_ASSERT( (HVertex<V>));
	typedef typename V::coord_system coord_system;
	typename coord_system::pos_rep vrep1 = v1.normalized(), vrep2 = v2.normalized();
	vrep2 -= vrep1;
	return std::sqrt( coord_system::squared_norm( vrep2));
}

/// \ingroup geometry
/// \brief It calculates the distance between a line and a vertex.
/// \tparam V the type of vertex, implementing HVertex concept
/// \tparam K the type of the line, implementing Line concept
/// \{
template< typename V, typename L>
typename boost::enable_if_c< 
		impl::is_vertex< V, 3, hcoord_system_tag>::value 
		&& impl::is_line< L, 3, hcoord_system_tag>::value, 
	typename V::coord_system::length_type>::type
distance( const V& v, const L& l)
{
	BOOST_CONCEPT_ASSERT( (HomogenousVertex3D<V>));
	BOOST_CONCEPT_ASSERT( (Line<L>));

	typedef typename V::coord_system coord_system;
	typedef typename coord_system::pos_rep pos_rep;
	typedef typename coord_system::dir_rep dir_rep;

	// Vertex - Line Base vector calculation
	dir_rep v_b = l.base().normalized() - v.normalized();
	// Calculate distance as cross product between the previously calculated vector [Vertex, Line Base> and the unity 
	// vector determining the line direction (l.dir)
	dir_rep line_dir = l.dir().representation();
	dir_rep cross = v_b % line_dir;
	// Normally, the length of the cross product should be divided to the length of the line direction vector. Since the 
	// line direction has the length 1, it is not necessary to divide.
	return std::sqrt( coord_system::squared_norm( cross));
}

template< typename V, typename L>
inline typename boost::enable_if_c< 
		impl::is_vertex< V, 3, hcoord_system_tag>::value 
		&& impl::is_line< L, 3, hcoord_system_tag>::value, 
	typename V::coord_system::length_type>::type
distance( const L& l, const V& v)
{
	return distance( v, l);
}
/// \}


/// \ingroup geometry
/// \brief It calculates the distance between a vertex and a plane.
/// \tparam V the type of the vertex, implementing HVertex3D concept.
/// \tparam P the type of the plane, implementing Plane concept.
/// \{
template< typename V, typename P>
typename boost::enable_if_c< 
		impl::is_plane< P, 3, hcoord_system_tag>::value 
		&& impl::is_vertex< V, 3, hcoord_system_tag>::value, 
	typename V::coord_system::length_type>::type
distance( const V& vertex, const P& plane)
{
	BOOST_CONCEPT_ASSERT( (Plane<P>));
	BOOST_CONCEPT_ASSERT( (HomogenousVertex3D<V>));
	BOOST_STATIC_ASSERT( (boost::is_same< typename P::coord_system, typename V::coord_system>::value));

	typedef typename P::coord_system coord_system;
	typename coord_system::dir_rep norm_dir( plane.a(), plane.b(), plane.c());
	typename coord_system::pos_rep pos = vertex.normalized();

	// For the plane Ax + By + Cz + D with normal direction (A,B,C) and vertex (x, y, z)
	// the distance is as in the formula below.
	// (a*x + b*y + c*z + d)/std::sqrt( a*a + b*b + c*c);
	return (norm_dir * pos + plane.d()) / std::sqrt( norm_dir*norm_dir);
}

template< typename V, typename P>
inline typename boost::enable_if_c< 
		impl::is_plane< P, 3, hcoord_system_tag>::value 
		&& impl::is_vertex< V, 3, hcoord_system_tag>::value, 
	typename V::coord_system::length_type>::type
distance( const P& plane, const V& vertex)
{
	return distance( vertex, plane);
}

/// \}


/// \brief It calculates the minimum distance between two lines
template< typename L>
typename boost::enable_if< impl::is_line< L, 3, hcoord_system_tag>, typename L::coord_system::length_type>::type
	distance( const L& line1, const L& line2)
{
	BOOST_CONCEPT_ASSERT( (Line3D<L>));

	typedef typename L::unit_type unit_type;
	typedef typename L::unit_traits_type unit_traits_type;
	typedef typename L::coord_system coord_system;

	// We need one point from each line - P1(x1,y1,z1), P2(x2,y2,z2)
	typename coord_system::pos_rep p1( line1.base().normalized()), p2( line2.base().normalized());
	// Line directions
	typename coord_system::dir_rep dir1( line1.dir().representation()), dir2( line2.dir().representation());
	
	// Calculate the distance between the two bases
	typename coord_system::dir_rep d = p2 - p1;

	// Now, calculate the cross product n = v1 x v2, where v1 and v2 are directions for line 1 and line 2.
	typename coord_system::dir_rep n = dir1 % dir2;
	unit_type norm = std::sqrt( coord_system::squared_norm( n));

	if( unit_traits_type::is_zero( norm))
	{
		// We are in the case of parallel line
		// The distance D is P1P2 x dir1 / norm of dir1
		// Since direction of the line is always of norm 1, we don't need to bother to consider that in calculation.
		n = d % dir1;
		unit_type dist = std::sqrt( coord_system::squared_norm( n));
		return dist;
	}
	else 
	{
		// We are in the case of skewing line
		// The distance D is P1P2 dot n / norm of n
		unit_type dist = d*n/norm;
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
	typedef typename plane::coord_system coord_system;
	typedef typename plane::unit_type unit_type;
	typedef typename plane::unit_traits_type unit_traits_type;

	// Get nromal direction components for the planes
	typename coord_system::dir_rep n1( p1.a(), p1.b(), p1.c()), n2( p2.a(), p2.b(), p2.c());

	// First, check whether the planes are parallel:
	unit_type norm1 = algebra::norm( n1);
	unit_type norm2 = algebra::norm( n2);

	// Cosinus of the dihedral angle, calculated as dot product of the normals divided by norms of the normals:
	unit_type cos_angle = n1*n2/norm1*norm2;
	if( unit_traits_type::is_zero( unit_type(1.0) - std::abs(cos_angle)))
	{
		// parallel planes. Sanity checks first: both planes can be reduced to the same values for a, b and c.
		assert( unit_traits_type::is_zero( std::abs( n1.at<0>()/norm1) - std::abs( n2.at<0>()/norm2)));
		assert( unit_traits_type::is_zero( std::abs( n1.at<1>()/norm1) - std::abs( n2.at<1>()/norm2)));
		assert( unit_traits_type::is_zero( std::abs( n1.at<2>()/norm1) - std::abs( n2.at<2>()/norm2)));

		unit_type dist = (p2.d()/norm2 - p1.d()/norm1);
		return dist;
	}
	else
	{
		return 0;
	}
}

} // namespace geometry

#endif // GEOMETRY_HOMOGENOUS_DISTANCES_HPP
