#ifndef GEOMETRY_HOMOGENOUS_INTERSECTIONS_HPP
#define GEOMETRY_HOMOGENOUS_INTERSECTIONS_HPP

#include "geometry/homogenous/shortest_segment.hpp"
#include "geometry/plane_concept.hpp"
#include <cmath>

namespace geometry
{

/// \ingroup geometry
/// \brief It calculates the intersection between two lines. If the lines are skewed, the returned point is invalid.
/// \tparam V the vertex type, implementing Homogenous Vertex concept.
/// \tparam L the line type, implementing Line concept.
/// \param l1 the first line involved in calculation
/// \param l2 the second line involved in calculation
/// \return a vertex as intersection or an invalid one if the lines don't intersect.
template< typename V, typename L>
typename boost::enable_if_c<
		impl::is_line< L, 3, hcoord_system_tag>::value && impl::is_vertex< V, 3, hcoord_system_tag>::value,
		V >::type
	intersect( const L& l1, const L& l2)
{
	typedef typename V::unit_traits_type unit_traits_type;
	std::pair<V,V> ssegm = shortest_segment<V>( l1, l2);
	if( unit_traits_type::is_zero( ssegm.first.x() - ssegm.second.x())
		&& unit_traits_type::is_zero( ssegm.first.y() - ssegm.second.y())
		&& unit_traits_type::is_zero( ssegm.first.z() - ssegm.second.z())
		&& !unit_traits_type::is_zero( 1 - std::abs( l1.dir().representation() * l2.dir().representation())))
	{
		return ssegm.first; 
	}
	else
		return V( unit_traits_type::infinity(), unit_traits_type::infinity(), unit_traits_type::infinity());
}


/// \ingroup geometry
/// \brief It implements the intersection between two planes.
/// \tparam L the type of the line, implementing Line concept
/// \tparam P the type of the plane, implementing Plane concept
/// \param p1 the first plane involved in the calculation.
/// \param p2 the second plane involved in the calculation.
/// \return the intersection line or a line with invalid direction if the planes are parallel or superimposed.
template< typename L, typename P>
typename boost::enable_if_c< 
	impl::is_plane< P, 3, hcoord_system_tag>::value && impl::is_line< L, 3, hcoord_system_tag>::value,
	L>::type
intersect( const P& p1, const P& p2)
{
	BOOST_CONCEPT_ASSERT( (HCoordSystem<typename P::coord_system>));
	BOOST_CONCEPT_ASSERT( (Line<L>));
	BOOST_CONCEPT_ASSERT( (Plane<P>));

	typedef typename P::coord_system coord_system;
	typedef typename coord_system::unit_traits_type unit_traits_type;
	typedef typename coord_system::unit_type unit_type;

	// We have plane Pi defined as Ni.p + d = 0
	typename coord_system::dir_rep 
		n1( p1.a(), p1.b(), p1.c()),
		n2( p2.a(), p2.b(), p2.c());

	// The equation of the intersection can be written as:
	// p = c1 * N1 + c2 * N2 + u*(N1 x N2)
	// where u is the parameter of the line, and c1 and c2 need to be determined.
	
	typename coord_system::dir_rep n1_x_n2 = n1 % n2;
	if( unit_traits_type::is_zero( n1_x_n2.at<0>())
		&& unit_traits_type::is_zero( n1_x_n2.at<1>())
		&& unit_traits_type::is_zero( n1_x_n2.at<2>()))
	{
		// Case of parallel planes
		// Return invalid line
		return L( typename L::vertex_type(), typename L::direction_type( n1_x_n2));
	}

	// Eventually, c1 and c2 can be deduced from the following system of equations:
	//		N1.p = -d1 = c1*N1.N1 + c2*N1.N2
	//		N2.p = -d2 = c1*N1.N2 + c2*N2.N2
	// 
	// Solving the system of equations gives:
	//		c1 = (-d1*N2.N2 + d1*N1.N2) / det
	//		c2 = (-d2*N1.N1 + d2*N1.N2) / det
	// where
	//		det = (N1.N1)*(N2.N2) - (N1.N2)*(N1.N2)

	unit_type
		n1n1 = n1*n1,
		n2n2 = n2*n2,
		n1n2 = n1*n2,
		det = n1n1*n2n2 - n1n2*n1n2,
		d1 = p1.d(),
		d2 = p2.d(),
		c1 = (-d1*n2n2 + d1*n1n2) / det,
		c2 = (-d2*n1n1 + d2*n1n2) / det;

	// Considering the equation of the line as:
	//		p = c1 * N1 + c2 * N2 + u*(N1 x N2)
	// where u is the parameter,
	// we can determine one point of the line as base, by using u = 0. So the base vertex coordinates are:
	//		p0 = c1*N1 + c2*N2;
	typename coord_system::pos_rep p0 = c1*n1 + c2*n2;
	
	// The direction of the line was calculated as N1 x N2

	// So the final line is:
	return L( typename L::vertex_type( p0), typename L::direction_type( n1_x_n2));
}

} // namespace geometry

#endif // GEOMETRY_HOMOGENOUS_INTERSECTIONS_HPP
