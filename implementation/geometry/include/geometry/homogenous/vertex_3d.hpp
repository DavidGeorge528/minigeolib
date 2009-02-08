#ifndef GEOMETRY_HOMOGENOUS_VERTEX_3_HPP
#define GEOMETRY_HOMOGENOUS_VERTEX_3_HPP

#include "geometry/vertex.hpp"

namespace geometry
{

// DOC
template< typename CS>
class vertex< CS, typename impl::enabled_for<CS,3,hcoord_system_tag>::type>
	: public impl::vertex_base< CS>
{
	typedef vertex<CS> my_type_;

public:
	// TODO: Check position concept
	vertex( const unit_type& x, const unit_type& y, const unit_type& z, const unit_type& w = 1.0)
		: position_( x, y, z, w) { }

	vertex()
		: position_( 0, 0, 0, 1) { }

	const unit_type& x() const 
	{ 
		// TODO: Check 1D concept
		return position_.at<0>(); 
	}

	const unit_type& y() const 
	{ 
		// TODO: Check 2D Concept	
		return position_.at<1>(); 
	}

	const unit_type& z() const 
	{
		// TODO: CHeck 3D COncept
		return position_.at<2>(); 
	}

	const unit_type& w() const 
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


#endif // GEOMETRY_HOMOGENOUS_VERTEX_3_HPP
