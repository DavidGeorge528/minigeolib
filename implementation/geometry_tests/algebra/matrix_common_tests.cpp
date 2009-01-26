#include "algebra/matrix.hpp"
#include "matrix_test_fixtures.hpp"
#include "../tests_common.hpp"
#include "../test_traits.hpp"

namespace
{

using namespace algebra;

BOOST_AUTO_TEST_CASE_TEMPLATE( test_default_constructor, M, matrix_test_types)
{
	typedef M matrix_type;
	typedef matrix_test_fixture< M::ROWS, M::COLUMNS, typename M::unit_type, typename M::unit_traits_type> test_fixture;
	test_fixture f;

	matrix_type m;
	BOOST_CHECK( check_equal_matrix( &f.zeros_[0][0], &f.zeros_[0][0] + M::ROWS*M::COLUMNS, m));
}

} // namespace
