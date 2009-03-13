#include "geometry/homogenous/distances.hpp"
#include "geometry/homogenous/hcoord_system.hpp"
#include "geometry/homogenous/vertex.hpp"
#include "geometry/plane.hpp"
#include "geometry/line.hpp"
#include "geometry/homogenous/direction.hpp"
#include "algebra/epsilon_tolerance.hpp"
#include "../tests_common.hpp"
#include "../test_traits.hpp"
#include <boost/mpl/list.hpp>

namespace 
{

using namespace geometry;

typedef hcoord_system< 3, float, algebra::unit_traits< float> > float_hcoord_system;
typedef hcoord_system< 3, double, algebra::unit_traits< double> > double_hcoord_system;
typedef vertex< float_hcoord_system> float_vertex;
typedef vertex< double_hcoord_system> double_vertex;
typedef line< float_hcoord_system> float_line;
typedef line< double_hcoord_system> double_line;
typedef plane< float_hcoord_system> float_plane;
typedef plane< double_hcoord_system> double_plane;

typedef boost::mpl::list< float_vertex, double_vertex> tested_vertices;

typedef boost::mpl::list<
		boost::mpl::pair< float_vertex, float_line>, 
		boost::mpl::pair< double_vertex, double_line> 
	> tested_line_vertex;

typedef boost::mpl::list< float_line, double_line> tested_line_to_line;
typedef boost::mpl::list< float_plane, double_plane> tested_plane_to_plane;
typedef boost::mpl::list< 
		boost::mpl::pair< float_vertex, float_plane>,
		boost::mpl::pair< double_vertex, double_plane> > tested_vertex_to_plane;

BOOST_AUTO_TEST_CASE_TEMPLATE( test_vertex_to_vertex_distance, V, tested_vertices)
{
	typedef V vertex;
	typedef typename vertex::unit_type unit_type;
	typedef typename vertex::unit_traits_type unit_traits_type;
	typedef typename vertex::coord_system::length_type length_type;

	vertex v1( 10, 20, 30, 10), v2( -1, -2, -3);
	length_type expected_distance = std::sqrt( unit_type(4+16+36));
	ALGTEST_CHECK_EQUAL_UNIT( expected_distance, distance( v1, v2));
	ALGTEST_CHECK_EQUAL_UNIT( unit_traits_type::zero(), distance( v1, v1));
}

// ---------------------------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE_TEMPLATE( test_distance_as_predicate, V, tested_vertices)
{
	using namespace boost;

	typedef V vertex;
	typedef typename vertex::unit_type unit_type;
	typedef typename vertex::coord_system::length_type length_type;

	vertex v1( 10, 20, 10, 20);
	std::list< vertex> lv;
	lv.push_back( vertex(0,0,0,0));
	lv.push_back( vertex(2,2,2, 20));
	std::vector< unit_type> distances( lv.size());
	std::transform( lv.begin(), lv.end(), distances.begin(), bind( distance<vertex>, _1, v1));
}

// ---------------------------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE_TEMPLATE( test_distance_vertex_line, P, tested_line_vertex)
{
	typedef typename P::first vertex;
	typedef typename P::second line;
	typedef typename vertex::unit_type unit_type;
	typedef typename vertex::coord_system::length_type length_type;
	typedef direction< typename vertex::coord_system> direction;

	line lx( vertex( 0,0,0), direction( 1, 0, 0));
	line ly( vertex( 0,0,0), direction( 0, 1, 0));
	line lz( vertex( 0,0,0), direction( 0, 0, 1));

	ALGTEST_CHECK_EQUAL_UNIT( 1, distance( vertex( 0, 10, 0, 10), lx));
	ALGTEST_CHECK_EQUAL_UNIT( 2, distance( vertex( 0, 0, 20, 10), ly));
	ALGTEST_CHECK_EQUAL_UNIT( 3, distance( vertex( 30, 0, 0, 10), lz));

	ALGTEST_CHECK_EQUAL_UNIT( 1, distance( vertex( 30, 10, 0, 10), lx));
	ALGTEST_CHECK_EQUAL_UNIT( 2, distance( vertex( 0, 40, 20, 10), ly));
	ALGTEST_CHECK_EQUAL_UNIT( 3, distance( vertex( 30, 0, 50, 10), lz));

	ALGTEST_CHECK_EQUAL_UNIT( 0, distance( vertex( 10, 0, 0,10), lx));
	ALGTEST_CHECK_EQUAL_UNIT( 0, distance( vertex( 0, 10, 0,10), ly));
	ALGTEST_CHECK_EQUAL_UNIT( 0, distance( vertex( 0, 0, 10,10), lz));

	ALGTEST_CHECK_EQUAL_UNIT( 0, distance( vertex( 0, 0, 0), lx));
	ALGTEST_CHECK_EQUAL_UNIT( 0, distance( vertex( 0, 0, 0), ly));
	ALGTEST_CHECK_EQUAL_UNIT( 0, distance( vertex( 0, 0, 0), lz));


	ALGTEST_CHECK_EQUAL_UNIT( 1, distance( lx, vertex( 0, 10, 0, 10)));
	ALGTEST_CHECK_EQUAL_UNIT( 2, distance( ly, vertex( 0, 0, 20, 10)));
	ALGTEST_CHECK_EQUAL_UNIT( 3, distance( lz, vertex( 30, 0, 0, 10)));

	ALGTEST_CHECK_EQUAL_UNIT( 1, distance( lx, vertex( 30, 10, 0, 10)));
	ALGTEST_CHECK_EQUAL_UNIT( 2, distance( ly, vertex( 0, 40, 20, 10)));
	ALGTEST_CHECK_EQUAL_UNIT( 3, distance( lz, vertex( 30, 0, 50, 10)));

	ALGTEST_CHECK_EQUAL_UNIT( 0, distance( lx, vertex( 10, 0, 0,10)));
	ALGTEST_CHECK_EQUAL_UNIT( 0, distance( ly, vertex( 0, 10, 0,10)));
	ALGTEST_CHECK_EQUAL_UNIT( 0, distance( lz, vertex( 0, 0, 10,10)));

	ALGTEST_CHECK_EQUAL_UNIT( 0, distance( lx, vertex( 0, 0, 0)));
	ALGTEST_CHECK_EQUAL_UNIT( 0, distance( ly, vertex( 0, 0, 0)));
	ALGTEST_CHECK_EQUAL_UNIT( 0, distance( lz, vertex( 0, 0, 0)));
}

// ---------------------------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE_TEMPLATE( test_line_to_line_distance, L, tested_line_to_line)
{
	typedef L line;
	typedef typename line::unit_type unit_type;
	typedef vertex< typename line::coord_system> vertex;
	typedef direction< typename line::coord_system> direction;

	// Test non-intersecting line
	line l1( vertex( 0,0,0), direction( 1,0,0));
	line l2( vertex( 0,0,1), direction( 0,1,0));
	ALGTEST_CHECK_EQUAL_UNIT( 1, distance( l1, l2));

	// Test parallel lines
	line l3( vertex( 0,0,1), l1.dir());
	ALGTEST_CHECK_EQUAL_UNIT( 1, distance( l1, l3));

	// Test intersecting lines
	line l4( l1.base(), direction( 0,0,1));
	ALGTEST_CHECK_SMALL( distance( l1, l4));

	// Test same line
	ALGTEST_CHECK_SMALL( distance( l1, l1));

	// Test coincidence
	line l5( l1.base(), l1.dir());
	ALGTEST_CHECK_SMALL( distance(l1,l5));
}

// ---------------------------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE_TEMPLATE( test_plane_to_plane_distance, P, tested_plane_to_plane)
{
	typedef P plane_type;
	typedef typename plane_type::unit_type unit_type;
	typedef typename plane_type::coord_system coord_system;
	typedef direction< coord_system> direction_type;
	typedef vertex< coord_system> vertex_type;

	vertex_type v1( 1, 1, 1), v2( 2, 2, 2);
	direction_type d( 1, 0, 0);
	plane_type p1( v1, d), p2( v2, d);
	plane_type p3( v2, direction_type( 1, 1, 1));

	ALGTEST_CHECK_EQUAL_UNIT( unit_type( -1.0), distance( p1, p2));
	ALGTEST_CHECK_EQUAL_UNIT( unit_type( 1.0), distance( p2, p1));
	ALGTEST_CHECK_SMALL( distance( p3, p1));
	ALGTEST_CHECK_SMALL( distance( p1, p3));
	ALGTEST_CHECK_SMALL( distance( p1, p1));
	ALGTEST_CHECK_SMALL( distance( p3, p3));
}

// ---------------------------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE_TEMPLATE( test_vertex_normal_init, P, tested_vertex_to_plane)
{
	typedef typename P::second plane_type;
	typedef typename plane_type::unit_type unit_type;
	typedef typename P::first vertex_type;
	typedef direction< typename plane_type::coord_system> dir_type;

	BOOST_CONCEPT_ASSERT( (Plane<plane_type>));
	BOOST_CONCEPT_ASSERT( (Vertex<vertex_type>));

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
	ALGTEST_CHECK_SMALL( distance( pos, plane));
	ALGTEST_CHECK_SMALL( distance( plane, pos));
	// Positive distance check
	ALGTEST_CHECK_EQUAL_UNIT( expected_distance_1, distance( outside_vertex_1, plane));
	ALGTEST_CHECK_EQUAL_UNIT( expected_distance_1, distance( plane, outside_vertex_1));
	// Negative distance (vertex on the oposite side of the plane) check.
	ALGTEST_CHECK_EQUAL_UNIT( expected_distance_2, distance( outside_vertex_2, plane));
	ALGTEST_CHECK_EQUAL_UNIT( expected_distance_2, distance( plane, outside_vertex_2));
}

} // namespace
