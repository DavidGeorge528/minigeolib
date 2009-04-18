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

/// \ingroup geometry
/// \brief It checks the requirements for a line concept.
template< typename L>
class Line: public GeometricObject< L, line_tag>
{
public:
	// Expect vertex alias.
	typedef typename L::vertex_type vertex_type;
	// Expect direction alias.
	typedef typename L::direction_type direction_type;

	BOOST_CONCEPT_ASSERT( (Vertex<vertex_type>));
	BOOST_CONCEPT_ASSERT( (Direction<direction_type>));

	BOOST_CONCEPT_USAGE( Line)
	{
		// Require base vertex
		vertex_type base = line_.base();

		// Require direction.
		direction_type dir = line_.dir();

		// Require initialization:
		L line( base, dir);
	}

private:
	L line_;
};

template< typename L>
class Line3D: public Line< L>
{
public:
	BOOST_CONCEPT_ASSERT( (Vertex3D< vertex_type>));
	BOOST_CONCEPT_ASSERT( (Direction3D< direction_type>));
};

namespace impl
{

/// \brief It checks that the given type is a line in a coordinate system with the specified number of dimensions.
/// \tparam L the type to be checked.
/// \tparam D the expected number of dimensions of the coordinate system. 0 means ignore it.
/// \tparam CSID the expected system type ID. void means ignore it.
/// \details
///		The default implementation assumes that the given type is not a line type. The line checking relies on the
///		mechanism of partial template specialization, so in case a new line type is implemented, a specialization of
///		this class should be defined for that type of line.
template< typename L, unsigned D, typename CSID = void>
struct is_line
{
	BOOST_STATIC_CONSTANT( bool, value = false);
};

} // namespace impl

} // geometry

#endif // GEOMETRY_LINE_CONCEPT_HPP
