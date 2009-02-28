#ifndef GEOMETRY_VERTEX_HPP
#define GEOMETRY_VERTEX_HPP

#include "geometry/impl/vertex_base.hpp"
#include "geometry/impl/enablers.hpp"
#include "geometry/coord_system_tags.hpp"
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>

namespace geometry
{

template< typename CS, typename Enable = void >
class vertex
{
	BOOST_STATIC_ASSERT( !(boost::is_same< typename CS::system_type, hcoord_system_tag>::value && CS::DIMENSIONS == 3));
	BOOST_STATIC_ASSERT( !(boost::is_same< typename CS::system_type, hcoord_system_tag>::value && CS::DIMENSIONS == 2));
};

namespace impl
{

/// \brief It specializes the vertex type checking for vertex class.
/// \sa is_vertex< typename V, unsigned D>
template< typename CS, unsigned D>
struct is_vertex< vertex< CS>, D >
{
	BOOST_STATIC_CONSTANT( bool, value = (CS::DIMENSIONS == D));
};

} // namespace impl

} // geometry

#endif // GEOMETRY_VERTEX_HPP
