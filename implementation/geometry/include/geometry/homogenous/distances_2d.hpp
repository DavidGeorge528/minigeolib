#ifndef GEOMETRY_HOMOGENOUS_DISTANCES_2D_HPP
#define GEOMETRY_HOMOGENOUS_DISTANCES_2D_HPP

#include "geometry/coord_system_concept.hpp"
#include "geometry/coord_system_tags.hpp"
#include "geometry/impl/enablers.hpp"
#include "geometry/vertex_concept.hpp"
#include <boost/concept/assert.hpp>

namespace geometry
{

template< typename V>
typename impl::enabled_for< typename V::coord_system, 2, hcoord_system_tag, typename V::coord_system::length_type>::type  
	distance( const V& vertex1, const V& vertex2)
{
	BOOST_CONCEPT_ASSERT( (CoordSystem<typename V::coord_system>));
	BOOST_CONCEPT_ASSERT( (HomogenousVertex2D<V>));
	typename V::unit_type 
		dx = vertex2.x() - vertex1.x(),
		dy = vertex2.y() - vertex1.y();
	return std::sqrt( dx*dx + dy*dy);
}

} // geometry

#endif // GEOMETRY_HOMOGENOUS_DISTANCES_2D_HPP
