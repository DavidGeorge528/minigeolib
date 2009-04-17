#include "geometry/homogenous/intersections.hpp"
#include "geometry/homogenous/vertex.hpp"
#include "geometry/homogenous/hcoord_system.hpp"
#include "geometry/homogenous/direction.hpp"
#include "geometry/line.hpp"
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

typedef boost::mpl::list< 
		boost::mpl::pair< float_line, float_vertex>, 
		boost::mpl::pair< double_line, double_vertex> >
	tested_lines;


BOOST_AUTO_TEST_CASE_TEMPLATE( test_line_intersection, P, tested_lines)
{
	typedef typename P::first line;
	typedef typename P::second vertex;
	typedef typename vertex::unit_type unit_type;
	typedef typename vertex::unit_traits_type unit_traits_type;
	typedef typename vertex::coord_system::length_type length_type;
	typedef typename line::direction_type direction;

	// Intersection case
	line 
		lx( vertex( 1,3,10), direction( 1,0,0)),
		ly( vertex( 2,1,10), direction( 0,1,0));
	vertex v = intersect<vertex>( lx, ly);
	ALGTEST_CHECK_EQUAL_UNIT( 2, v.x());
	ALGTEST_CHECK_EQUAL_UNIT( 3, v.y());
	ALGTEST_CHECK_EQUAL_UNIT( 10, v.z());

	// Intersection is the same as base vertex
	lx = line( vertex( 3,2,10), direction( 1,0,0)),
	ly = line( vertex( 3,2,10), direction( 0,1,0));
	v = intersect<vertex>( lx, ly);
	ALGTEST_CHECK_EQUAL_UNIT( 3, v.x());
	ALGTEST_CHECK_EQUAL_UNIT( 2, v.y());
	ALGTEST_CHECK_EQUAL_UNIT( 10, v.z());

	// Parallel lines
	lx = line( vertex( 1, 2, 3), direction( 1, 1, 1));
	ly = line( vertex( 5, 4, 3), direction( 1, 1, 1));
	v = intersect<vertex>( lx, ly);
	ALGTEST_CHECK_INVALID_UNIT( v.x());
	ALGTEST_CHECK_INVALID_UNIT( v.y());
	ALGTEST_CHECK_INVALID_UNIT( v.z());

	// Skewed lines
	lx = line( vertex( 3,2,0), direction( 1,0,0)),
	ly = line( vertex( 3,2,10), direction( 0,1,0));
	v = intersect<vertex>( lx, ly);
	ALGTEST_CHECK_INVALID_UNIT( v.x());
	ALGTEST_CHECK_INVALID_UNIT( v.y());
	ALGTEST_CHECK_INVALID_UNIT( v.z());

	// Superimposed lines
	lx = line( vertex( 1, 2, 3), direction( 1, 1, 1));
	ly = line( vertex( 1, 2, 3), direction( 1, 1, 1));
	v = intersect<vertex>( lx, ly);
	ALGTEST_CHECK_INVALID_UNIT( v.x());
	ALGTEST_CHECK_INVALID_UNIT( v.y());
	ALGTEST_CHECK_INVALID_UNIT( v.z());
}

} // namespace
