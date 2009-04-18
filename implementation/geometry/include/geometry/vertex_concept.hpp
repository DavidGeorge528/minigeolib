#ifndef GEOMETRY_VERTEX_CONCEPT_HPP
#define GEOMETRY_VERTEX_CONCEPT_HPP

#include "geometry/geometric_object_concept.hpp"
#include "geometry/impl/enablers.hpp"
#include <boost/concept/usage.hpp>

namespace geometry
{

struct vertex_tag { };

/// \ingroup geometry
/// \brief It checks the generic requirements of a vertex concept.
template< typename V>
class Vertex: public GeometricObject< V, vertex_tag>
{
public:
	typedef typename V::coord_vector coord_vector;
};

/// \ingroup geometry
/// \brief It checks the requirements of a 3D vertex concept.
template< typename V>
class Vertex3D: public Vertex< V>
{
public:
	BOOST_CONCEPT_USAGE( Vertex3D)
	{
		unit_type x = v_.x();
		unit_type y = v_.y();
		unit_type z = v_.z();

		// Initialization using three coordinates
		V v1( x, y, z);
		// Require default constructor
		V v2;
	}

private:
	V v_;
	unit_type x_, y_, z_;
	unit_type coords_[3];
};


/// \ingroup geometry
/// \brief It checks the requirements of a 2D vertex concept.
template< typename V>
class Vertex2D: public Vertex<V>
{
public:
	BOOST_CONCEPT_USAGE( Vertex2D)
	{
		unit_type x = v_.x();
		unit_type y = v_.y();

		// Initialization using three coordinates
		V v1( x, y);
		// Require default constructor
		V v2;
	}

private:
	V v_;
	unit_type x_, y_, z_;
	unit_type coords_[2];
};


namespace impl
{

/// \brief It checks that the given type is a vertex.
/// \tparam V the type to be checked.
/// \tparam D the expected number of dimensions of the coordinate system.
/// \tparam CSID the expected type identifier of the coordinate system. Should be void if not needed.
/// \details
///		The default implementation assumes that the given type is not a vertex type. The vertex checking relies on the
///		mechanism of partial template specialization, so in case a new vertex type is implemented, a specialization of
///		this class should be defined for that type of vertex.
template< typename V, unsigned D, typename CSID = void>
struct is_vertex
{
	BOOST_STATIC_CONSTANT( bool, value = false);
};

} // namespace impl

} // geometry

#endif // GEOMETRY_VERTEX_CONCEPT_HPP
