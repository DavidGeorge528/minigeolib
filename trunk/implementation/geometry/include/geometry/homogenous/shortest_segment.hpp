#ifndef GEOMETRY_HOMOGENOUS_SHORTEST_SEGMENT_HPP
#define GEOMETRY_HOMOGENOUS_SHORTEST_SEGMENT_HPP

#include "geometry/homogenous/hcoord_system_concept.hpp"
#include "geometry/homogenous/vertex_concept.hpp"
#include "geometry/line_concept.hpp"
#include <boost/concept/assert.hpp>
#include <utility>
#include <cassert>


namespace geometry
{

/// \ingroup geometry
/// \brief It calculates the shortest segment that connects two lines.
/// \tparam V the vertex type, implementing Homogenous Vertex concept.
/// \tparam L the line type, implementing Line concept.
/// \param l1 the first line involved in calculation
/// \param l2 the second line involved in calculation
/// \return a pair of vertices, one from the first line, one from the second one, defining the segment. In case the two 
///		lines are parallel, the returned segment edges are invalid.
/// \details
///		The calculation is done by applying the following formula:
///		\n\code
///		Pa = base1 + mua*dir1
///		Pb = base2 + mub*dir2
///		\endcode
///		\n
///		where Pa and Pb are the resulted segment edges, base1 and base2 are the two vertices positioning the lines, and 
///		mua and mub are the two parameters defining the position of the points on the line direction, relative to the 
///		base vertices for each line.
///		\n
///		mua and mub are calculated by solving a system of two equations, provided that the resulted segment direction 
///		should be orthogonal to both line directions:
///		\n
///		\code
///		(Pa - Pb).dir1 = 0
///		(Pa - Pb).dir2 = 0
///		\endcode
///		\n
///		where dir1 and dir2 are the directions of the two lines.
template< typename V, typename L>
typename boost::enable_if_c<
		impl::is_line< L, 3, hcoord_system_tag>::value && impl::is_vertex< V, 3, hcoord_system_tag>::value,
		std::pair< V, V> >::type
	shortest_segment( const L& l1, const L& l2)
{
	BOOST_CONCEPT_ASSERT( (HCoordSystem<typename V::coord_system>));
	BOOST_CONCEPT_ASSERT( (HomogenousVertex3D<V>));
	BOOST_CONCEPT_ASSERT( (Line<L>));

	typedef typename V::coord_system coord_system;
	typedef typename coord_system::unit_traits_type unit_traits_type;
	typedef typename coord_system::unit_type unit_type;

	// It should calculate mua, mub values for the lines l1, l2 respectively, considering line equations:
	//	Pa = base1 + mua*dir1
    //	Pb = base2 + mub*dir2
	// base1 and base2 are the two points used as positioning for l1 and l2. dir1 and dir2 are the directions for both 
	// lines.

	// The shortest segment will have its direction perpendicular on both line directions, meanining that:
	//	(Pa - Pb).dir1 = 0
	//	(Pa - Pb).dir2 = 0

	typename coord_system::pos_rep 
		base1 = l1.base().normalized(), 
		base2 = l2.base().normalized();
	typename coord_system::dir_rep 
		dir1 = l1.dir().representation(),
		dir2 = l2.dir().representation();

	// This means (replacing Pa and Pb:
	//	(base1 + mua*dir1 - base2 - mub*dir2).dir1 = 0
	//	(base1 + mua*dir1 - base2 - mub*dir2).dir2 = 0
	//
	//	( (base1 - base2) + mua*dir1 - mub*dir2).dir1 = 0
	//  ( (base1 - base2) + mua*dir1 - mub*dir2).dir2 = 0

	// So we consider 
	//		vect = base1 - base2
	typename coord_system::dir_rep 
		vect = base1 - base2;

	if( unit_traits_type::is_zero( vect.at<0>()) && unit_traits_type::is_zero( vect.at<1>()) && unit_traits_type::is_zero( vect.at<2>()))
	{
		// The two bases are the same point. We have an intersection.
		return std::make_pair( V( base1), V(base2));
	}

	// And the equation system becomes
	//	(vect + mua*dir1 - mub*dir2).dir1 = 0
	//	(vect + mua*dir1 - mub*dir2).dir2 = 0
	//
	// Splitting dot product:
	//  vect.dir1 + mua*(dir1.dir1) - mub*(dir2.dir1) = 0
	//  vect.dir2 + mua*(dir1.dir2) - mub*(dir2.dir2) = 0
	//
	// Now, the quoeficients are:
	//  vd1 = vect.dir1
	//  vd2 = vect.dir2
	//  d1d2 = dir1.dir2
	//  dd1 = dir1.dir1
	//  dd2 = dir2.dir2
	
	unit_type 
		vd1 = vect*dir1,
		vd2 = vect*dir2,
		d1d2 = dir1*dir2,
		dd1 = dir1*dir1,
		dd2 = dir2*dir2;

	// So the equation system becomes:
	//		dd1*mua - d1d2*mub = -vd1
	//		d1d2*mua - dd2*mub = -vd2

	// From first equation, mua can be calculated as:
	//		mua = (-vd1 + d1d2*mub)/dd1
	//
	// Replacing in the second equation, results:
	//		d1d2*(-vd1 + d1d2*mub)/dd1 - dd2*mub = -vd2
	// Expanding
	//		-d1d2*vd1/dd1 + (d1d2*d1d2/dd1 - dd2)*mub = -vd2
	// Meaning 
	//		mub = (-vd2 + d1d2*vd1/dd1)/(d1d2*d1d2/dd1 - dd2)
	// Arranging the result gives:
	//		mub = (d1d2*vd1 - dd1*vd2) / (d1d2*d1d2 - dd1*dd2)

	unit_type mub = (d1d2*vd1 - dd1*vd2) / (d1d2*d1d2 - dd1*dd2);
	unit_type mua = (-vd1 + d1d2*mub)/dd1;

	// Pa
	dir1 *= mua;
	base1 += dir1;
	// Pb
	dir2 *= mub;
	base2 += dir2;

	return std::make_pair( V( base1), V(base2));
}

} // namespace geometry

#endif // GEOMETRY_HOMOGENOUS_SHORTEST_SEGMENT_HPP
