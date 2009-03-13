#include "geometry/homogenous/angles.hpp"
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

typedef boost::mpl::list< float_plane, double_plane> tested_plane_to_plane;

const double PI = 3.1415926535897932384626433;

BOOST_AUTO_TEST_CASE_TEMPLATE( test_dihedral_angle, P, tested_plane_to_plane)
{
	typedef P plane_type;
	typedef typename plane_type::unit_type unit_type;
	typedef typename plane_type::coord_system coord_system;
	typedef direction< coord_system> direction_type;
	typedef vertex< coord_system> vertex_type;

	vertex_type v( 0,0,0);
	direction_type d1( 1,0,0), d2( 0,1,0), d3( 0,1,1);
	plane_type p1( v, d1), p2( v, d2), p3( v, d3);

	ALGTEST_CHECK_EQUAL_UNIT( PI/2.0, angle( p1, p2));
	ALGTEST_CHECK_EQUAL_UNIT( PI/4.0, angle( p3, p2));
}

} // namespace
