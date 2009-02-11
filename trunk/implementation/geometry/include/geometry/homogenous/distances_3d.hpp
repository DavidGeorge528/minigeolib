#ifndef GEOMETRY_HOMOGENOUS_DISTANCES_3D_HPP
#define GEOMETRY_HOMOGENOUS_DISTANCES_3D_HPP

#include "geometry/coord_system_concept.hpp"
#include "geometry/coord_system_tags.hpp"
#include "geometry/impl/enablers.hpp"
#include "geometry/vertex_concept.hpp"
#include <boost/concept/assert.hpp>

namespace geometry
{

template< typename V>
typename impl::enabled_for< typename V::coord_system, 3, hcoord_system_tag, typename V::coord_system::length_type>::type  
	distance( const V& vertex1, const V& vertex2)
{
	BOOST_CONCEPT_ASSERT( (coord_system_concept<typename V::coord_system>));
	BOOST_CONCEPT_ASSERT( (HomogenousVertex3D<V>));
	typename V::unit_type 
		dx = vertex2.x() / vertex2.w() - vertex1.x() / vertex1.w(),
		dy = vertex2.y() / vertex2.w() - vertex1.y() / vertex1.w(),
		dz = vertex2.z() / vertex2.w() - vertex1.z() / vertex1.w();
	return std::sqrt( dx*dx + dy*dy + dz*dz);
}

} // geometry

#endif // GEOMETRY_HOMOGENOUS_DISTANCES_3D_HPP
