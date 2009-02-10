#ifndef GEOMETRY_HOMOGENOUS_DIRECTION_2D_HPP
#define GEOMETRY_HOMOGENOUS_DIRECTION_2D_HPP

#include "geometry/direction.hpp"
#include "algebra/vector.hpp"

namespace geometry
{

// DOC
template< typename CS>
class direction< CS, typename impl::enabled_for< CS, 2, hcoord_system_tag>::type>
	: public impl::direction_base< CS>
{
	typedef algebra::vector<2, unit_type, unit_traits_type> representation;
public:
	direction( const unit_type& dx, const unit_type& dy)
		: components_( dx, dy)
	{
		this->normalize();
	}

	const unit_type& dx() const { return components_.at<0>(); }
	const unit_type& dy() const { return components_.at<1>(); }

private:
	representation components_;

	void normalize()
	{
		unit_type norm = std::sqrt( dx()*dx() + dy()*dy());
		components_.at<0>() /= norm;
		components_.at<1>() /= norm;
	}
};

} // geometry

#endif // GEOMETRY_HOMOGENOUS_DIRECTION_2D_HPP
