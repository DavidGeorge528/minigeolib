#ifndef GEOMETRY_HOMOGENOUS_DIRECTION_HPP
#define GEOMETRY_HOMOGENOUS_DIRECTION_HPP

#include "geometry/direction.hpp"
#include "geometry/plane_concept.hpp"
#include <boost/concept/assert.hpp>
#include <cmath>

namespace geometry
{
namespace impl
{

/// \ingroup geometry
/// \brief It provides the common methods for homogenous direction concept implementations.
/// \tparam CS the coordinate system used by the transformation.
/// \tparam Derived the derived class, used to access the data from.
/// \details
///		This template depends on the most derived class for two reasons: 
///		\li Optimized data initialization: the direction with three dimensions need constructor with 3 parameters, 
///			the one with two dimensions need a constructor with 2 paramaters. Since there is no optimized way of passing 
///			different number of parameters to the base class constructors, the data is put in the most derived classes 
///			and initialized by the most derived constructors. 
///		\li Most of the generic methods can be expressed using generic representation of direction and coordinates, so 
///			the base class needs access to the specialized data, so Derived template parameter is used to perform a 
///			static cast for getting to that data. Note that the derived class should declare this class as friend, in 
///			order to allow direct access to the private data.
template< typename CS, typename Derived>
class hdirection_base: public impl::direction_base<CS>
{
public:
	typedef typename CS::dir_rep dir_rep;

protected:
	/// \brief It ensures that the norm of the direction is always one.
	void normalize()
	{
		this->dir() /= std::sqrt( CS::squared_norm( this->dir()));
	}
private:
	dir_rep& dir() { return static_cast< Derived*>( this)->components_; }
	const dir_rep& dir() const { return static_cast< const Derived*>( this)->components_; }
};

} // namespace impl


/// \ingroup geometry
/// \brief It implements the direction for two dimensional, homogenous coordinate system.
template< typename CS>
class direction< CS, typename impl::enabled_for< CS, 2, hcoord_system_tag>::type>
	: public impl::hdirection_base< CS, direction< CS, typename impl::enabled_for< CS, 2, hcoord_system_tag>::type> >
{
	template< typename C, typename D> friend class impl::hdirection_base;
public:
	/// \brief Explicit initialization of direction components.
	/// \details
	///		It makes sure that the norm of the direction is always 1.
	direction( const unit_type& dx, const unit_type& dy)
		: components_( dx, dy)
	{
		this->normalize();
	}

	/// \brief Explicit initialization of direction components.
	/// \details
	///		It makes sure that the norm of the direction is always 1.
	/// \todo: unit test
	direction( const dir_rep& repr)
		: components_( repr) 
	{
		this->normalize();
	}

	/// \brief Components access
	/// \{
	const unit_type& dx() const { return components_.at<0>(); }
	const unit_type& dy() const { return components_.at<1>(); }
	/// \}

private:
	dir_rep components_;
};

/// \ingroup geometry
/// \brief It implements the direction for three dimensional, homogenous coordinate system.
template< typename CS>
class direction< CS, typename impl::enabled_for< CS, 3, hcoord_system_tag>::type>
	: public impl::hdirection_base< CS, direction< CS, typename impl::enabled_for< CS, 3, hcoord_system_tag>::type> >
{
	template< typename C, typename D> friend class impl::hdirection_base;
public:
	/// \brief Explicit initialization of direction components.
	/// \details
	///		It makes sure that the norm of the direction is always 1.
	direction( const unit_type& dx, const unit_type& dy, const unit_type& dz)
		: components_( dx, dy, dz) 
	{
		this->normalize();
	}

	/// \brief Explicit initialization of direction components.
	/// \details
	///		It makes sure that the norm of the direction is always 1.
	/// \todo: Unit test
	direction( const dir_rep& repr)
		: components_( repr)
	{
		this->normalize();
	}

	/// \brief It creates a direction equivalent with the normal direction of the provided plane.
	/// \tparam P the type of the plane, implementing the Plane concept.
	/// \param plane the plane providing the normal direction.
	template< typename P>
	direction( const P& plane, typename boost::enable_if< impl::is_plane<P,3> >::type* = NULL)
		: components_( plane.a(), plane.b(), plane.c())
	{
		BOOST_CONCEPT_ASSERT( (Plane<P>));
		this->normalize();
	}

	/// \brief Access to direction components.
	/// \{
	const unit_type& dx() const { return components_.at<0>(); }
	const unit_type& dy() const { return components_.at<1>(); }
	const unit_type& dz() const { return components_.at<2>(); }
	/// \}

private:
	dir_rep components_;
};

} // namespace geometry

#endif // GEOMETRY_HOMOGENOUS_DIRECTION_HPP
