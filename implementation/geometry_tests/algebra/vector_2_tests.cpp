#include "algebra/vector.hpp"
#include "vector_test_fixtures.hpp"
#include "../test_traits.hpp"
#include "../tests_common.hpp"

namespace
{
	using namespace algebra;

	typedef boost::mpl::list< 
		vector< 2, double, unit_traits< double> >,
		vector< 2, float, unit_traits< float> > > tested_types;


#define DEF_TYPES( V) \
	typedef V tested_vector; \
	typedef typename tested_vector::unit_type unit_type; \
	typedef vector_test_fixture< tested_vector::DIMENSIONS, unit_type, typename tested_vector::unit_traits_type > test_fixture

BOOST_AUTO_TEST_CASE_TEMPLATE( test_specific_initialization, V, tested_types)
{
	DEF_TYPES( V);
	test_fixture f;
	tested_vector v( f.c_array_[0], f.c_array_[1]);

	ALGTEST_CHECK_EQUAL_UNIT( f.c_array_[0], v(0));
	ALGTEST_CHECK_EQUAL_UNIT( f.c_array_[1], v(1));
}

} // namespace
