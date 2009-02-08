#ifndef GEOMETRY_IMPL_VERTEX_BASE_HPP
#define GEOMETRY_IMPL_VERTEX_BASE_HPP

#include "geometry/coord_system_concept.hpp"
#include <boost/concept/assert.hpp>

namespace geometry
{
namespace impl
{

template< typename CS>
class vertex_base
{
public:
	BOOST_CONCEPT_ASSERT( (coord_system_concept<CS>));

	typedef CS coord_system;
	typedef typename coord_system::unit_type unit_type;
	typedef typename coord_system::unit_traits_type unit_traits_type;
	typedef typename coord_system::position_type position_type;
};


} // impl
} // geometry

#endif // GEOMETRY_IMPL_VERTEX_BASE_HPP
