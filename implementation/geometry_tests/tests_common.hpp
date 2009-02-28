#ifndef TESTS_COMMON_HPP
#define TESTS_COMMON_HPP

#include "algebra/unit_traits.hpp"
#include <boost/mpl/list.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/at.hpp>
#include <boost/test/auto_unit_test.hpp>
#include <boost/test/test_case_template.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include <boost/test/test_tools.hpp>

typedef boost::mpl::list< float, double> algebraic_types;


/// \brief It checks the equality two values of type unit_type, using the tolerance specified by the test traits.
#define ALGTEST_CHECK_EQUAL_UNIT( E, O) \
	BOOST_CHECK_CLOSE( static_cast< unit_type>(E), O, test_traits< unit_type>::check_tolerance())

/// \brief It checks that the specified value is close to 0, using the tolerance specified by the test traits.
#define ALGTEST_CHECK_SMALL( O) \
	BOOST_CHECK_SMALL( O, test_traits<unit_type>::check_tolerance())

#endif // TESTS_COMMON_HPP
