#ifndef GEOMETRY_VERTEX_HPP
#define GEOMETRY_VERTEX_HPP

#include "geometry/coord_system_concept.hpp"
#include "geometry/coord_system_tags.hpp"
#include <boost/static_assert.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>

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

private:
	typedef typename boost::enable_if_c< coord_system::DIMENSIONS == 3>::type enable_if_3d;
	typedef typename boost::enable_if_c< 
		boost::is_same< typename coord_system::system_type, hcoord_system_tag>::value >::type enable_if_homogenous;

public:
// TODO: Check position concept
	vertex( const unit_type& x, const unit_type& y, const unit_type& z, const unit_type& w = 1.0,
			enable_if_3d* = NULL, enable_if_homogenous* = NULL)
		: position_( x, y, z, w) { }

	vertex( enable_if_3d* = NULL, enable_if_homogenous* = NULL)
		: position_( 0, 0, 0, 1) { }

	const unit_type& x( typename boost::enable_if_c< coord_system::DIMENSIONS >=1>::type* = NULL) const 
	{ 
		// TODO: Check 1D concept
		return position_.at<0>(); 
	}
	
	const unit_type& y( typename boost::enable_if_c< coord_system::DIMENSIONS >=2>::type* = NULL) const 
	{ 
		// TODO: Check 2D Concept	
		return position_.at<1>(); 
	}
	
	const unit_type& z( typename boost::enable_if_c< coord_system::DIMENSIONS >=3>::type* = NULL) const 
	{
		// TODO: CHeck 3D COncept
		return position_.at<2>(); 
	}

	const unit_type& w( enable_if_3d* = NULL, enable_if_homogenous* = NULL) const 
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
