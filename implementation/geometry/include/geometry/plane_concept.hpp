#ifndef GEOMETRY_PLANE_CONCEPT_HPP
#define GEOMETRY_PLANE_CONCEPT_HPP

#include "geometry/geometric_object_concept.hpp"
#include "geometry/impl/enablers.hpp"
#include <boost/concept/assert.hpp>
#include <boost/concept/usage.hpp>

namespace geometry
{

	struct plane_tag { };

template< typename P>
class Plane: public GeometricObject<P, plane_tag>
{
public:
	BOOST_CONCEPT_USAGE( Plane)
	{
		unit_type a = plane_.a();
		unit_type b = plane_.b();
		unit_type c = plane_.c();
		unit_type d = plane_.d();
	}

private:
	P plane_;
};


namespace impl
{

/// \brief It checks that the given type is a plane in a coordinate system with the specified number of dimensions.
/// \tparam P the type to be checked.
/// \tparam D the expected number of dimensions of the coordinate system.
/// \details
///		The default implementation assumes that the given type is not a plane type. The plane checking relies on the
///		mechanism of partial template specialization, so in case a new plane type is implemented, a specialization of
///		this class should be defined for that type of plane.
template< typename P, unsigned D, typename CSID = void>
struct is_plane
{
	BOOST_STATIC_CONSTANT( bool, value = false);
};

} // namespace impl

} // geometry

#endif // GEOMETRY_PLANE_CONCEPT_HPP
