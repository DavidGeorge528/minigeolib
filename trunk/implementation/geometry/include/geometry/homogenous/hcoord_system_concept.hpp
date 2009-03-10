#ifndef GEOMETRY_HCOORD_SYSTEM_CONCEPT_HPP
#define GEOMETRY_HCOORD_SYSTEM_CONCEPT_HPP

#include <geometry/coord_system_concept.hpp>

namespace geometry
{

// DOC:
template< typename C>
class hcoord_system_concept: coord_system_concept< C>
{
public:
	typedef typename C::coord_vector coord_vector;
	typedef typename C::pos_rep pos_rep;
	typedef typename C::dir_rep dir_rep;
	typedef typename C::transform_matrix transform_matrix;

	BOOST_CONCEPT_USAGE( hcoord_system_concept)
	{
		// TODO: Check coord vector
		// TODO: Check pos_rep
		// TODO: Check dir_rep
		// TODO: Check transform matrix
	}

private:

};

} // namespace geometry

#endif // GEOMETRY_HCOORD_SYSTEM_CONCEPT_HPP
