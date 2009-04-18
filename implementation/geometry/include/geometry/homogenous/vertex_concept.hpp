#ifndef GEOMETRY_HOMOGENOUS_VERTEX_CONCEPT_HPP
#define GEOMETRY_HOMOGENOUS_VERTEX_CONCEPT_HPP

#include "geometry/vertex_concept.hpp"
#include <boost/concept/assert.hpp>

namespace geometry
{

/// \ingroup geometry
/// \brief It checks the homogenous vertex concept.
template< typename V>
class HomogenousVertex: public Vertex< V>
{
	BOOST_CONCEPT_ASSERT( (HCoordSystem< coord_system>));
public:
	BOOST_CONCEPT_USAGE( HomogenousVertex)
	{
		// Require weight additional coordinate.
		unit_type w = v_.w();

		// Provides normalized method, returing the position representation.
		typename coord_system::pos_rep pos = v_.normalized();
		v_.normalized( pos);
	}

private:
	V v_;
};

/// \ingroup geometry
/// \brief It checks the concept of 2D homogenous vertex concept.
template< typename V>
class HomogenousVertex2D: public Vertex2D< V>, public HomogenousVertex<V>
{
public:
	BOOST_CONCEPT_USAGE( HomogenousVertex2D)
	{
		// Initialization
		V v1( x, y, w);
		// Initialization with position representation
		V v2( pos);
		// Initialization with coordinates representation
		V v3( coords_);
	}

private:
	V v_;
	unit_type x, y, w;
	typename coord_system::pos_rep pos_;
	typename coord_system::coord_vector coords_;
};


/// \ingroup geometry
/// \brief It checks the concept of 3D homogenous vertex concept.
template< typename V>
class HomogenousVertex3D: public Vertex3D< V>, public HomogenousVertex<V>
{
public:
	BOOST_CONCEPT_USAGE( HomogenousVertex3D)
	{
		// Initialization
		V v1( x, y, z, w);
		// Initialization with position representation
		V v2( pos_);
		// Initialization with coordinates representation
		V v3( coords_);
	}

private:
	V v_;
	unit_type x, y, z, w;
	typename coord_system::pos_rep pos_;
	typename coord_system::coord_vector coords_;
};

} // namespace geometry

#endif // GEOMETRY_HOMOGENOUS_VERTEX_CONCEPT_HPP
