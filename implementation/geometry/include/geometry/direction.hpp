#ifndef GEOMETRY_DIRECTION_HPP
#define GEOMETRY_DIRECTION_HPP

#include "geometry/impl/direction_base.hpp"
#include "geometry/homogenous/hcoord_system_concept.hpp"
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>

namespace geometry
{

template< typename CS, typename Enabler = void>
class direction
{
	BOOST_STATIC_ASSERT( !(boost::is_same< typename CS::system_type, hcoord_system_tag>::value && CS::DIMENSIONS == 3));
	BOOST_STATIC_ASSERT( !(boost::is_same< typename CS::system_type, hcoord_system_tag>::value && CS::DIMENSIONS == 2));
};

} // geometry

#endif // GEOMETRY_DIRECTION_HPP
