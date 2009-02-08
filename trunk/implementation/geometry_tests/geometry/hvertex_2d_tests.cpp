#include "geometry/homogenous/vertex_2d.hpp"
#include "geometry/homogenous/hcoord_system.hpp"
#include "geometry/homogenous/transformation_2d.hpp"
#include "../tests_common.hpp"
#include "../test_traits.hpp"
#include <boost/mpl/list.hpp>

namespace 
{

using namespace geometry;

typedef boost::mpl::list< 
	vertex< hcoord_system< 2, float, algebra::unit_traits< float> > >,
	vertex< hcoord_system< 2, double, algebra::unit_traits< double> > >
> tested_types;


BOOST_AUTO_TEST_CASE_TEMPLATE( test_full_init_constructor, V, tested_types)
{
	typedef V vertex;
	typedef typename vertex::unit_type unit_type;
	vertex v( 1, 2, 3);

	ALGTEST_CHECK_EQUAL_UNIT( 1, v.x());
	ALGTEST_CHECK_EQUAL_UNIT( 2, v.y());
	ALGTEST_CHECK_EQUAL_UNIT( 3, v.w());
}

// ---------------------------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE_TEMPLATE( test_default_constructor, V, tested_types)
{
	typedef V vertex;
	typedef typename vertex::unit_type unit_type;
	vertex v;

	ALGTEST_CHECK_EQUAL_UNIT( 0, v.x());
	ALGTEST_CHECK_EQUAL_UNIT( 0, v.y());
	ALGTEST_CHECK_EQUAL_UNIT( 1, v.w());
}

} // namespace