#include "geometry/homogenous/parallelism_3d.hpp"
#include "geometry/homogenous/hcoord_system.hpp"
#include "geometry/homogenous/direction_3d.hpp"
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

} // namespace
