#ifndef GEOMETRY_PARALLELISM_3D_HPP
#define GEOMETRY_PARALLELISM_3D_HPP

#include "geometry/direction_concept.hpp"
#include "geometry/line_concept.hpp"
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
/// \param d1 the first line to be compared.
/// \param d2 the second line to be compared.
/// \param tolerance the tolerance to be used for comparing the calculation results with the expected results.
/// \details
///		It uses the direction parallelism checking function, providing the directions of the two involved lines.
template< typename L, typename TP>
typename boost::enable_if< impl::is_line< L, 3>, bool>::type
	are_parallel( const L& l1, const L& l2, const TP& tolerance)
{
	return are_parallel( l1.dir(), l2.dir(), tolerance);
}

} // namespace geometry

#endif // GEOMETRY_PARALLELISM_3D_HPP
