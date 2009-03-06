#include "algebra/epsilon_tolerance.hpp"
#include "../test_traits.hpp"
#include "../tests_common.hpp"

namespace
{
using namespace algebra;

typedef boost::mpl::list< float, double> tested_types;

BOOST_AUTO_TEST_CASE_TEMPLATE( test_initialization, U, tested_types)
{
	typedef U unit_type;
	typedef epsilon_tolerance< unit_type> tolerance;

	unit_type e = 1;
	tolerance t1( e);
	tolerance t2;

	BOOST_CHECK_EQUAL( e, t1.epsilon());
	BOOST_CHECK_EQUAL( 
		std::numeric_limits< unit_type>::is_integer ? 0 : std::numeric_limits< unit_type>::min()
		, t2.epsilon());
}

// ---------------------------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE_TEMPLATE( test_equal, U, tested_types)
{
	typedef U unit_type;
	typedef epsilon_tolerance< unit_type> tolerance;

	unit_type eps = 2;
	tolerance t( eps);
	unit_type 
		v1 = 10, 
		v2 = v1, 
		v3 = v1 + eps/2.0, 
		v4 = v1 - eps/2.0, 
		v5 = v1 + eps, 
		v6 = v1 - eps, 
		v7 = v1 + eps + 1, 
		v8 = v1 - eps - 1;

	BOOST_CHECK( t.equals( v1, v2));
	BOOST_CHECK( t.equals( v1, v3));
	BOOST_CHECK( t.equals( v1, v4));
	BOOST_CHECK( t.equals( v1, v5));
	BOOST_CHECK( t.equals( v1, v6));
	BOOST_CHECK( !t.equals( v1, v7));
	BOOST_CHECK( !t.equals( v1, v8));
}

} // namespace
