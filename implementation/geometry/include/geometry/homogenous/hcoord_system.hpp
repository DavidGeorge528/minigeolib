#ifndef GEOMETRY_HOMOGENOUS_HCOORD_SYSTEM_HPP
#define GEOMETRY_HOMOGENOUS_HCOORD_SYSTEM_HPP

#include "geometry/homogenous/hcoord_system_concept.hpp"
#include "algebra/vector.hpp"
#include "algebra/matrix.hpp"
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>

namespace geometry
{

namespace impl
{
	template< unsigned D, typename U, typename UT = algebra::unit_traits< U> >
	class hcoord_base
	{
	public:
		enum { DIMENSIONS = D};
		typedef UT unit_traits_type;
		typedef typename unit_traits_type::unit_type unit_type;
		typedef hcoord_system_tag system_type;
		typedef algebra::vector< DIMENSIONS + 1, unit_type, unit_traits_type> coord_vector;
		typedef algebra::vector< DIMENSIONS, unit_type, unit_traits_type> pos_rep;
		typedef algebra::vector< DIMENSIONS, unit_type, unit_traits_type> dir_rep;
		typedef algebra::matrix< DIMENSIONS + 1, DIMENSIONS + 1, unit_type, unit_traits_type> transform_matrix;
		typedef unit_type length_type;

		BOOST_STATIC_ASSERT( (boost::is_same< U, unit_type>::value));
	};
}

// DOC
template< unsigned D, typename U, typename UT = algebra::unit_traits< U> >
class hcoord_system: public impl::hcoord_base< D, U, UT>
{
public:
	
};


template< typename U, typename UT >
class hcoord_system< 3, U, UT>: public impl::hcoord_base< 3, U, UT>
{
public:
	/// \brief It converts homogenous coordinates to carthesian coordinates.
	/// \{
	static pos_rep normalize_coords( const coord_vector& coords)
	{
		return pos_rep( 
			coords.at<0>()/coords.at<3>(), 
			coords.at<1>()/coords.at<3>(),
			coords.at<2>()/coords.at<3>());
	}

	static void normalize_coords( const coord_vector& coords, pos_rep& pos)
	{
		pos.at<0>() = coords.at<0>() / coords.at<3>();
		pos.at<1>() = coords.at<1>() / coords.at<3>();
		pos.at<2>() = coords.at<2>() / coords.at<3>();
	}
	/// \}

	/// \brief It calculates the squared norm for the given direction representation.
	static unit_type squared_norm( const dir_rep& dir)
	{
		return dir.at<0>()*dir.at<0>() + dir.at<1>()*dir.at<1>() + dir.at<2>()*dir.at<2>();
	}
};

template< typename U, typename UT >
class hcoord_system< 2, U, UT>: public impl::hcoord_base< 2, U, UT>
{
public:
	/// \copydoc hcoord_system<3,U,UT>::normalize_coords
	static pos_rep normalize_coords( const coord_vector& coords)
	{
		return pos_rep( 
			coords.at<0>()/coords.at<2>(), 
			coords.at<1>()/coords.at<2>());
	}

	/// \copydoc hcoord_system<3,U,UT>::normalize_coords
	static void normalize_coords( const coord_vector& coords, pos_rep& pos)
	{
		pos.at<0>() = coords.at<0>() / coords.at<2>();
		pos.at<1>() = coords.at<1>() / coords.at<2>();
	}

	/// \copydoc hcoord_system<3,U,UT>::squared_norm
	static unit_type squared_norm( const dir_rep& dir)
	{
		return dir.at<0>()*dir.at<0>() + dir.at<1>()*dir.at<1>();
	}
};

} // namespace geometry

#endif // GEOMETRY_HOMOGENOUS_HCOORD_SYSTEM_HPP
