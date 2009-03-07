#ifndef GEOMETRY_IMPL_GEOMETRIC_OBJECT_HPP
#define GEOMETRY_IMPL_GEOMETRIC_OBJECT_HPP

#include "geometry/coord_system_concept.hpp"
#include <boost/concept/assert.hpp>

namespace geometry
{
namespace impl
{

template< typename CS, typename Tag>
class geometric_object
{
public:
	BOOST_CONCEPT_ASSERT( (CoordSystem<CS>));

	typedef CS coord_system;
	typedef typename coord_system::unit_type unit_type;
	typedef typename coord_system::unit_traits_type unit_traits_type;
	typedef Tag tag;
};

} // impl
} // geometry

#endif // GEOMETRY_IMPL_GEOMETRIC_OBJECT_HPP
