#ifndef GEOMETRY_HOMOGENOUS_HCOORD_SYSTEM_3_HPP
#define GEOMETRY_HOMOGENOUS_HCOORD_SYSTEM_3_HPP

#include "geometry/homogenous/hcoord_system.hpp"
#include "algebra/vector.hpp"
#include <boost/type_traits/is_same.hpp>
#include <boost/static_assert.hpp>

namespace geometry
{

// DOC:
template< typename U, typename UT>
class hcoord_system< 3, U, UT>
{
public:
	enum { DIMENSIONS = 3};
	typedef UT unit_traits_type;
	typedef typename unit_traits_type::unit_type unit_type;
	typedef hcoord_system_tag system_type;
	typedef algebra::vector< 4, U, UT> position_type;
	typedef unit_type length_type;

	BOOST_STATIC_ASSERT( (boost::is_same< U, unit_type>::value));

	// TEST:
	static length_type distance( const position_type& p1, const position_type& p2)
	{
		unit_type 
			dx = (p2.x()/p2.w() - p1.x()/p1.w()),
			dy = (p2.y()/p2.w() - p1.y()/p1.w()),
			dz = (p2.z()/p2.w() - p1.z()/p1.w());
		return std::sqrt( dx*dx + dy*dy + dz*dz);
	}
};

} // geometry

#endif // GEOMETRY_HOMOGENOUS_HCOORD_SYSTEM_3_HPP
