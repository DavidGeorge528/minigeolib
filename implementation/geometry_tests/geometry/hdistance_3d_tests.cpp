#include "geometry/homogenous/distances_3d.hpp"
#include "geometry/homogenous/distances_2d.hpp" // keep this include to check on SFINAE
#include "geometry/homogenous/hcoord_system.hpp"
#include "geometry/homogenous/vertex_3d.hpp"
#include "geometry/line.hpp"
#include "geometry/homogenous/direction_3d.hpp"
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

typedef boost::mpl::list< float_vertex, double_vertex> tested_vertices;

typedef boost::mpl::list<
		boost::mpl::pair< float_vertex, float_line>, 
		boost::mpl::pair< double_vertex, double_line> 
	> tested_line_vertex;

typedef boost::mpl::list< float_line, double_line> tested_line_to_line;

BOOST_AUTO_TEST_CASE_TEMPLATE( test_distance, V, tested_vertices)
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

} // namespace
