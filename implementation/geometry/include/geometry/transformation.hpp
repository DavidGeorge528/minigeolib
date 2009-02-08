#ifndef GEOMETRY_TRANSFORMATION_HPP
#define GEOMETRY_TRANSFORMATION_HPP

#include "geometry/impl/enablers.hpp"
#include "geometry/impl/transformation_base.hpp"
#include <boost/static_assert.hpp>

namespace geometry
{
/// \brief It defines a generic transformation.
/// \tparam CS the coordinate system the transformation type is compatible with.
template< typename CS, typename Enable = void>
class transformation: public impl::transformation_base< CS>
{
	BOOST_STATIC_ASSERT( !(impl::has_dimensions<CS,2>::value && impl::is_hcoord_system<CS>::value));
	BOOST_STATIC_ASSERT( !(impl::has_dimensions<CS,3>::value && impl::is_hcoord_system<CS>::value));
};

} // geometry

#endif // GEOMETRY_TRANSFORMATION_HPP
