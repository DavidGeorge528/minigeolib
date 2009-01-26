#ifndef VECTOR_TEST_MACROS_HPP
#define VECTOR_TEST_MACROS_HPP

/// \brief It extracts the unit type from a tuple of types.
/// \sa algebraic_traited_types
#define TSTVECTOR_UNIT_TYPE( TUPLE) boost::mpl::at<TUPLE, boost::mpl::int_<1> >::type

/// \brief It extracts the unit traits type from a tuple of types.
/// \sa algebraic_traited_types
#define TSTVECTOR_TRAITS_TYPE( TUPLE) boost::mpl::at<TUPLE, boost::mpl::int_<2> >::type

/// \brief It extracts the number of dimensions from a tuple of types.
/// \sa algebraic_traited_types
#define TSTVECTOR_DIM_NUMBER( TUPLE) boost::mpl::at<TUPLE, boost::mpl::int_<0> >::type::value

/// \brief It defines an alias for the unit type, called unit_type.
/// \details
///		Use this macro inside the test cases, to improve naming of the currently tested unit type.
#define TSTVECTOR_UNIT_ALIAS( TUPLE) typedef TSTVECTOR_UNIT_TYPE(TUPLE) unit_type


#endif // VECTOR_TEST_MACROS_HPP
