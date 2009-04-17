#ifndef GEOMETRY_HOMOGENOUS_INTERSECTIONS_HPP
#define GEOMETRY_HOMOGENOUS_INTERSECTIONS_HPP

#include "geometry/homogenous/shortest_segment.hpp"

namespace geometry
{

/// \ingroup geometry
/// \brief It calculates the intersection between two lines. If the lines are skewed, the returned point is invalid.
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
		&& unit_traits_type::is_zero( ssegm.first.z() - ssegm.second.z()))
	{
		return ssegm.first;
	}
	else
		V( unit_traits_type::infinity(), unit_traits_type::infinity(), unit_traits_type::infinity());
}


} // namespace geometry

#endif // GEOMETRY_HOMOGENOUS_INTERSECTIONS_HPP
