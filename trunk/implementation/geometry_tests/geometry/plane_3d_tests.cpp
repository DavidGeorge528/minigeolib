#include "geometry/plane.hpp"
#include "geometry/homogenous/vertex_3d.hpp"
#include "geometry/homogenous/hcoord_system.hpp"
#include "geometry/plane_concept.hpp"
#include "geometry/homogenous/direction_3d.hpp"
#include "geometry/homogenous/distances_3d.hpp"
#include "../tests_common.hpp"
#include "../test_traits.hpp"
#include <boost/mpl/list.hpp>

namespace 
{

using namespace geometry;

typedef boost::mpl::list< 
	plane< hcoord_system< 3, float, algebra::unit_traits< float> > >,
	plane< hcoord_system< 3, double, algebra::unit_traits< double> > >
> tested_types;

BOOST_AUTO_TEST_CASE_TEMPLATE( test_default_constructor, P, tested_types)
{
	BOOST_CONCEPT_ASSERT( (Plane< P>));
	typedef P plane_type;
	typedef typename plane_type::unit_type unit_type;

	plane_type p;
	ALGTEST_CHECK_EQUAL_UNIT( 0, p.a());
	ALGTEST_CHECK_EQUAL_UNIT( 0, p.b());
	ALGTEST_CHECK_EQUAL_UNIT( 0, p.c());
	ALGTEST_CHECK_EQUAL_UNIT( 0, p.d());
}

// ---------------------------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE_TEMPLATE( test_explicit_initialization, P, tested_types)
{
	BOOST_CONCEPT_ASSERT( (Plane< P>));
	typedef P plane_type;
	typedef typename plane_type::unit_type unit_type;

	unit_type a = 10, b = 20, c = 30, d = 40;
	plane_type p( a, b, c, d);
	ALGTEST_CHECK_EQUAL_UNIT( a, p.a());
	ALGTEST_CHECK_EQUAL_UNIT( b, p.b());
	ALGTEST_CHECK_EQUAL_UNIT( c, p.c());
	ALGTEST_CHECK_EQUAL_UNIT( d, p.d());
}

// ---------------------------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE_TEMPLATE( test_vertex_normal_init, P, tested_types)
{
	BOOST_CONCEPT_ASSERT( (Plane<P>));
	typedef P plane_type;
	typedef typename plane_type::unit_type unit_type;
	typedef vertex< typename plane_type::coord_system> vertex_type;
	typedef direction< typename plane_type::coord_system> dir_type;

	plane_type xy_plane( vertex_type( 0,0,0), dir_type( 0, 0, 1));
	plane_type yz_plane( vertex_type( 0,0,0), dir_type( 1, 0, 0));
	plane_type zx_plane( vertex_type( 0,0,0), dir_type( 0, 1, 0));

	ALGTEST_CHECK_EQUAL_UNIT( 0, xy_plane.a());
	ALGTEST_CHECK_EQUAL_UNIT( 0, xy_plane.b());
	ALGTEST_CHECK_EQUAL_UNIT( 1, xy_plane.c());
	ALGTEST_CHECK_EQUAL_UNIT( 0, xy_plane.d());

	ALGTEST_CHECK_EQUAL_UNIT( 1, yz_plane.a());
	ALGTEST_CHECK_EQUAL_UNIT( 0, yz_plane.b());
	ALGTEST_CHECK_EQUAL_UNIT( 0, yz_plane.c());
	ALGTEST_CHECK_EQUAL_UNIT( 0, yz_plane.d());

	ALGTEST_CHECK_EQUAL_UNIT( 0, zx_plane.a());
	ALGTEST_CHECK_EQUAL_UNIT( 1, zx_plane.b());
	ALGTEST_CHECK_EQUAL_UNIT( 0, zx_plane.c());
	ALGTEST_CHECK_EQUAL_UNIT( 0, zx_plane.d());

	dir_type normal( 20, 30, 50);
	vertex_type pos( 10, 20, 30);
	plane_type plane( pos, normal);
	ALGTEST_CHECK_EQUAL_UNIT( normal.dx(), plane.a());
	ALGTEST_CHECK_EQUAL_UNIT( normal.dy(), plane.b());
	ALGTEST_CHECK_EQUAL_UNIT( normal.dz(), plane.c());
	ALGTEST_CHECK_EQUAL_UNIT( -(normal.dx()*pos.x() + normal.dy()*pos.y() + normal.dz()*pos.z()), plane.d());

	// Take one point at 10 units outside the plane
	unit_type expected_distance_1 = 10;
	vertex_type outside_vertex_1( 
		pos.x() + normal.dx()*expected_distance_1, 
		pos.y() + normal.dy()*expected_distance_1, 
		pos.z() + normal.dz()*expected_distance_1);

	// Take one point at -10 units outside the plane
	unit_type expected_distance_2 = -10;
	vertex_type outside_vertex_2( 
		pos.x() + normal.dx()*expected_distance_2, 
		pos.y() + normal.dy()*expected_distance_2, 
		pos.z() + normal.dz()*expected_distance_2);
	// Normal base vertex should be on the plane (0 distance)
	unit_type d1 = distance( pos, plane),
		d2 = distance( outside_vertex_1, plane),
		d3 = distance( outside_vertex_2, plane);
	ALGTEST_CHECK_SMALL( d1);
	// Positive distance check
	ALGTEST_CHECK_EQUAL_UNIT( expected_distance_1, d2);
	// Negative distance (vertex on the oposite side of the plane) check.
	ALGTEST_CHECK_EQUAL_UNIT( expected_distance_2, d3);

	// TODO: Implement cross check with projection calculation
}

// --------------------------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE_TEMPLATE( test_three_point_init, P, tested_types)
{
	BOOST_CONCEPT_ASSERT( (Plane<P>));
	typedef P plane_type;
	typedef typename plane_type::unit_type unit_type;
	typedef vertex< typename plane_type::coord_system> vertex_type;
	typedef direction< typename plane_type::coord_system> dir_type;

	plane_type xy_plane( vertex_type( 0,0,0), vertex_type( 1, 0, 0), vertex_type( 0,1,0));
	plane_type yz_plane( vertex_type( 0,0,0), vertex_type( 0, 1, 0), vertex_type( 0,0,1));
	plane_type zx_plane( vertex_type( 0,0,0), vertex_type( 1, 0, 0), vertex_type( 0,0,1));

	ALGTEST_CHECK_SMALL( distance( vertex_type( 0,0,0), xy_plane));
	ALGTEST_CHECK_SMALL( distance( vertex_type( 1,0,0), xy_plane));
	ALGTEST_CHECK_SMALL( distance( vertex_type( 0,1,0), xy_plane));
	ALGTEST_CHECK_SMALL( distance( vertex_type( 0,2,0), xy_plane));
	ALGTEST_CHECK_EQUAL_UNIT( 1, distance( vertex_type( 1,1,1), xy_plane));

	ALGTEST_CHECK_SMALL( distance( vertex_type( 0,0,0), yz_plane));
	ALGTEST_CHECK_SMALL( distance( vertex_type( 0,1,0), yz_plane));
	ALGTEST_CHECK_SMALL( distance( vertex_type( 0,0,1), yz_plane));
	ALGTEST_CHECK_SMALL( distance( vertex_type( 0,0,2), yz_plane));
	ALGTEST_CHECK_EQUAL_UNIT( 1, distance( vertex_type( 1,1,1), yz_plane));

	ALGTEST_CHECK_SMALL( distance( vertex_type( 0,0,0), zx_plane));
	ALGTEST_CHECK_SMALL( distance( vertex_type( 1,0,0), zx_plane));
	ALGTEST_CHECK_SMALL( distance( vertex_type( 0,0,1), zx_plane));
	ALGTEST_CHECK_SMALL( distance( vertex_type( 0,0,2), zx_plane));
	ALGTEST_CHECK_EQUAL_UNIT( -1, distance( vertex_type( 1,1,1), zx_plane));
}

// --------------------------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE_TEMPLATE( test_normal, P, tested_types)
{
	BOOST_CONCEPT_ASSERT( (Plane<P>));
	typedef P plane_type;
	typedef typename plane_type::unit_type unit_type;
	typedef vertex< typename plane_type::coord_system> vertex_type;
	typedef direction< typename plane_type::coord_system> dir_type;

	dir_type normal( 20, 30, 50);
	vertex_type pos( 10, 20, 30);
	plane_type plane( pos, normal);
	dir_type expected_normal = plane.normal< dir_type>();
	ALGTEST_CHECK_EQUAL_UNIT( normal.dx(), expected_normal.dx());
	ALGTEST_CHECK_EQUAL_UNIT( normal.dy(), expected_normal.dy());
	ALGTEST_CHECK_EQUAL_UNIT( normal.dz(), expected_normal.dz());
}

} // namespace
