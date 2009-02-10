#ifndef GEOMETRY_GEOMETRIC_OBJECT_CONCEPT_HPP
#define GEOMETRY_GEOMETRIC_OBJECT_CONCEPT_HPP

#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>

namespace geometry
{

// DOC
template< typename GO, typename Tag>
class GeometricObject
{
public:
	// Require coordinate system alias.
	typedef typename GO::coord_system coord_system;

	// Require unit type alias
	typedef typename GO::unit_type unit_type;

	// Require unit traits type alias
	typedef typename GO::unit_traits_type unit_traits_type;

	typedef typename GO::tag tag;

	// Require unit type traits uses unit type
	BOOST_STATIC_ASSERT( (boost::is_same< unit_type, typename unit_traits_type::unit_type>::value));

	// Require expected tag
	BOOST_STATIC_ASSERT( (boost::is_same< tag, Tag>::value));
};

} // geometry

#endif // GEOMETRY_GEOMETRIC_OBJECT_CONCEPT_HPP
