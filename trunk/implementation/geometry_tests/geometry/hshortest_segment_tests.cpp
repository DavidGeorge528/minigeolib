#include "geometry/homogenous/shortest_segment.hpp"
#include "geometry/homogenous/hcoord_system.hpp"
#include "geometry/homogenous/vertex.hpp"
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

BOOST_AUTO_TEST_CASE_TEMPLATE( test_shortest_segm_btw_lines, P, tested_lines)
{
	typedef typename P::first line;
	typedef typename P::second vertex;
	typedef typename vertex::unit_type unit_type;
	typedef typename vertex::unit_traits_type unit_traits_type;
	typedef typename vertex::coord_system::length_type length_type;
	typedef typename line::direction_type direction;

	// Test happy flow - bases are also the edges of the resulted segments
	line 
		lx( vertex( 3,2,0), direction( 1,0,0)),
		ly( vertex( 3,2,10), direction( 0,1,0));
	std::pair< vertex, vertex> segment;
	segment = shortest_segment<vertex>( lx, ly);
	ALGTEST_CHECK_EQUAL_UNIT( 3, segment.first.x());
	ALGTEST_CHECK_EQUAL_UNIT( 2, segment.first.y());
	ALGTEST_CHECK_EQUAL_UNIT( 0, segment.first.z());
	ALGTEST_CHECK_EQUAL_UNIT( 3, segment.second.x());
	ALGTEST_CHECK_EQUAL_UNIT( 2, segment.second.y());
	ALGTEST_CHECK_EQUAL_UNIT( 10, segment.second.z());

	// Test happy flow - bases are not the edges of the resulted segment
	lx = line( vertex( 1,3,5), direction( 1,0,0));
	ly = line( vertex( 2,1,10), direction( 0,1,0));
	segment = shortest_segment<vertex>( lx, ly);
	ALGTEST_CHECK_EQUAL_UNIT( 2, segment.first.x());
	ALGTEST_CHECK_EQUAL_UNIT( 3, segment.first.y());
	ALGTEST_CHECK_EQUAL_UNIT( 5, segment.first.z());
	ALGTEST_CHECK_EQUAL_UNIT( 2, segment.second.x());
	ALGTEST_CHECK_EQUAL_UNIT( 3, segment.second.y());
	ALGTEST_CHECK_EQUAL_UNIT( 10, segment.second.z());

	// Test happy flow - directions are oposite
	lx = line( vertex( 1,3,5), direction( -1,0,0));
	ly = line( vertex( 2,1,10), direction( 0,-1,0));
	segment = shortest_segment<vertex>( lx, ly);
	ALGTEST_CHECK_EQUAL_UNIT( 2, segment.first.x());
	ALGTEST_CHECK_EQUAL_UNIT( 3, segment.first.y());
	ALGTEST_CHECK_EQUAL_UNIT( 5, segment.first.z());
	ALGTEST_CHECK_EQUAL_UNIT( 2, segment.second.x());
	ALGTEST_CHECK_EQUAL_UNIT( 3, segment.second.y());
	ALGTEST_CHECK_EQUAL_UNIT( 10, segment.second.z());

	// Test parallel lines
	lx = line( vertex( 1, 2, 3), direction( 1, 1, 1));
	ly = line( vertex( 5, 4, 3), direction( 1, 1, 1));
	segment = shortest_segment<vertex>( lx, ly);
	ALGTEST_CHECK_INVALID_UNIT( segment.first.x());
	ALGTEST_CHECK_INVALID_UNIT( segment.first.y());
	ALGTEST_CHECK_INVALID_UNIT( segment.first.z());
	ALGTEST_CHECK_INVALID_UNIT( segment.second.x());
	ALGTEST_CHECK_INVALID_UNIT( segment.second.y());
	ALGTEST_CHECK_INVALID_UNIT( segment.second.z());

	// Test lines that are superimposed
	lx = line( vertex( 1, 2, 3), direction( 1, 1, 1));
	ly = line( vertex( 2, 3, 4), direction( 1, 1, 1));
	segment = shortest_segment<vertex>( lx, ly);
	ALGTEST_CHECK_INVALID_UNIT( segment.first.x());
	ALGTEST_CHECK_INVALID_UNIT( segment.first.y());
	ALGTEST_CHECK_INVALID_UNIT( segment.first.z());
	ALGTEST_CHECK_INVALID_UNIT( segment.second.x());
	ALGTEST_CHECK_INVALID_UNIT( segment.second.y());
	ALGTEST_CHECK_INVALID_UNIT( segment.second.z());

	// Test same origin
	lx = line( vertex( 3,2,10), direction( 1,0,0));
	ly = line( vertex( 3,2,10), direction( 0,1,0));
	segment = shortest_segment<vertex>( lx, ly);
	ALGTEST_CHECK_EQUAL_UNIT( 3, segment.first.x());
	ALGTEST_CHECK_EQUAL_UNIT( 2, segment.first.y());
	ALGTEST_CHECK_EQUAL_UNIT( 10, segment.first.z());
	ALGTEST_CHECK_EQUAL_UNIT( 3, segment.second.x());
	ALGTEST_CHECK_EQUAL_UNIT( 2, segment.second.y());
	ALGTEST_CHECK_EQUAL_UNIT( 10, segment.second.z());

	// Test lines intersect
	lx = line( vertex( 1,3,5), direction( 1,0,0));
	ly = line( vertex( 2,1,5), direction( 0,1,0));
	segment = shortest_segment<vertex>( lx, ly);
	ALGTEST_CHECK_EQUAL_UNIT( 2, segment.first.x());
	ALGTEST_CHECK_EQUAL_UNIT( 3, segment.first.y());
	ALGTEST_CHECK_EQUAL_UNIT( 5, segment.first.z());
	ALGTEST_CHECK_EQUAL_UNIT( 2, segment.second.x());
	ALGTEST_CHECK_EQUAL_UNIT( 3, segment.second.y());
	ALGTEST_CHECK_EQUAL_UNIT( 5, segment.second.z());
}

} // namespace

