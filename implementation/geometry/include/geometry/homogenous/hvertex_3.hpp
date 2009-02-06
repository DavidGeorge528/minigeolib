#ifndef GEOMETRY_HOMOGENOUS_HVERTEX_3_HPP
#define GEOMETRY_HOMOGENOUS_HVERTEX_3_HPP

#include "geometry/vertex.hpp"
#include "geometry/homogenous/hcoord_system_3.hpp"

namespace geometry
{

// DOC:
// TEST:
template< typename U, typename UT>
class vertex< hcoord_system< 3, U, UT> >
{
	typedef vertex< hcoord_system< 3, U, UT> > my_type_;
public:
	typedef hcoord_system< 3, U, UT> coord_system;
	typedef typename coord_system::unit_type unit_type;
	typedef typename coord_system::unit_traits_type unit_traits_type;
	typedef typename coord_system::position_type position_type;

	vertex( const unit_type& x, const unit_type& y, const unit_type& z, const unit_type& w = 1.0)
		: position_( x, y, z, w) { }

	vertex()
		: position_( 0, 0, 0, 1) { }

	const unit_type& x() const { return position_.x(); }
	const unit_type& y() const { return position_.y(); }
	const unit_type& z() const { return position_.z(); }
	const unit_type& w() const { return position_.w(); }

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

#endif // GEOMETRY_HOMOGENOUS_HVERTEX_3_HPP
