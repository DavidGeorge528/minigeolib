#ifndef GEOMETRY_VERTEX_HPP
#define GEOMETRY_VERTEX_HPP

#include "geometry/coord_system_concept.hpp"
#include <boost/static_assert.hpp>

namespace geometry
{

// DOC
template< typename CS >
class vertex
{
	// This generic class is specialized for 2 and 3 dimensions! Use that class!
	BOOST_STATIC_ASSERT( CS::DIMENSIONS != 2);
	BOOST_STATIC_ASSERT( CS::DIMENSIONS != 3);
};


} // geometry

#endif // GEOMETRY_VERTEX_HPP
