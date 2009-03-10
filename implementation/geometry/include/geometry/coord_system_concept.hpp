#ifndef GEOMETRY_COORD_SYSTEM_CONCEPT_HPP
#define GEOMETRY_COORD_SYSTEM_CONCEPT_HPP

namespace geometry
{

/// \brief 
///		The coordinate system provides basic setup and operations for algorithms. These basic operations depend on 
///		the coordinate system so this class helps establishing an abstraction layer to be used by algorithms.
template< typename C>
class CoordSystem
{
	typedef C concept;

	/// Require definition of number of spatial dimensions
	enum { CHECKED_DIMENSIONS = concept::DIMENSIONS};
	/// Require position type definition.
	typedef typename concept::coord_vector coord_vector;

	/// Require distance type definition
	typedef typename concept::length_type length_type;

	/// Require compile-time type identification
	typedef typename concept::system_type system_type;
};

} // namespace geometry

#endif // GEOMETRY_COORD_SYSTEM_CONCEPT_HPP
