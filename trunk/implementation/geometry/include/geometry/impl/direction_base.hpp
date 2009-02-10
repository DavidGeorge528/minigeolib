#ifndef GEOMETRY_IMPL_DIRECTION_BASE_HPP
#define GEOMETRY_IMPL_DIRECTION_BASE_HPP

#include "geometry/coord_system_concept.hpp"
#include "geometry/direction_concept.hpp"
#include "geometry/impl/geometric_object.hpp"
#include <boost/concept/assert.hpp>

namespace geometry
{
namespace impl
{

template< typename CS>
class direction_base: public impl::geometric_object< CS, direction_tag>
{
};

} // impl
} // geometry

#endif // GEOMETRY_IMPL_DIRECTION_BASE_HPP
