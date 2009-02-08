#ifndef GEOMETRY_HOMOGENOUS_HCOORD_SYSTEM_HPP
#define GEOMETRY_HOMOGENOUS_HCOORD_SYSTEM_HPP

#include "geometry/coord_system_tags.hpp"
#include "algebra/vector.hpp"
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
		typedef algebra::vector< D+1, U, UT> position_type;
		typedef unit_type length_type;

		BOOST_STATIC_ASSERT( (boost::is_same< U, unit_type>::value));
	};
}

// DOC
template< unsigned D, typename U, typename UT = algebra::unit_traits< U> >
class hcoord_system: public impl::hcoord_base< D, U, UT>
{
public:
	// TEST:
	static length_type distance( const position_type& p1, const position_type& p2)
	{
		return 0;
	}
};


template< typename U, typename UT >
class hcoord_system< 3, U, UT>: public impl::hcoord_base< 3, U, UT>
{
public:
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

template< typename U, typename UT >
class hcoord_system< 2, U, UT>: public impl::hcoord_base< 2, U, UT>
{
public:
	// TEST:
	static length_type distance( const position_type& p1, const position_type& p2)
	{
		unit_type 
			dx = (p2.x()/p2.w() - p1.x()/p1.w()),
			dy = (p2.y()/p2.w() - p1.y()/p1.w());
		return std::sqrt( dx*dx + dy*dy);
	}
};

} // namespace geometry

#endif // GEOMETRY_HOMOGENOUS_HCOORD_SYSTEM_HPP
