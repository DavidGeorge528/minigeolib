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

/// \brief 
///		Definition of the testing contexts that are used by generic test cases. It is a tuple of number of 
///		dimensions, the type of the unit and the traits for the unit type.
typedef boost::mpl::list< 
	boost::mpl::vector< boost::mpl::int_<2>,	float,	algebra::unit_traits< float> >,
	boost::mpl::vector< boost::mpl::int_<2>,	double,	algebra::unit_traits< double> >,
	boost::mpl::vector< boost::mpl::int_<3>,	float,	algebra::unit_traits< float> >,
	boost::mpl::vector< boost::mpl::int_<3>,	double,	algebra::unit_traits< double> >,
	boost::mpl::vector< boost::mpl::int_<4>,	float,	algebra::unit_traits< float> >,
	boost::mpl::vector< boost::mpl::int_<4>,	double,	algebra::unit_traits< double> >
> algebraic_traited_types;


#endif // TESTS_COMMON_HPP
