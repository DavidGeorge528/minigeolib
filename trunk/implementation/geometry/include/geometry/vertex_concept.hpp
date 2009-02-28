#ifndef GEOMETRY_VERTEX_CONCEPT_HPP
#define GEOMETRY_VERTEX_CONCEPT_HPP

#include "geometry/geometric_object_concept.hpp"
#include "geometry/impl/enablers.hpp"
#include <boost/concept/usage.hpp>

namespace geometry
{

struct vertex_tag { };

// TODO: Continue
template< typename V>
class Vertex: public GeometricObject< V, vertex_tag>
{
public:
	typedef typename V::position_type position_type;
};

template< typename V>
class Vertex3D: public Vertex< V>
{
public:
	BOOST_CONCEPT_USAGE( Vertex3D)
	{
		unit_type x = v_.x();
		unit_type y = v_.y();
		unit_type z = v_.z();
	}

private:
	V v_;
};

template< typename V>
class HomogenousVertex3D: public Vertex3D< V>
{
public:
	BOOST_CONCEPT_USAGE( HomogenousVertex3D)
	{
		unit_type w = v_.w();
	}

private:
	V v_;
};

template< typename V>
class Vertex2D: public Vertex<V>
{
public:
	BOOST_CONCEPT_USAGE( Vertex2D)
	{
		unit_type x = v_.x();
		unit_type y = v_.y();
	}

private:
	V v_;
};

template< typename V>
class HomogenousVertex2D: public Vertex2D< V>
{
public:
	BOOST_CONCEPT_USAGE( HomogenousVertex2D)
	{
		unit_type w = v_.w();
	}

private:
	V v_;
};

namespace impl
{

template< typename V, unsigned D>
struct is_vertex
{
	BOOST_STATIC_CONSTANT( bool, value = 
		(is_a< V, vertex_tag>::value 
		&& has_dimensions< typename V::coord_system, D>::value));
};


} // namespace impl

} // geometry

#endif // GEOMETRY_VERTEX_CONCEPT_HPP
