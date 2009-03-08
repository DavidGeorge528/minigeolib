#include "algebra/vector.hpp"
#include "vector_test_fixtures.hpp"
#include "../test_traits.hpp"
#include "../tests_common.hpp"

namespace
{
	using namespace algebra;

	typedef boost::mpl::list< 
		vector< 3, double, unit_traits< double> >,
		vector< 3, float, unit_traits< float> > > tested_types;


#define DEF_TYPES( V) \
	typedef V tested_vector; \
	typedef typename tested_vector::unit_type unit_type; \
	typedef vector_test_fixture< tested_vector::DIMENSIONS, unit_type, typename tested_vector::unit_traits_type > test_fixture

BOOST_AUTO_TEST_CASE_TEMPLATE( test_specific_initialization, V, tested_types)
{
	DEF_TYPES( V);
	test_fixture f;
	tested_vector v( f.c_array_[0], f.c_array_[1], f.c_array_[2]);

	ALGTEST_CHECK_EQUAL_UNIT( f.c_array_[0], v(0));
	ALGTEST_CHECK_EQUAL_UNIT( f.c_array_[1], v(1));
	ALGTEST_CHECK_EQUAL_UNIT( f.c_array_[2], v(2));
}

// ---------------------------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE_TEMPLATE( test_cross_product, V, tested_types)
{
	DEF_TYPES( V);
	tested_vector v1( 1, 0, 0);
	tested_vector v2( 0, 1, 0);
	tested_vector v = v1%v2;
	ALGTEST_CHECK_EQUAL_UNIT( 0, v(0));
	ALGTEST_CHECK_EQUAL_UNIT( 0, v(1));
	ALGTEST_CHECK_EQUAL_UNIT( 1, v(2));
}

} // namespace
