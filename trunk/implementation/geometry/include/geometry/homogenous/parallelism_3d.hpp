#ifndef GEOMETRY_PARALLELISM_3D_HPP
#define GEOMETRY_PARALLELISM_3D_HPP

#include "geometry/direction_concept.hpp"
#include "geometry/line_concept.hpp"
#include "geometry/plane_concept.hpp"
#include "geometry/homogenous/direction.hpp"
#include "geometry/impl/vector_utils.hpp"
#include "algebra/tolerance_policy_concept.hpp"
#include "algebra/epsilon_tolerance.hpp"
#include <boost/concept/assert.hpp>
#include <cmath>

namespace geometry
{

/// \brief It checks whether two given directions are parallel or not.
/// \tparam Dir the direction type, implementing the 3D direction concept.
/// \tparam TP the tolerance policy to be used for comparing the calculation results with the expected results.
/// \param d1 the first direction to be compared.
/// \param d2 the second direction to be compared.
/// \param tolerance the tolerance to be used for comparing the calculation results with the expected results.
/// \details
///		It calculates the cosinus of the angle between the two given directions. If the absolute value of that cosinus 
///		is 1 (considering the given tolerance), it means that the two directions are parallel.
template< typename Dir, typename TP>
typename boost::enable_if< impl::is_direction< Dir, 3>, bool>::type 
	are_parallel( const Dir& d1, const Dir& d2, const TP& tolerance)
{
	typedef typename Dir::unit_type unit_type;
	BOOST_CONCEPT_ASSERT( (algebra::TolerancePolicy< TP>));
	BOOST_CONCEPT_ASSERT( (Direction3D<Dir>));
	// We know that the norm of direction concept is always 1, so we "simply" the computation, by making only the dot 
	// product:
	const unit_type cos_angle = d1.dx()*d2.dx() + d1.dy()*d2.dy() + d1.dz()*d2.dz();
	return tolerance.equals( std::abs( cos_angle), unit_type( 1));
}


/// \brief It checks whether two given lines are parallel or not.
/// \tparam L the line type, implementing the 3D line concept.
/// \tparam TP the tolerance policy to be used for comparing the calculation results with the expected results.
/// \param l1 the first line to be compared.
/// \param l2 the second line to be compared.
/// \param tolerance the tolerance to be used for comparing the calculation results with the expected results.
/// \details
///		It uses the direction parallelism checking function, providing the directions of the two involved lines.
template< typename L, typename TP>
typename boost::enable_if< impl::is_line< L, 3>, bool>::type
	are_parallel( const L& l1, const L& l2, const TP& tolerance)
{
	BOOST_CONCEPT_ASSERT( (Line3D<L>));
	BOOST_CONCEPT_ASSERT( (algebra::TolerancePolicy<TP>));
	return are_parallel( l1.dir(), l2.dir(), tolerance);
}


/// \brief It checks whether two given planes are parallel or not.
/// \tparam P the plane type, implementing the 3D plane concept.
/// \tparam TP the tolerance policy to be used for comparing the calculation results with the expected results.
/// \param p1 the first plane to be compared.
/// \param p2 the second line to be compared.
/// \param tolerance the tolerance to be used for comparing the calculation results with the expected results.
/// \details
///		It uses the direction parallelism checking function, providing the normal directions of the two involved planes.
template< typename P, typename TP>
typename boost::enable_if< impl::is_plane< P, 3>, bool>::type
	are_parallel( const P& p1, const P& p2, const TP& tolerance)
{
	BOOST_CONCEPT_ASSERT( (Plane<P>));
	BOOST_CONCEPT_ASSERT( (algebra::TolerancePolicy<TP>));
	typedef direction< typename P::coord_system> direction_type;
	return are_parallel( direction_type( p1), direction_type( p2), tolerance);
}

/// \brief It checks whether a given line is parallel with a given plane.
/// \tparam P the type of the plane, implementing the 3D plane concept.
/// \tparam L the type of the line, implementing the 3D line concept.
/// \tparam TP the tolerance policy to be used for comparing the calculation results with the expected results.
/// \param plane the plane to check.
/// \param line the line to check.
/// \param tolerance the tolerance to be used for comparing the calculation results with the expected results.
/// \details
///		It uses the direction parallelism checking function, providing the normal direction of the involved plane and 
///		the direction of the line.
template< typename P, typename L, typename TP>
typename boost::enable_if_c< impl::is_plane< P, 3>::value && impl::is_line< L, 3>::value, bool>::type
	are_parallel( const P& plane, const L& line, const TP& tolerance)
{
	BOOST_CONCEPT_ASSERT( (Plane<P>));
	BOOST_CONCEPT_ASSERT( (Line3D<L>));
	BOOST_CONCEPT_ASSERT( (algebra::TolerancePolicy<TP>));
	
	typedef typename L::direction_type direction_type;
	typedef typename L::unit_type unit_type;

	direction_type plane_normal( plane);
	direction_type line_dir = line.dir();
	unit_type cos_angle = impl::dot_product( 
		plane_normal.dx(), plane_normal.dy(), plane_normal.dz(),
		line_dir.dx(), line_dir.dy(), line_dir.dz());
	return tolerance.equals( 0, cos_angle);
}

/// \copydoc are_parallel<P,L,TP>( const P& , const L& , const TP& )
template< typename P, typename L, typename TP>
inline typename boost::enable_if_c< impl::is_plane< P, 3>::value && impl::is_line< L, 3>::value, bool>::type
	are_parallel( const L& line, const P& plane, const TP& tolerance)
{
	return are_parallel( plane, line, tolerance);
}

} // namespace geometry

#endif // GEOMETRY_PARALLELISM_3D_HPP
