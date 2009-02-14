#include "geometry/plane.hpp"
#include "geometry/homogenous/vertex_3d.hpp"
#include "geometry/homogenous/hcoord_system.hpp"
#include "geometry/plane_concept.hpp"
#include "../tests_common.hpp"
#include "../test_traits.hpp"
#include <boost/mpl/list.hpp>

namespace 
{

	using namespace geometry;

	typedef boost::mpl::list< 
		plane< hcoord_system< 3, float, algebra::unit_traits< float> > >,
		plane< hcoord_system< 3, double, algebra::unit_traits< double> > >
	> tested_types;

BOOST_AUTO_TEST_CASE_TEMPLATE( test_default_constructor, P, tested_types)
{
	BOOST_CONCEPT_ASSERT( (Plane< P>));
	typedef P plane_type;
	typedef typename plane_type::unit_type unit_type;

	plane_type p;
	ALGTEST_CHECK_EQUAL_UNIT( 0, p.a());
	ALGTEST_CHECK_EQUAL_UNIT( 0, p.b());
	ALGTEST_CHECK_EQUAL_UNIT( 0, p.c());
	ALGTEST_CHECK_EQUAL_UNIT( 0, p.d());
}

// ---------------------------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE_TEMPLATE( test_explicit_initialization, P, tested_types)
{
	BOOST_CONCEPT_ASSERT( (Plane< P>));
	typedef P plane_type;
	typedef typename plane_type::unit_type unit_type;

	unit_type a = 10, b = 20, c = 30, d = 40;
	plane_type p( a, b, c, d);
	ALGTEST_CHECK_EQUAL_UNIT( a, p.a());
	ALGTEST_CHECK_EQUAL_UNIT( b, p.b());
	ALGTEST_CHECK_EQUAL_UNIT( c, p.c());
	ALGTEST_CHECK_EQUAL_UNIT( d, p.d());
}

} // namespace
