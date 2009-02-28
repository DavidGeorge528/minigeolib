#ifndef GEOMETRY_DIRECTION_CONCEPT_HPP
#define GEOMETRY_DIRECTION_CONCEPT_HPP

#include "geometry/geometric_object_concept.hpp"
#include "geometry/impl/enablers.hpp"
#include <boost/concept/usage.hpp>

namespace geometry
{

	struct direction_tag {};

template< typename D>
class Direction: public GeometricObject< D, direction_tag>
{
public:
	BOOST_CONCEPT_USAGE( Direction)
	{

	}
};

template< typename D>
class Direction3D: public Direction<D>
{
public:
	BOOST_CONCEPT_USAGE( Direction3D)
	{
		unit_type dx = d_.dx();
		unit_type dy = d_.dy();
		unit_type dz = d_.dz();
	}

private:
	D d_;
};


template< typename D>
class Direction2D: public Direction<D>
{
public:
	BOOST_CONCEPT_USAGE( Direction2D)
	{
		unit_type dx = d_.dx();
		unit_type dy = d_.dy();
	}

private:
	D d_;
};

namespace impl
{

template< typename Dir, unsigned D>
struct is_direction
{
	BOOST_STATIC_CONSTANT( bool, value = 
		(is_a< Dir, direction_tag>::value 
		&& has_dimensions< typename Dir::coord_system, D>::value));
};


} // namespace impl

} // geometry

#endif // GEOMETRY_DIRECTION_CONCEPT_HPP
