#ifndef GEOMETRY_HOMOGENOUS_DIRECTION_3D_HPP
#define GEOMETRY_HOMOGENOUS_DIRECTION_3D_HPP

#include "geometry/direction.hpp"
#include "algebra/vector.hpp"
#include "geometry/impl/enablers.hpp"
#include "geometry/plane_concept.hpp"
#include <boost/concept/assert.hpp>

namespace geometry
{

// DOC
template< typename CS>
class direction< CS, typename impl::enabled_for< CS, 3, hcoord_system_tag>::type>
	: public impl::direction_base< CS>
{
	typedef algebra::vector<3, unit_type, unit_traits_type> representation;
public:
	direction( const unit_type& dx, const unit_type& dy, const unit_type& dz)
		: components_( dx, dy, dz) 
	{
		this->normalize();
	}

	template< typename P>
	direction( const P& plane, typename boost::enable_if< impl::is_plane<P,3> >::type* = NULL)
		: components_( plane.a(), plane.b(), plane.c())
	{
		BOOST_CONCEPT_ASSERT( (Plane<P>));
		this->normalize();
	}

	const unit_type& dx() const { return components_.at<0>(); }
	const unit_type& dy() const { return components_.at<1>(); }
	const unit_type& dz() const { return components_.at<2>(); }

private:
	representation components_;

	void normalize()
	{
		unit_type norm = std::sqrt( dx()*dx() + dy()*dy() + dz()*dz());
		components_.at<0>() /= norm;
		components_.at<1>() /= norm;
		components_.at<2>() /= norm;
	}
};

} // geometry

#endif // GEOMETRY_HOMOGENOUS_DIRECTION_3D_HPP
