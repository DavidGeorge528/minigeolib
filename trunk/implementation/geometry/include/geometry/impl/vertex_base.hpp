#ifndef GEOMETRY_IMPL_VERTEX_BASE_HPP
#define GEOMETRY_IMPL_VERTEX_BASE_HPP

#include "geometry/coord_system_concept.hpp"
#include "geometry/vertex_concept.hpp"
#include "geometry/impl/geometric_object.hpp"
#include <boost/concept/assert.hpp>

namespace geometry
{
namespace impl
{

template< typename CS>
class vertex_base: public geometric_object< CS, vertex_tag>
{
public:
	typedef typename coord_system::position_type position_type;
};


} // impl
} // geometry

#endif // GEOMETRY_IMPL_VERTEX_BASE_HPP
