#ifndef GEOMETRY_VERTEX_HPP
#define GEOMETRY_VERTEX_HPP

#include "geometry/coord_system_concept.hpp"
#include "geometry/coord_system_tags.hpp"
#include "geometry/impl/enablers.hpp"
#include <boost/static_assert.hpp>

namespace geometry
{

// DOC
template< typename CS >
class vertex
{
	typedef vertex<CS> my_type_;

public:
	typedef CS coord_system;
	typedef typename coord_system::unit_type unit_type;
	typedef typename coord_system::unit_traits_type unit_traits_type;
	typedef typename coord_system::position_type position_type;

public:
// TODO: Check position concept
	vertex( const unit_type& x, const unit_type& y, const unit_type& z, const unit_type& w = 1.0,
			GEOMETRY_ENABLED_IF_3D, GEOMETRY_ENABLED_IF_HOMOGENEOUS)
		: position_( x, y, z, w) { }

	vertex( GEOMETRY_ENABLED_IF_3D, GEOMETRY_ENABLED_IF_HOMOGENEOUS)
		: position_( 0, 0, 0, 1) { }

	const unit_type& x( GEOMETRY_ENABLED_IF_AT_LEAST_1D) const 
	{ 
		// TODO: Check 1D concept
		return position_.at<0>(); 
	}
	
	const unit_type& y( GEOMETRY_ENABLED_IF_AT_LEAST_2D) const 
	{ 
		// TODO: Check 2D Concept	
		return position_.at<1>(); 
	}
	
	const unit_type& z( GEOMETRY_ENABLED_IF_AT_LEAST_3D) const 
	{
		// TODO: CHeck 3D COncept
		return position_.at<2>(); 
	}

	const unit_type& w( GEOMETRY_ENABLED_IF_3D, GEOMETRY_ENABLED_IF_HOMOGENEOUS) const 
	{ 
		// TODO: Check 3D Homogeneous concept
		return position_.at<3>(); 
	}

	template< typename T>
	my_type_& transform( const T& tr)
	{
		// TODO: Check transformation concept
		tr.transform( position_);
		return *this;
	}

	template< typename T>
	my_type_ transformed( const T& tr)
	{
		// TODO: Check transformation concept
		return tr.transformed( position_);
	}

private:
	position_type position_;
};


} // geometry

#endif // GEOMETRY_VERTEX_HPP
