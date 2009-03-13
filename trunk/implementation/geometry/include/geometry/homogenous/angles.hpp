#ifndef GEOMETRY_HOMOGENOUS_ANGLES_HPP
#define GEOMETRY_HOMOGENOUS_ANGLES_HPP

#include "geometry/homogenous/hcoord_system_concept.hpp"
#include "geometry/line_concept.hpp"
#include "geometry/plane_concept.hpp"
#include <boost/concept/requires.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <cmath>

namespace geometry
{

namespace impl
{

/// \ingroup geometry
/// \brief It calculates the cosinus of the angle between two given directions.
/// \tparam CS the coordinate system, providing the direction representation. It must be an implementation of homogenous 
///		coordinates.
template< typename CS>
BOOST_CONCEPT_REQUIRES( ((HCoordSystem<CS>)), (typename CS::unit_type))
	cos_angle( const typename CS::dir_rep& d1, const typename CS::dir_rep& d2)
{
	return d1*d2 / (algebra::norm( d1) * algebra::norm(d2));
}

} // namespace impl


/// \ingroup geometry
/// \brief It calculates the dihedral angle between two planes.
/// \tparam P the plane type, implementing the Plane concept.
template< typename P>
typename boost::enable_if< impl::is_plane<P,3>, typename P::unit_type>::type
	angle( const P& p1, const P& p2)
{
	BOOST_CONCEPT_ASSERT( (Plane<P>));
	typedef P plane_type;
	typedef typename plane_type::coord_system coord_system;
	typedef typename plane_type::unit_type unit_type;

	// Get nromal direction components for the planes
	typename coord_system::dir_rep n1( p1.a(), p1.b(), p1.c()), n2( p2.a(), p2.b(), p2.c());

	// cos(dihedral): n1.n2/|n1||n2|
	unit_type cangle = impl::cos_angle<coord_system>( n1, n2);
	return std::acos( cangle);
}

} // namespace geometry

#endif // GEOMETRY_HOMOGENOUS_ANGLES_HPP
