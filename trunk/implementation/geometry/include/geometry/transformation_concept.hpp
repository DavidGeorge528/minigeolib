#ifndef GEOMETRY_TRANSFORMATION_CONCEPT_HPP
#define GEOMETRY_TRANSFORMATION_CONCEPT_HPP

#include <boost/concept/usage.hpp>

namespace geometry
{

template< typename T>
class Transformation
{
public:
	typedef typename T::coord_system coord_system;
	typedef typename T::unit_type unit_type;
	typedef typename T::unit_traits_type unit_traits_type;
	typedef typename T::position_type position_type;

	BOOST_CONCEPT_USAGE( Transformation)
	{
		position_type p( tr_.transformed( pos_));
		tr_.transform( pos_);
	}

private:
	T tr_;
	position_type pos_;
};

} // geometry

#endif // GEOMETRY_TRANSFORMATION_CONCEPT_HPP
