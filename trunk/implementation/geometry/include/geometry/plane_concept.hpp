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

template< typename P, unsigned D>
struct is_plane
{
	BOOST_STATIC_CONSTANT( bool, value 
		= (is_a< P, plane_tag>::value 
		&& has_dimensions< typename P::coord_system, 3>::value));
};

} // namespace impl

} // geometry

#endif // GEOMETRY_PLANE_CONCEPT_HPP
