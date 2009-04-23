#ifndef GEOMETRY_HOMOGENOUS_VERTEX_HPP
#define GEOMETRY_HOMOGENOUS_VERTEX_HPP

#include "geometry/vertex.hpp"
#include "geometry/transformation_concept.hpp"
#include "geometry/homogenous/hcoord_system_concept.hpp"
#include <boost/concept/requires.hpp>
#include <boost/concept/assert.hpp>

namespace geometry
{
namespace impl
{

/// \ingroup geometry
/// \brief It provides common methods for all vertex classes which are based on homogenous coordinate representations.
/// \tparam CS the coordinate system used by the vertex.
/// \tparam Derived the derived class, used to access the data from.
/// \details
///		This template depends on the most derived class for two reasons: 
///		\li Optimized data initialization: the vertex with three dimensions need constructor with four parameters, the 
///			one with two dimensions need a constructor with two paramaters. Since there is no optimized way of passing 
///			different number of parameters to the base class constructors, the data is put in the most derived classes 
///			and initialized by the most derived constructors. 
///		\li Most of the generic methods can be expressed using generic representation of the coordinates, so the base 
///			class needs access to the specialized data, so Derived template parameter is used to perform a static cast 
///			for getting to that data. Note that the derived class should declare this class as friend, in order to 
///			allow direct access to the private data.
template< typename CS, typename Derived>
class hvertex_base: public vertex_base< CS>
{
	BOOST_CONCEPT_ASSERT( (HCoordSystem<CS>));

protected:
	typedef typename CS::pos_rep pos_rep;
public:
	pos_rep normalized() const { return CS::normalize_coords( this->position()); }
	void normalized( pos_rep& pos) const { CS::normalize_coords( this->position(), pos); }

	template< typename T>
	BOOST_CONCEPT_REQUIRES( ((Transformation<T>)), (Derived&))
		transform( const T& tr)
	{
		tr.transform( this->position());
		return static_cast<Derived&>(*this);
	}

	template< typename T>
	BOOST_CONCEPT_REQUIRES( ((Transformation<T>)), (Derived))
		transformed( const T& tr) const
	{
		return Derived( tr.transformed( this->position()));
	}


private:
	const coord_vector& position() const { return static_cast< const Derived*>( this)->position_; }
	coord_vector& position() { return static_cast< Derived*>( this)->position_; }
};

} // namespace impl

/// \ingroup geometry
/// \brief It specializes vertex implementation for two dimensional, homogenous coordinate system.
/// \tparam CS the coordinate system type.
template< typename CS>
class vertex< CS, typename impl::enabled_for<CS,2,hcoord_system_tag>::type>
	: public impl::hvertex_base< CS, vertex< CS, typename impl::enabled_for<CS,2,hcoord_system_tag>::type> >
{
	typedef vertex< CS, typename impl::enabled_for<CS,2,hcoord_system_tag>::type> my_type_;
	typedef impl::hvertex_base< CS, my_type_> base_type_;

	template< typename C, typename D> friend class impl::hvertex_base;
public:
	/// \brief It initializes the coordinates of the vertex.
	vertex( const unit_type& x, const unit_type& y, const unit_type& w = 1.0)
		: position_( x, y, w)
	{
	}

	/// \brief It sets the origin coordinates.
	vertex()
		: position_( 0, 0, 1)
	{
	}

	/// \brief It sets the coordinates from coordinate specific internal representation.
	vertex( const coord_vector& coords)
		: position_( coords) { }

	/// \brief It sets the coordinates from the position internal representation
	vertex( const pos_rep& coords)
		: position_( coords.at<0>(), coords.at<1>(), 1)
	{
	}

	/// \brief Coordinate accessors. It normalize the coordinate value before returning it.
	/// \{
	unit_type x() const 
	{ 
		return position_.at<0>()/this->w(); 
	}

	unit_type y() const 
	{ 
		return position_.at<1>()/this->w(); 
	}

	unit_type w() const 
	{ 
		return position_.at<2>(); 
	}
	/// \}

	/// \brief It checks whether the vertex is valid.
	/// \details
	///		A vertex is valid if its coordinates (X,Y) are valid, finite numbers and if the weight coordinate is a 
	///		valid, finite number.
	bool is_valid() const
	{
		return unit_traits_type::is_valid_number( position_.at<0>())
			&& unit_traits_type::is_valid_number( position_.at<1>())
			&& unit_traits_type::is_valid_number( position_.at<2>());
	}

private:
	coord_vector position_;
};


/// \ingroup geometry
/// \brief It specializes vertex implementation for three dimensional, homogenous coordinate system.
/// \tparam CS the coordinate system type.
template< typename CS>
class vertex< CS, typename impl::enabled_for<CS,3,hcoord_system_tag>::type>
	: public impl::hvertex_base< CS,vertex< CS, typename impl::enabled_for<CS,3,hcoord_system_tag>::type>>
{
	typedef vertex< CS, typename impl::enabled_for<CS,3,hcoord_system_tag>::type> my_type_;
	typedef impl::hvertex_base< CS, my_type_> base_type_;

	template< typename C, typename D> friend class impl::hvertex_base;
public:
	/// \brief It sets the coordinates from coordinate specific internal representation.
	vertex( const coord_vector& pos)
		: position_( pos) { }

	/// \brief It initializes the coordinates of the vertex.
	vertex( const unit_type& x, const unit_type& y, const unit_type& z, const unit_type& w = 1.0)
		: position_( x, y, z, w)
	{
	}

	/// \brief It sets the origin coordinates.
	vertex()
		: position_( 0, 0, 0, 1) { }

	/// \brief It sets the coordinates from the position internal representation
	vertex( const pos_rep& coords)
		: position_( coords.at<0>(), coords.at<1>(), coords.at<2>(), 1)
	{
	}

	/// \brief Coordinate accessors. It normalize the coordinate value before returning it.
	/// \{
	unit_type x() const 
	{ 
		return position_.at<0>() / this->w(); 
	}

	unit_type y() const 
	{ 
		return position_.at<1>() / this->w(); 
	}

	unit_type z() const 
	{
		return position_.at<2>() / this->w(); 
	}

	unit_type w() const 
	{ 
		return position_.at<3>(); 
	}
	/// \}

	/// \brief It checks whether the vertex is valid.
	/// \details
	///		A vertex is valid if its coordinates (X,Y,Z) are valid, finite numbers and if the weight coordinate is a 
	///		valid, finite number.
	bool is_valid() const
	{
		return unit_traits_type::is_valid_number( position_.at<0>())
			&& unit_traits_type::is_valid_number( position_.at<1>())
			&& unit_traits_type::is_valid_number( position_.at<2>())
			&& unit_traits_type::is_valid_number( position_.at<3>());
	}

private:
	coord_vector position_;
};


} // namespace geometry


#endif // GEOMETRY_HOMOGENOUS_VERTEX_HPP
