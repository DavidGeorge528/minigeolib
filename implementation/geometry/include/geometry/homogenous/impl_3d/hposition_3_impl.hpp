#ifndef GEOMETRY_IMPL_HPOSITION_3_IMPL_HPP
#define GEOMETRY_IMPL_HPOSITION_3_IMPL_HPP

#include "algebra/vector.hpp"

namespace geometry
{
namespace impl_3d
{

// DOC:
// TEST:
template< typename U, typename UT>
class hposition_3_impl: public algebra::vector< 4, U, UT>
{
	typedef hposition_3_impl< U, UT> my_type_;
	typedef algebra::vector< 4, U, UT> base_type_;
public:
	hposition_3_impl(): base_type_( 0,0,0,1) { }

	hposition_3_impl( const unit_type& x, const unit_type& y, const unit_type& z, const unit_type& w = 1.0)
		: base_type_( x, y, z, w) {}

	hposition_3_impl( const base_type_& orig)
		: base_type_( orig) { }

	hposition_3_impl& operator=( const base_type_& orig)
	{
		base_type_::operator=( orig);
		return *this;
	}

	const unit_type& x() const { return this->at<0>(); }
	void set_x( const unit_type& new_val) { this->at<0>() = new_val; }
	const unit_type& y() const { return this->at<1>(); }
	void set_y( const unit_type& new_val) { this->at<1>() = new_val; }
	const unit_type& z() const { return this->at<2>(); }
	void set_z( const unit_type& new_val) { this->at<2>() = new_val; }
	const unit_type& w() const { return this->at<3>(); }
	void set_w( const unit_type& new_val) { this->at<3>() = new_val; }

	hposition_3_impl& normalize()
	{
		at<0>() /= w();
		at<1>() /= w();
		at<2>() /= w();
		at<3>() = 1;
	}

	hposition_3_impl normalized() const
	{
		return hposition_3_impl( x()/w(), y()/w(), z()/w(), 1);
	}
};

} // namespace impl_3d
} // namespace geometry

#endif // GEOMETRY_IMPL_HPOSITION_3_IMPL_HPP
