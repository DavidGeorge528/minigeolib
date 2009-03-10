#ifndef GEOMETRY_HCOORD_SYSTEM_CONCEPT_HPP
#define GEOMETRY_HCOORD_SYSTEM_CONCEPT_HPP

#include <geometry/coord_system_concept.hpp>

namespace geometry
{

// DOC:
template< typename C>
class HCoordSystem: CoordSystem< C>
{
public:
	typedef typename C::coord_vector coord_vector;
	typedef typename C::pos_rep pos_rep;
	typedef typename C::dir_rep dir_rep;
	typedef typename C::transform_matrix transform_matrix;

	BOOST_CONCEPT_USAGE( HCoordSystem)
	{
		// TODO: Check coord vector
		// TODO: Check pos_rep
		// TODO: Check dir_rep
		// TODO: Check transform matrix

		// Require squared_norm static method.
		unit_ = C::squared_norm( dir_);
		// Require coordinate normalization static methods
		pos_ = C::normalize_coords( coords_);
		C::normalize_coords( coord_, pos_);
	}

private:
	unit_type unit_;
	coord_vector coords_;
	pos_rep pos_;
	dir_rep dir_;
};

} // namespace geometry

#endif // GEOMETRY_HCOORD_SYSTEM_CONCEPT_HPP
