#include "geometry/homogenous/parallelism_3d.hpp"
#include "geometry/homogenous/hcoord_system.hpp"
#include "geometry/homogenous/direction_3d.hpp"
#include "geometry/homogenous/vertex.hpp"
#include "geometry/plane.hpp"
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
		boost::mpl::list< 
			line< hcoord_system_float>, vertex< hcoord_system_float>, direction< hcoord_system_float> >,
		boost::mpl::list< 
			line< hcoord_system_double>, vertex< hcoord_system_double>, direction< hcoord_system_double> > 
	> tested_lines;

typedef boost::mpl::list<
		boost::mpl::list< 
			plane< hcoord_system_float>, vertex< hcoord_system_float>, direction< hcoord_system_float> >,
		boost::mpl::list< 
			plane< hcoord_system_double>, vertex< hcoord_system_double>, direction< hcoord_system_double> > 
	> tested_planes;

typedef boost::mpl::list<
	boost::mpl::list< 
		plane< hcoord_system_float>, line< hcoord_system_float>, 
		vertex< hcoord_system_float>, direction< hcoord_system_float> >,
	boost::mpl::list< 
		plane< hcoord_system_double>, line< hcoord_system_double>, 
		vertex< hcoord_system_double>, direction< hcoord_system_double> >
	> tested_planes_to_lines;

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


// ---------------------------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE_TEMPLATE( test_parallel_planes, T, tested_planes)
{
	using namespace boost::mpl;

	typedef typename at<T,int_<0> >::type plane_type;
	typedef typename plane_type::unit_type unit_type;
	typedef typename at<T,int_<1> >::type vertex_type;
	typedef typename at<T,int_<2> >::type direction_type;

	vertex_type base1( 1, 2, 3), base2( 5, 6, 7), base3( 10, 9, 8), base4( 20, 30, 10);
	direction_type d1( 10, 20, 30), d2( 1, 2, 3), d3( -1, -2, -3), d4( 11, 12, 13);
	plane_type p1( base1, d1), p2( base2, d2), p3( base3, d3), p4( base4, d4);

	algebra::epsilon_tolerance< unit_type> tolerance( 1e-6);
	BOOST_CHECK( are_parallel( p1, p2, tolerance));
	BOOST_CHECK( are_parallel( p1, p3, tolerance));
	BOOST_CHECK( are_parallel( p2, p3, tolerance));
	BOOST_CHECK( !are_parallel( p1, p4, tolerance));
	BOOST_CHECK( !are_parallel( p2, p4, tolerance));
	BOOST_CHECK( !are_parallel( p3, p4, tolerance));
	BOOST_CHECK( are_parallel( p1, p1, tolerance));
	BOOST_CHECK( are_parallel( p4, p4, tolerance));
}

// ---------------------------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE_TEMPLATE( test_parallel_plane_to_line, T, tested_planes_to_lines)
{
	using namespace boost::mpl;

	typedef typename at<T,int_<0> >::type plane_type;
	typedef typename at<T,int_<1> >::type line_type;
	typedef typename at<T,int_<2> >::type vertex_type;
	typedef typename at<T,int_<3> >::type direction_type;
	typedef typename plane_type::unit_type unit_type;

	vertex_type base( 1, 2, 3);
	direction_type norm( 1, 0, 0);
	plane_type plane( base, norm);

	vertex_type lbase( 10, 20, 50);
	direction_type d1( 0, 1, 0);
	direction_type d2( 0, 0, 1);
	direction_type d3( 0, 1, 1);
	direction_type d4( 1, 2, 3);

	algebra::epsilon_tolerance< unit_type> tolerance( 1e-6);

	line_type l1( lbase, d1), l2( lbase, d2), l3( lbase, d3), l4( lbase, d4);
	BOOST_CHECK( are_parallel( plane, l1, tolerance));
	BOOST_CHECK( are_parallel( l1, plane, tolerance));
	BOOST_CHECK( are_parallel( plane, l2, tolerance));
	BOOST_CHECK( are_parallel( l2, plane, tolerance));
	BOOST_CHECK( are_parallel( plane, l3, tolerance));
	BOOST_CHECK( are_parallel( l3, plane, tolerance));
	BOOST_CHECK( !are_parallel( plane, l4, tolerance));
	BOOST_CHECK( !are_parallel( l4, plane, tolerance));
}

} // namespace
