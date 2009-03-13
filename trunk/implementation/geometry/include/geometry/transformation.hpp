#ifndef GEOMETRY_TRANSFORMATION_HPP
#define GEOMETRY_TRANSFORMATION_HPP

#include "geometry/impl/transformation_base.hpp"
#include <boost/static_assert.hpp>

namespace geometry
{
/// \brief It defines a generic transformation.
/// \tparam CS the coordinate system the transformation type is compatible with.
template< typename CS, typename Enable = void>
class transformation;

} // geometry

#endif // GEOMETRY_TRANSFORMATION_HPP
