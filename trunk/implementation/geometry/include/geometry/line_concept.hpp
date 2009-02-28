#ifndef GEOMETRY_LINE_CONCEPT_HPP
#define GEOMETRY_LINE_CONCEPT_HPP

#include "geometry/geometric_object_concept.hpp"
#include "geometry/vertex_concept.hpp"
#include "geometry/direction_concept.hpp"
#include "geometry/impl/enablers.hpp"
#include <boost/concept/assert.hpp>
#include <boost/concept/usage.hpp>

namespace geometry
{

	struct line_tag {};

template< typename L>
class Line: public GeometricObject< L, line_tag>
{
public:
	typedef typename L::vertex_type vertex_type;
	typedef typename L::direction_type direction_type;

	BOOST_CONCEPT_ASSERT( (Vertex<vertex_type>));
	BOOST_CONCEPT_ASSERT( (Direction<direction_type>));

	BOOST_CONCEPT_USAGE( Line)
	{
		vertex_type base = line_.base();
		direction_type dir = line_.dir();
	}

private:
	L line_;
};

namespace impl
{

template< typename L, unsigned D>
struct is_line
{
	BOOST_STATIC_CONSTANT( bool, value =
		(is_a< L, line_tag>::value
		&& has_dimensions< typename L::coord_system, D>::value));
};

} // namespace impl

} // geometry

#endif // GEOMETRY_LINE_CONCEPT_HPP
