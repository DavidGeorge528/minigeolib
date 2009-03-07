#include "../test_traits.hpp"
#include "../tests_common.hpp"

namespace
{
using namespace algebra;

typedef boost::mpl::list< float, double> tested_types;

BOOST_AUTO_TEST_CASE_TEMPLATE( test_infinity, T, tested_types)
{
	BOOST_REQUIRE( std::numeric_limits<T>::has_infinity);
	T z1 = std::numeric_limits<T>::min(), z2 = z1, z3 = z2;
	T close_to_zero = z1*z2*z3;
	BOOST_CHECK( !unit_traits<T>::is_zero( z1));
	BOOST_CHECK( !unit_traits<T>::is_zero( z2));
	BOOST_CHECK( !unit_traits<T>::is_zero( z3));
	BOOST_CHECK( unit_traits<T>::is_zero( close_to_zero));
	
	T infinity = 1/close_to_zero;
	BOOST_CHECK( std::numeric_limits<T>::max() < infinity);
}

} // namespace
