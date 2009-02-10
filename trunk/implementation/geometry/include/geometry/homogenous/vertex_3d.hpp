#ifndef GEOMETRY_HOMOGENOUS_VERTEX_3_HPP
#define GEOMETRY_HOMOGENOUS_VERTEX_3_HPP

#include "geometry/vertex.hpp"
#include "geometry/transformation_concept.hpp"
#include <boost/concept/requires.hpp>

namespace geometry
{

// DOC
template< typename CS>
class vertex< CS, typename impl::enabled_for<CS,3,hcoord_system_tag>::type>
	: public impl::vertex_base< CS>
{
	typedef vertex<CS> my_type_;

protected:
	vertex( const position_type& pos)
		: position_( pos) { }
public:
	// TODO: Check position concept
	vertex( const unit_type& x, const unit_type& y, const unit_type& z, const unit_type& w = 1.0)
		: position_( x, y, z, w) { }

	vertex()
		: position_( 0, 0, 0, 1) { }

	const unit_type& x() const 
	{ 
		return position_.at<0>(); 
	}

	const unit_type& y() const 
	{ 
		return position_.at<1>(); 
	}

	const unit_type& z() const 
	{
		return position_.at<2>(); 
	}

	const unit_type& w() const 
	{ 
		return position_.at<3>(); 
	}

	template< typename T>
	BOOST_CONCEPT_REQUIRES( ((Transformation<T>)), (my_type_&))
		transform( const T& tr)
	{
		tr.transform( position_);
		return *this;
	}

	template< typename T>
	BOOST_CONCEPT_REQUIRES( ((Transformation<T>)), (my_type_))
		transformed( const T& tr) const
	{
		return tr.transformed( position_);
	}

private:
	position_type position_;
};

} // geometry


#endif // GEOMETRY_HOMOGENOUS_VERTEX_3_HPP
