#ifndef OGLRENDER_HCOMMANDS_3_HPP
#define OGLRENDER_HCOMMANDS_3_HPP

#include "ogl_render/impl/commands.hpp"
#include "geometry/homogenous/hcoord_system.hpp"
#include "geometry/vertex.hpp"
#include <boost/type_traits/is_same.hpp>
#include <boost/static_assert.hpp>

namespace ogl_render
{
namespace impl
{

template< typename UT>
struct commands< geometry::hcoord_system< 3, float, UT> >
{
private:
	typedef geometry::hcoord_system< 3, float, UT> coord_system;
public:
	BOOST_STATIC_ASSERT( (boost::is_same< float, typename UT::unit_type>::value));

	static void vertex( const geometry::vertex< coord_system>& v)
	{
		glVertex4f( v.x(), v.y(), v.z(), v.w());
	}
};


template< typename UT>
struct commands< geometry::hcoord_system< 3, double, UT> >
{
private:
	typedef geometry::hcoord_system< 3, double, UT> coord_system;
public:
	BOOST_STATIC_ASSERT( (boost::is_same< double, typename UT::unit_type>::value));

	static void vertex( const geometry::vertex< coord_system>& v)
	{
		glVertex4d( v.x(), v.y(), v.z(), v.w());
	}
};

} // impl
} // ogl_render

#endif // OGLRENDER_HCOMMANDS_3_HPP
