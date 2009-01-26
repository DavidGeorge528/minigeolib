#include "algebra/matrix.hpp"
#include "matrix_test_fixtures.hpp"
#include "../test_traits.hpp"
#include "../tests_common.hpp"

namespace
{
	using namespace algebra;

	typedef boost::mpl::list< 
		matrix< 3, 3, float, unit_traits< float> >,
		matrix< 3, 3, double, unit_traits< double> > >
		tested_types;

#define DEF_TEST( M) \
	typedef M tested_matrix; \
	typedef typename tested_matrix::unit_type unit_type; \
	typedef matrix_test_fixture< M::ROWS, M::COLUMNS, typename M::unit_type, typename M::unit_traits_type> test_fixture;

BOOST_AUTO_TEST_CASE_TEMPLATE( test_specialized_initialization, M, tested_types)
{
	DEF_TEST(M);
	test_fixture f;
	tested_matrix m( 
		f.c_array_[0][0], f.c_array_[0][1], f.c_array_[0][2],
		f.c_array_[1][0], f.c_array_[1][1], f.c_array_[1][2],
		f.c_array_[2][0], f.c_array_[2][1], f.c_array_[2][2]);

	ALGTEST_CHECK_EQUAL_UNIT( f.c_array_[0][0], m(0,0));
	ALGTEST_CHECK_EQUAL_UNIT( f.c_array_[0][1], m(0,1));
	ALGTEST_CHECK_EQUAL_UNIT( f.c_array_[0][2], m(0,2));
	ALGTEST_CHECK_EQUAL_UNIT( f.c_array_[1][0], m(1,0));
	ALGTEST_CHECK_EQUAL_UNIT( f.c_array_[1][1], m(1,1));
	ALGTEST_CHECK_EQUAL_UNIT( f.c_array_[1][2], m(1,2));
	ALGTEST_CHECK_EQUAL_UNIT( f.c_array_[2][0], m(2,0));
	ALGTEST_CHECK_EQUAL_UNIT( f.c_array_[2][1], m(2,1));
	ALGTEST_CHECK_EQUAL_UNIT( f.c_array_[2][2], m(2,2));
}


// ---------------------------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE_TEMPLATE( test_identity, M, tested_types)
{
	DEF_TEST( M);
	test_fixture f;
	const tested_matrix& m = tested_matrix::IDENTITY();
	BOOST_CHECK( check_equal_matrix( &f.identity_[0][0], &f.identity_[0][0] + M::ROWS*M::COLUMNS, m));
}

} // namespace
