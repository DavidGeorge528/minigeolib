#include "geometry/homogenous/direction.hpp"
#include "geometry/homogenous/hcoord_system.hpp"
#include "../tests_common.hpp"
#include "../test_traits.hpp"
#include <boost/mpl/list.hpp>

namespace 
{

using namespace geometry;

typedef boost::mpl::list< 
	direction< hcoord_system< 2, float, algebra::unit_traits< float> > >,
	direction< hcoord_system< 2, double, algebra::unit_traits< double> > >
> tested_types;


BOOST_AUTO_TEST_CASE_TEMPLATE( test_initialization, D, tested_types)
{
	typedef D direction;
	typedef typename direction::unit_type unit_type;

	direction d( 2, 3);

	unit_type n = d.dx()*d.dx() + d.dy()*d.dy();
	ALGTEST_CHECK_EQUAL_UNIT( 1, n);
}

} // namespace
