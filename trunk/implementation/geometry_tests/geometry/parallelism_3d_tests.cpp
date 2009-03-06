#include "geometry/homogenous/parallelism_3d.hpp"
#include "geometry/homogenous/hcoord_system.hpp"
#include "geometry/homogenous/direction_3d.hpp"
#include "geometry/homogenous/vertex_3d.hpp"
#include "geometry/line.hpp"
#include "../tests_common.hpp"
#include "../test_traits.hpp"
#include <boost/mpl/list.hpp>

namespace 
{
using namespace geometry;

typedef hcoord_system< 3, float> hcoord_system_float;
typedef hcoord_system< 3, double> hcoord_system_double;

typedef boost::mpl::list< 
	direction< hcoord_system_float>, 
	direction< hcoord_system_double> > tested_directions;

typedef boost::mpl::list<
	boost::mpl::list< line< hcoord_system_float>, vertex< hcoord_system_float>, direction< hcoord_system_float> >,
	boost::mpl::list< line< hcoord_system_double>, vertex< hcoord_system_double>, direction< hcoord_system_double> > > tested_lines;

// ---------------------------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE_TEMPLATE( test_parallel_directions, D, tested_directions)
{
	typedef D direction_type;
	typedef typename direction_type::unit_type unit_type;

	direction_type d1( 10, 20, 30), d2( 1, 2, 3), d3( -1, -2, -3), d4( 11, 12, 13);
	algebra::epsilon_tolerance< unit_type> tolerance( 1e-6);
	BOOST_CHECK( are_parallel( d1, d2, tolerance));
	BOOST_CHECK( are_parallel( d1, d3, tolerance));
	BOOST_CHECK( are_parallel( d2, d3, tolerance));
	BOOST_CHECK( !are_parallel( d1, d4, tolerance));
	BOOST_CHECK( !are_parallel( d2, d4, tolerance));
	BOOST_CHECK( !are_parallel( d3, d4, tolerance));
	BOOST_CHECK( are_parallel( d1, d1, tolerance));
	BOOST_CHECK( are_parallel( d4, d4, tolerance));
}

// ---------------------------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE_TEMPLATE( test_parallel_lines, T, tested_lines)
{
	using namespace boost::mpl;

	typedef typename at<T,int_<0> >::type line_type;
	typedef typename line_type::unit_type unit_type;
	typedef typename at<T,int_<1> >::type vertex_type;
	typedef typename at<T,int_<2> >::type direction_type;

	vertex_type base1( 1, 2, 3), base2( 5, 6, 7), base3( 10, 9, 8), base4( 20, 30, 10);
	direction_type d1( 10, 20, 30), d2( 1, 2, 3), d3( -1, -2, -3), d4( 11, 12, 13);
	line_type l1( base1, d1), l2( base2, d2), l3( base3, d3), l4( base4, d4);

	algebra::epsilon_tolerance< unit_type> tolerance( 1e-6);
	BOOST_CHECK( are_parallel( l1, l2, tolerance));
	BOOST_CHECK( are_parallel( l1, l3, tolerance));
	BOOST_CHECK( are_parallel( l2, l3, tolerance));
	BOOST_CHECK( !are_parallel( l1, l4, tolerance));
	BOOST_CHECK( !are_parallel( l2, l4, tolerance));
	BOOST_CHECK( !are_parallel( l3, l4, tolerance));
	BOOST_CHECK( are_parallel( l1, l1, tolerance));
	BOOST_CHECK( are_parallel( l4, l4, tolerance));
}

} // namespace
