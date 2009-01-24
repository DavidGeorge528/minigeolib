#ifndef TEST_TRAITS_HPP
#define TEST_TRAITS_HPP


/// \brief It defines the utility methods that are used by the test cases.
template< typename U>
struct test_traits
{
	static U check_tollerance() { return 0; }
};

/// \copydoc test_traits<U>
template<>
struct test_traits< float>
{
	static float check_tollerance() { return 0.000001; }
};


/// \copydoc test_traits<U>
template<>
struct test_traits< double>
{
	static double check_tollerance() { return 0.000001; }
};


#endif // TEST_TRAITS_HPP
