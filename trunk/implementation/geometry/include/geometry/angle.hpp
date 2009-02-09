#ifndef GEOMETRY_ANGLE_HPP
#define GEOMETRY_ANGLE_HPP

#include "algebra/unit_base.hpp"

namespace geometry
{

struct radians { };
struct degrees { };

namespace impl
{
template< typename U>
class angle_base
{
public:
	static U PI() { return 3.141592653589793284626433; }
};

} // impl

template< typename U, typename Tag, typename UT = algebra::unit_traits< U> >
class angle;

// TEST
template< typename U, typename UT>
class angle< U, radians, UT>: public algebra::unit_base< U, radians, UT>, public impl::angle_base<U>
{
	typedef algebra::unit_base< U, radians, UT> base_type_;
	typedef angle< U, degrees, UT> angle_in_degrees;
public:
	angle() { }
	angle( const unit_type& val): base_type_( val) { }
	angle( const angle_in_degrees& val)
		: base_type_( val.value() * PI() / 180.0) { }
	
	operator angle_in_degrees() const
	{
		return (unit_type)(*this) * 180.0 / PI();
	}
};


// TEST
template< typename U, typename UT>
class angle< U, degrees, UT>: public algebra::unit_base< U, degrees, UT>, public impl::angle_base<U>
{
	typedef algebra::unit_base< U, degrees, UT> base_type_;
	typedef angle< U, radians, UT> angle_in_radians;
public:
	angle() { }
	angle( const unit_type& val): base_type_( val) { }
	angle( const angle_in_radians& val)
		: base_type_( val.value_() * 180.0 / PI()) { }

	operator angle_in_radians() const
	{
		return (unit_type)(*this) * PI() / 180.0;
	}
};

} // geometry

#endif // GEOMETRY_ANGLE_HPP

