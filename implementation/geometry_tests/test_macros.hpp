#ifndef TEST_MACROS_HPP
#define TEST_MACROS_HPP

/// \brief It extracts the unit type from a tuple of types.
/// \sa algebraic_traited_types
#define GEOMTEST_UNIT_TYPE( TUPLE) boost::mpl::at<TUPLE, boost::mpl::int_<1> >::type

/// \brief It extracts the unit traits type from a tuple of types.
/// \sa algebraic_traited_types
#define GEOMTEST_TRAITS_TYPE( TUPLE) boost::mpl::at<TUPLE, boost::mpl::int_<2> >::type

/// \brief It extracts the number of dimensions from a tuple of types.
/// \sa algebraic_traited_types
#define GEOMTEST_DIM_NUMBER( TUPLE) boost::mpl::at<TUPLE, boost::mpl::int_<0> >::type::value

/// \brief It defines an alias for the unit type, called unit_type.
/// \details
///		Use this macro inside the test cases, to improve naming of the currently tested unit type.
#define GEOMTEST_UNIT_ALIAS( TUPLE) typedef GEOMTEST_UNIT_TYPE(TUPLE) unit_type

/// \brief It checks the equality two values of type unit_type, using the tollerance specified by the test traits.
/// \sa GEOMTEST_UNIT_ALIAS
#define GEOMTEST_CHECK_EQUAL_UNIT( E, O) \
	BOOST_CHECK_CLOSE( static_cast< unit_type>(E), O, test_traits< unit_type>::check_tollerance())


#endif // TEST_MACROS_HPP
