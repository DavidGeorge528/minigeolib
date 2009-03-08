#include "geometry/homogenous/direction_3d.hpp"
#include "geometry/homogenous/hcoord_system.hpp"
#include "geometry/homogenous/vertex_3d.hpp"
#include "geometry/plane.hpp"
#include "../tests_common.hpp"
#include "../test_traits.hpp"
#include <boost/mpl/list.hpp>

namespace 
{

using namespace geometry;

typedef boost::mpl::list< 
	direction< hcoord_system< 3, float, algebra::unit_traits< float> > >,
	direction< hcoord_system< 3, double, algebra::unit_traits< double> > >
> tested_types;


BOOST_AUTO_TEST_CASE_TEMPLATE( test_initialization, D, tested_types)
{
	typedef D direction;
	typedef typename direction::unit_type unit_type;

	direction d( 2, 3, 4);

	unit_type n = d.dx()*d.dx() + d.dy()*d.dy() + d.dz()*d.dz();
	ALGTEST_CHECK_EQUAL_UNIT( 1, n);
}

// -----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE_TEMPLATE( test_init_from_plane, D, tested_types)
{
	BOOST_CONCEPT_ASSERT( (Direction3D< D>));
	typedef D dir_type;
	typedef plane< typename dir_type::coord_system> plane_type;
	typedef vertex< typename dir_type::coord_system> vertex_type;
	typedef typename dir_type::unit_type unit_type;

	dir_type expected_normal( 20, 30, 50);
	vertex_type pos( 10, 20, 30);
	plane_type plane( pos, expected_normal);

	dir_type normal( plane);
	ALGTEST_CHECK_EQUAL_UNIT( normal.dx(), expected_normal.dx());
	ALGTEST_CHECK_EQUAL_UNIT( normal.dy(), expected_normal.dy());
	ALGTEST_CHECK_EQUAL_UNIT( normal.dz(), expected_normal.dz());
}

} // namespace
