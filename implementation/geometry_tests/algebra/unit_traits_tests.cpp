#include "algebra/unit_traits.hpp"
#include "../tests_common.hpp"
#include "../test_traits.hpp"

namespace
{

using namespace algebra;

typedef boost::mpl::list< float, double> tested_types;

BOOST_AUTO_TEST_CASE_TEMPLATE( test_infinity, T, tested_types)
{
	typedef unit_traits< T> unit_traits;

	BOOST_REQUIRE( std::numeric_limits<T>::has_infinity);
	BOOST_CHECK_EQUAL( std::numeric_limits<T>::infinity(), unit_traits::infinity());
	BOOST_CHECK( unit_traits::is_infinity( unit_traits::infinity()));
	BOOST_CHECK( !unit_traits::is_not_a_number( unit_traits::infinity()));
	BOOST_CHECK( !unit_traits::is_valid_number( unit_traits::infinity()));
}

// ---------------------------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE_TEMPLATE( test_not_a_number, T, tested_types)
{
	typedef unit_traits< T> unit_traits;
	BOOST_REQUIRE( std::numeric_limits<T>::has_signaling_NaN);
	BOOST_REQUIRE( std::numeric_limits<T>::has_quiet_NaN);
	BOOST_CHECK( unit_traits::is_not_a_number( unit_traits::not_a_number()));
	BOOST_CHECK( !unit_traits::is_valid_number( unit_traits::not_a_number()));
}

} // namespace
